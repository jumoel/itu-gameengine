#include <Game/Model.hpp>
#include <assert.h>
#include <Managers/MediaManager.hpp>

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

    glGenBuffers(1, &VB);
  	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

Model::Model()
{
}


Model::~Model()
{
    Clear();
}


void Model::Clear()
{
    for (unsigned int i = 0 ; i < m_Materials.size() ; i++) {
        SAFE_DELETE(m_Materials[i]);
    }
}

bool Model::InitFromScene(const aiScene* pScene, const std::string& Filename)
{  
	//std::cout << "Number of meshes: " << + pScene->mNumMeshes << std::endl;
	//std::cout << "Number of materials: " << + pScene->mNumMaterials << std::endl;

    m_Entries.resize(pScene->mNumMeshes);

    m_Materials.resize(pScene->mNumMaterials);

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
                 Vector3f(-pNormal->x, -pNormal->y, -pNormal->z));
		//std::cout << "x: " << v.m_normal.x() << ", y: " << v.m_normal.y() <<  ", z: " << v.m_normal.z() << std::endl;
        Vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
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

        m_Materials[i] = new Material();
		aiColor3D color(0.0f,0.0f,0.0f);
		pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		m_Materials[i]->diffuse[0] = color.r;
		m_Materials[i]->diffuse[1] = color.g;
		m_Materials[i]->diffuse[2] = color.b;
		m_Materials[i]->diffuse[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		m_Materials[i]->specular[0] = color.r, m_Materials[i]->specular[1] = color.g, m_Materials[i]->specular[2] = color.b, m_Materials[i]->specular[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		m_Materials[i]->ambient[0] = color.r, m_Materials[i]->ambient[1] = color.g, m_Materials[i]->ambient[2] = color.b, m_Materials[i]->ambient[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		m_Materials[i]->emissive[0] = color.r, m_Materials[i]->emissive[1] = color.g, m_Materials[i]->emissive[2] = color.b, m_Materials[i]->emissive[3] = 1.0f;

		pMaterial->Get(AI_MATKEY_SHININESS, m_Materials[i]->shininess);

		//pMaterial->Get(AI_MATKEY_SHADING_MODEL, m_Materials[i]->shader);


        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + Path.data;
				char* temp = new char();
				strcpy(temp, FullPath.c_str());

				m_Materials[i]->texture = SINGLETONINSTANCE( MediaManager )->FindTexture(temp);
				if(m_Materials[i]->texture == NULL)
				{
					m_Materials[i]->texture = SINGLETONINSTANCE( MediaManager )->LoadTexture(temp, temp);
				}
				
				if(!m_Materials[i]->texture) {
					m_Materials[i]->texture =  SINGLETONINSTANCE( MediaManager )->defaultTex;
				}
					


				m_Materials[i]->texture->textureTarget = GL_TEXTURE_2D;

            }
        }
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

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Materials.size()) {
			if(m_Materials[MaterialIndex]->texture)
			{
				m_Materials[MaterialIndex]->texture->Bind(GL_TEXTURE0);
			}
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_Materials[MaterialIndex]->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_Materials[MaterialIndex]->specular);
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_Materials[MaterialIndex]->ambient);
			glMaterialfv(GL_FRONT, GL_EMISSION, m_Materials[MaterialIndex]->emissive);
			glMaterialf(GL_FRONT, GL_SHININESS, m_Materials[MaterialIndex]->shininess);
        }

		

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
			if(m_Materials[MaterialIndex]->texture)
			{
				m_Materials[MaterialIndex]->texture->Bind(GL_TEXTURE0);
			}
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_Materials[MaterialIndex]->diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_Materials[MaterialIndex]->specular);
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_Materials[MaterialIndex]->ambient);
			glMaterialfv(GL_FRONT, GL_EMISSION, m_Materials[MaterialIndex]->emissive);
			glMaterialf(GL_FRONT, GL_SHININESS, m_Materials[MaterialIndex]->shininess);
        }

		

        glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
#endif
}

