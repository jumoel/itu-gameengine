#include <Managers/MediaManager.hpp>
#include <iostream>
#include <fstream>

/* 
	MS3D STRUCTURES 
*/

// byte-align structures
#ifdef _MSC_VER
#	pragma pack( push, packing )
#	pragma pack( 1 )
#	define PACK_STRUCT
#elif defined( __GNUC__ )
#	define PACK_STRUCT	__attribute__((packed))
#else
#	error you must byte-align these structures with the appropriate compiler directives
#endif

typedef unsigned char byte;
typedef unsigned short word;

// File header
struct MS3DHeader
{
	char m_ID[10];
	int m_version;
} PACK_STRUCT;

// Vertex information
struct MS3DVertex
{
	byte m_flags;
	float m_vertex[3];
	char m_boneID;
	byte m_refCount;
} PACK_STRUCT;

// Triangle information
struct MS3DTriangle
{
	word m_flags;
	word m_vertexIndices[3];
	float m_vertexNormals[3][3];
	float m_s[3], m_t[3];
	byte m_smoothingGroup;
	byte m_groupIndex;
} PACK_STRUCT;

// Material information
struct MS3DMaterial
{
    char m_name[32];
    float m_ambient[4];
    float m_diffuse[4];
    float m_specular[4];
    float m_emissive[4];
    float m_shininess;	// 0.0f - 128.0f
    float m_transparency;	// 0.0f - 1.0f
    byte m_mode;	// 0, 1, 2 is unused now
    char m_texture[128];
    char m_alphamap[128];
} PACK_STRUCT;

//	Joint information
struct MS3DJoint
{
	byte m_flags;
	char m_name[32];
	char m_parentName[32];
	float m_rotation[3];
	float m_translation[3];
	word m_numRotationKeyframes;
	word m_numTranslationKeyframes;
} PACK_STRUCT;

// Keyframe data
struct MS3DKeyframe
{
	float m_time;
	float m_parameter[3];
} PACK_STRUCT;

// Default alignment
#ifdef _MSC_VER
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT



void MediaManager::StartUp()
{
	///IMPORTANT: LOAD TEXTURES BEFORE MODELS
	defaultTex = LoadTexture("Resources/Wood.tga", "DefaultTex");
	carTexture1 = LoadTexture("Resources/truck_thumb.tga", "Resources/truck_thumb.jpg");
	carTexture2 = LoadTexture("Resources/truck_1915.tga", "Resources/truck_1915.jpg");
	playerTex = LoadTexture("Resources/kalahk.tga", "Resources/kalahk.jpg");
	warrior = LoadTexture("Resources/Space_Warrior.tga", "Warrior");
	LoadTexture("Resources/1b9a24c3118674f59ef3cb7ac19eab3d.tga", "Resources/1B9A24C3.PNG");
	LoadTexture("Resources/box_diffuse.tga", "Resources/BOX_DIFF.PNG");
	Hud = LoadTexture("Resoures/HUD.tga", "HUD");

	

	boxModel = ImportAssimpModel("Resources/box.3ds");
	ground = ImportAssimpModel("Resources/plane.3ds");
	//carModel = ImportAssimpModel("Resources/truck_1915.ms3d");
	//playerModel = LoadModel("Resources/Model.ms3d");
	crazyModel = ImportAssimpModel("Resources/Kalahk.ms3d");
	
}

void MediaManager::ShutDown()
{
	delete helper;

	delete playerScene;

	delete crazyModel;
	delete carModel;
	delete boxModel;
	delete ground;
	delete boxTex1;
	delete boxTex2;
	delete boxTex3;
	delete carTexture1;
	delete carTexture2;
	delete warrior;
	delete playerTex;
	delete defaultTex;
	delete Hud;
	delete playerModel;

	textures.clear();
}

Texture* MediaManager::LoadTexture(char *filename, char* name)                 // Loads A TGA File Into Memory
{   
	Texture *tex = new Texture();
	tex->name = name;
	tex->filename = filename;

    GLubyte     TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};					// Uncompressed TGA Header
    GLubyte     TGAcompare[12];												// Used To Compare TGA Header
    GLubyte     header[6];													// First 6 Useful Bytes From The Header
    GLuint      bytesPerPixel;												// Holds Number Of Bytes Per Pixel Used In The TGA File
    GLuint      imageSize;													// Used To Store The Image Size When Setting Aside Ram
    GLuint      temp;														// Temporary Variable
    GLuint      type=GL_RGBA;												// Set The Default GL Mode To RBGA (32 BPP)

	
	FILE *file = fopen(filename, "rb");										// Open The TGA File
	if( file==NULL														||	// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||  // Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)													// Did The File Even Exist?
		{
			std::cout << "ERROR! The file " << filename << " does not exist!" << std::endl; 
			return NULL;													// Return False
		}
		else
		{
			fclose(file);													// If Anything Failed, Close The File
			std::cout << "ERROR! The file is not supported" << std::endl;
			return NULL;													 // Return False
		}
	}

	tex->width  = header[1] * 256 + header[0];							// Determine The TGA Width  (highbyte*256+lowbyte)
	tex->height = header[3] * 256 + header[2];							// Determine The TGA Height (highbyte*256+lowbyte)

	if( tex->width   <=0  ||											// Is The Width Less Than Or Equal To Zero
		tex->height  <=0  ||											// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))									// Is The TGA 24 or 32 Bit?
	{
		fclose(file);														// If Anything Failed, Close The File
		std::cout << "ERROR! The TGA is not 24 or 32bit" << std::endl;
		return NULL;														// Return False
	}

	tex->bpp		= header[4];											// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel   = tex->bpp/8;										// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= tex->width * tex->height * bytesPerPixel;     // Calculate The Memory Required For The TGA Data

	tex->imageData=(GLubyte *)malloc(imageSize);						// Reserve Memory To Hold The TGA Data

	if( tex->imageData==NULL ||											// Does The Storage Memory Exist?
		fread(tex->imageData, 1, imageSize, file)!=imageSize)			// Does The Image Size Match The Memory Reserved?
	{
		if(tex->imageData!=NULL)										// Was Image Data Loaded
			free(tex->imageData);										// If So, Release The Image Data
		fclose(file);														// Close The File
		std::cout << "ERROR occured during loading the TGA" << std::endl;
		return NULL;														// Return False
	}
	
	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)						// Loop Through The Image Data
	{																		// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=tex->imageData[i];											// Temporarily Store The Value At Image Data 'i'
		tex->imageData[i] = tex->imageData[i + 2];					// Set The 1st Byte To The Value Of The 3rd Byte
		tex->imageData[i + 2] = temp;									// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);															// Success - Close The File

	
	// Build A Texture From The Data
	glGenTextures(1, &(tex->texID));									// Generate OpenGL texture IDs
	glBindTexture(GL_TEXTURE_2D, tex->texID);							// Bind Our Texture
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);       // Linear Filtered
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);       // Linear Filtered
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	if (tex->bpp==24)													// Was The TGA 24 Bits
	{
		type=GL_RGB;														// If So Set The 'type' To GL_RGB
		std::cout << "The TGA has no alpha channel" << std::endl;
	}

	
    //glTexImage2D(GL_TEXTURE_2D, 0, type, tex->width, tex->height, 0, type, GL_UNSIGNED_BYTE, tex->imageData);
	
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, tex->width, tex->height, type, GL_UNSIGNED_BYTE, tex->imageData );
 
	textures.push_back(tex);

	std::cout << "The TGA has been loaded successfully" << std::endl;
	return tex;															// Success - Texture Building Went Ok, Return True
}

GfxModel* MediaManager::LoadModel(const char *filename)
{
	std::cout << "Loading model" << std::endl;

	GfxModel* model = new GfxModel();

	std::ifstream inputFile( filename, std::ios::in | std::ios::binary );

	if(inputFile.fail())
	{
		std::cout << "Loading file into stream failed!!!" << std::endl;
		return NULL;
	}
	inputFile.seekg(0, std::ios::end);
	long fileSize = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);

	byte *buffer = new byte[fileSize];
	//inputFile.read( buffer, fileSize);
	inputFile.read(reinterpret_cast<char*>(buffer), fileSize);
	inputFile.close();

	const byte *ptr = buffer;
	MS3DHeader *headerPtr = (MS3DHeader*) ptr;
	ptr += sizeof( MS3DHeader );
	
	if(strncmp( headerPtr->m_ID, "MS3D000000", 10 ) != 0 )
	{
		std::cout << "Error loading model: 'Not a Milkshape file'" << std::endl;
		return NULL; //Not a milkshape file
	}

	if(headerPtr->m_version < 3 || headerPtr->m_version > 4)
	{
		std::cout << "Error loading model: 'Unhandled file version. Only Milkshape version 1.3 and 1.4 is supported'" << std::endl;
		return NULL;
	}

	int nVertices = *(word *) ptr;
	model->numVertices = nVertices;
	model->mVertices = new Vertex[nVertices];
	ptr += sizeof( word );
	int i;
	for(i = 0; i < nVertices; i++)
	{
		MS3DVertex *vertexPtr = (MS3DVertex* ) ptr;
		model->mVertices[i].boneID = vertexPtr->m_boneID;
		memcpy(model->mVertices[i].location, vertexPtr->m_vertex, sizeof(float) * 3);
		ptr += sizeof(MS3DVertex);
	}

	int nTriangles = *( word*) ptr;
	model->numTriangles = nTriangles;
	model->mTriangles = new Triangle[nTriangles];
	ptr += sizeof(word);

	for(i = 0; i < nTriangles; i++)
	{
		MS3DTriangle* trianglePtr = (MS3DTriangle* ) ptr;
		int vertexIndices[3] = { trianglePtr->m_vertexIndices[0], trianglePtr->m_vertexIndices[1], trianglePtr->m_vertexIndices[2]};
		
		float t[3] = {1.0f-trianglePtr->m_t[0], 1.0f-trianglePtr->m_t[1], 1.0f-trianglePtr->m_t[2]};
		memcpy(model->mTriangles[i].vertexNormals, trianglePtr->m_vertexNormals, sizeof(float)*3*3);
		memcpy(model->mTriangles[i].sTex, trianglePtr->m_s, sizeof(float)*3);
		memcpy(model->mTriangles[i].tTex, t, sizeof(float)*3);
		memcpy(model->mTriangles[i].verticeIndices, vertexIndices, sizeof(int)*3);
		ptr += sizeof(MS3DTriangle);
		/*for(int f = 0; f < 3; f++)
		{
			std::cout << "Vertex index: " << model->mTriangles->verticeIndices[f] << std::endl;
		}*/
	}

	int nGroups = *(word*) ptr;
	model->numMeshes = nGroups;
	model->mMeshes = new Mesh[nGroups];
	ptr += sizeof(word);

	for(i = 0; i < nGroups; i++)
	{
		ptr += sizeof(byte); //Flags
		ptr += 32; //name

		word nTriangles = *(word*) ptr;
		ptr += sizeof(word);
		int* triangleIndicesPtr = new int[nTriangles];
		for(int j = 0; j < nTriangles; j++)
		{
			triangleIndicesPtr[j] = *(word*) ptr;
			ptr += sizeof(word);
		}

		char materialIndex = *(char*) ptr;
		ptr += sizeof(char);

		model->mMeshes[i].materialIndex = materialIndex;
		model->mMeshes[i].numTriangles = nTriangles;
		model->mMeshes[i].triangleIndices = triangleIndicesPtr;
		/*
		for(int f = 0; f < model->mMeshes[i].numTriangles; f++)
		{
			int triangleIndex = model->mMeshes[i].triangleIndices[f];
			std::cout << "index: " << triangleIndex << std::endl;
			for ( int k = 0; k < 3; k++ )
				{
					int index =  model->mTriangles[triangleIndex].verticeIndices[k]; //pTri->verticeIndices[k];
					//std::cout << "index: " << index << std::endl;
				}

		}*/
	}

	
	int nMaterials = *( word* )ptr;
	model->numMaterials = nMaterials;
	model->mMaterials = new Mat[nMaterials];
	ptr += sizeof( word );

	for ( i = 0; i < nMaterials; i++ )
	{

		MS3DMaterial *pMaterial = ( MS3DMaterial* )ptr;
		memcpy( model->mMaterials[i].ambient, pMaterial->m_ambient, sizeof( float )*4 );
		memcpy( model->mMaterials[i].diffuse, pMaterial->m_diffuse, sizeof( float )*4 );
		memcpy( model->mMaterials[i].specular, pMaterial->m_specular, sizeof( float )*4 );
		memcpy( model->mMaterials[i].emissive, pMaterial->m_emissive, sizeof( float )*4 );
		model->mMaterials[i].shininess = pMaterial->m_shininess;
		int strLenght = strlen( pMaterial->m_texture )+1;
		model->mMaterials[i].textureFileName = (char*)malloc(strLenght);

		strcpy_s( model->mMaterials[i].textureFileName, strLenght, pMaterial->m_texture );
		ptr += sizeof( MS3DMaterial );
	}
	
	for(int k = 0; k < model->numMaterials; k++)
	{
		//std::cout << "model texture file name: " << model->mMaterials[k].textureFileName << std::endl;
		model->mMaterials[k].tex = LoadTexture(model->mMaterials[k].textureFileName, model->mMaterials[k].textureFileName);
	}
	reloadTextures(model);

	delete buffer;
	std::cout << "The MS3D has been loaded successfully " << std::endl;
	return model;

}

void MediaManager::reloadTextures(GfxModel* model)
{
	for ( int i = 0; i < model->numMaterials; i++ )
	{
		if ( strlen( model->mMaterials[i].textureFileName ) > 0 )
		{
			bool exists = false;
			Texture* tex = FindTexture(model->mMaterials[i].textureFileName);
			
			if(tex != NULL)
			{
				model->mMaterials[i].mTexture = tex->texID;
			}
			else
			{
				model->mMaterials[i].mTexture = 0;
			}
		}
        else
		{
			model->mMaterials[i].mTexture = 0;
		}
	}
}


Texture* MediaManager::FindTexture(const char* name)
{
	for(int j = 0; j < textures.size(); j++)
	{
		if(strcmp(textures[j]->filename, name) == 0 || strcmp(textures[j]->name, name) == 0)
		{
			return textures[j];
		}
	}
	return NULL;
}

Model* MediaManager::ImportAssimpModel( const std::string& Filename)
{
	
	Model* model = new Model();
	
    bool Ret = false;
    Assimp::Importer Importer;

    helper = Importer.ReadFile(Filename.c_str(),
		aiProcess_CalcTangentSpace  |
        aiProcess_Triangulate |
        aiProcess_MakeLeftHanded |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType |
        aiProcess_CalcTangentSpace |
        aiProcess_JoinIdenticalVertices |
        aiProcess_GenNormals |
        aiProcess_LimitBoneWeights |
        aiProcess_RemoveRedundantMaterials |
		aiProcess_GenUVCoords |
		aiProcess_TransformUVCoords |
		aiProcess_FixInfacingNormals |
		aiProcess_OptimizeMeshes);

    if (helper) {
        Ret = model->InitFromScene(helper, Filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }

    return model;

	/*
  // Create an instance of the Importer class
  Assimp::Importer importer;
  
  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll 
  // propably to request more postprocessing than we do in this example.
  helper = importer.ReadFile( Filename, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);
  
  // If the import failed, report it
  if( !helper)
  {
	  std::cout << "Import failed" << std::endl;
    //DoTheErrorLogging( importer.GetErrorString());
    return model;
  }

  // Now we can access the file's contents. 
  //DoTheSceneProcessing( scene);
  
  // We're done. Everything will be cleaned up by the importer destructor
  //delete scene;
  return model;*/
}

