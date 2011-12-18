#include <Game/Model.hpp>
#include <assert.h>
#include <Managers/MediaManager.hpp>
#include <cmath>
#include <Assertion.hpp>

#define INVALID_OGL_VALUE 0xFFFFFFFF
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

Model::ModelEntry::ModelEntry()
{
    VB = INVALID_OGL_VALUE;
    IB = INVALID_OGL_VALUE;
    NumIndices  = 0;
    MaterialIndex = INVALID_MATERIAL;
};

Model::ModelEntry::~ModelEntry()
{
    if (VB != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &VB);
    }

    if (IB != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &IB);
    }
}

void Model::ModelEntry::Init(const std::vector<Vert>& Vertices,
                          const std::vector<unsigned int>& Indices)
{
    NumIndices = Indices.size();
	NumVertices = Vertices.size();
	Verts = Vertices;

    glGenBuffers(1, &VB);
  	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

Model::Model()
{
	m_Materials = new std::vector<Material*>();
}


Model::~Model()
{
	if(m_Materials != NULL)
	{
	//	delete m_Materials;
	}
}

bool Model::InitFromScene(const aiScene* pScene, const std::string& Filename)
{  
	//std::cout << "Number of meshes: " << + pScene->mNumMeshes << std::endl;
	//std::cout << "Number of materials: " << + pScene->mNumMaterials << std::endl;

    m_Entries.resize(pScene->mNumMeshes);

    m_Materials->resize(pScene->mNumMaterials);

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitModel(i, paiMesh);
    }

    return InitMaterials(pScene, Filename);
}

void Model::InitModel(unsigned int Index, const aiMesh* paiMesh)
{
    m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;
    
    std::vector<Vert> Vertices;
    std::vector<unsigned int> Indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		
        Vert v(Vector3f(pPos->x, pPos->y, pPos->z),
                 Vector2f(pTexCoord->x, pTexCoord->y),
                 Vector3f(pNormal->x, pNormal->y, pNormal->z));
		//std::cout << "x: " << v.m_normal.x() << ", y: " << v.m_normal.y() <<  ", z: " << v.m_normal.z() << std::endl;
		//std::cout << "Length of normal: " << sqrt( v.m_normal.x() * v.m_normal.x() + v.m_normal.y() * v.m_normal.y() + v.m_normal.z() * v.m_normal.z()) << std::endl;
        Vertices.push_back(v);
    }
	
    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];

		ASSERT(Face.mNumIndices == 3);

        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }

    m_Entries[Index].Init(Vertices, Indices);
}

bool Model::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    int SlashIndex = Filename.find_last_of("/");
    std::string Dir = "Resources";

	/*
    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }*/

    bool Ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];
		
		auto mat = new Material();
        
		aiColor3D color(0.0f,0.0f,0.0f);
		pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		mat->diffuse[0] = color.r;
		mat->diffuse[1] = color.g;
		mat->diffuse[2] = color.b;
		mat->diffuse[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		mat->specular[0] = color.r, mat->specular[1] = color.g, mat->specular[2] = color.b, mat->specular[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		mat->ambient[0] = color.r, mat->ambient[1] = color.g, mat->ambient[2] = color.b, mat->ambient[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		mat->emissive[0] = color.r, mat->emissive[1] = color.g, mat->emissive[2] = color.b, mat->emissive[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_SHININESS, mat->shininess);

		//pMaterial->Get(AI_MATKEY_SHADING_MODEL, mat->shader);


        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + Path.data;
				int pathLen = FullPath.length() + 1;
				char* temp = (char *)malloc(pathLen);
				strcpy_s(temp, pathLen, FullPath.c_str());

				mat->texture = SINGLETONINSTANCE( MediaManager )->FindTexture(temp);
				if(mat->texture == NULL)
				{
					mat->texture = SINGLETONINSTANCE( MediaManager )->LoadTexture(temp, temp);
				}
				
				if(!mat->texture) {
					mat->texture =  SINGLETONINSTANCE( MediaManager )->defaultTex;
				}
					


				mat->texture->textureTarget = GL_TEXTURE_2D;

            }
        }

		m_Materials->at(i) = mat;
    }

    return Ret;
}

void Model::Render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	

    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);

		glVertexPointer(3, GL_FLOAT, sizeof(Vert), 0);
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Vert), (const GLvoid*)12 );	
		glNormalPointer( GL_FLOAT, sizeof(Vert), (const GLvoid*)20);

		
		/*for(int j = 0; j < m_Entries[i].Verts.size(); j++)
		{
			glBegin(GL_LINE);
			glColor3f(1,0,0);
			glVertex3f(m_Entries[i].Verts[j].m_pos.x(),m_Entries[i].Verts[j].m_pos.y(),m_Entries[i].Verts[j].m_pos.z());
			glVertex3f(m_Entries[i].Verts[j].m_normal.x()*3.0f,m_Entries[i].Verts[j].m_normal.y()*3.0f,m_Entries[i].Verts[j].m_normal.z()*3.0f);

			glEnd();
		}
		glColor3f(1,1,1);
		*/

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Materials->size()) {
			if(m_Materials->at(MaterialIndex)->texture)
			{
				m_Materials->at(MaterialIndex)->texture->Bind(GL_TEXTURE0);
			}
			else
			{
				SINGLETONINSTANCE(MediaManager)->defaultTex->Bind(GL_TEXTURE0);
			}
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_Materials->at(MaterialIndex)->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_Materials->at(MaterialIndex)->specular);
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_Materials->at(MaterialIndex)->ambient);
			glMaterialfv(GL_FRONT, GL_EMISSION, m_Materials->at(MaterialIndex)->emissive);
			glMaterialf(GL_FRONT, GL_SHININESS, m_Materials->at(MaterialIndex)->shininess);
        }
		else
		{
			SINGLETONINSTANCE(MediaManager)->defaultTex->Bind(GL_TEXTURE0);
			float *temp = new float[4];
			temp[0] = 1.0f, temp[1] = 1.0f, temp[2] = 1.0f, temp[3] = 1.0f; 
			glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
			glMaterialfv(GL_FRONT, GL_SPECULAR, temp);
			glMaterialfv(GL_FRONT, GL_AMBIENT, temp);
			glMaterialfv(GL_FRONT, GL_EMISSION, temp);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
		}

		//glDrawArrays( GL_TRIANGLES, 0, m_Entries[i].NumVertices );

        glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY);
	glDisableClientState( GL_NORMAL_ARRAY );
	

#if 0
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Materials.size()) {
			if(m_Materials->at(MaterialIndex)->texture)
			{
				m_Materials->at(MaterialIndex)->texture->Bind(GL_TEXTURE0);
			}
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_Materials->at(MaterialIndex)->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_Materials->at(MaterialIndex)->specular);
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_Materials->at(MaterialIndex)->ambient);
			glMaterialfv(GL_FRONT, GL_EMISSION, m_Materials->at(MaterialIndex)->emissive);
			glMaterialf(GL_FRONT, GL_SHININESS, m_Materials->at(MaterialIndex)->shininess);
        }

		

        glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
#endif
}

