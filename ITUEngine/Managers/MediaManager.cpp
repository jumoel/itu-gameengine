#include <Managers/MediaManager.hpp>
#include <iostream>
#include <fstream>


void MediaManager::StartUp()
{
	///IMPORTANT: LOAD TEXTURES BEFORE MODELS
	defaultTex = LoadTexture("Resources/Wood.tga", "DefaultTex");
	playerTex = LoadTexture("Resources/kalahk.tga", "Resources/kalahk.jpg");
	LoadTexture("Resources/1b9a24c3118674f59ef3cb7ac19eab3d.tga", "Resources/1B9A24C3.PNG");
	LoadTexture("Resources/box_diffuse.tga", "Resources/BOX_DIFF.PNG");	

	boxModel = ImportAssimpModel("Resources/box.3ds");
	ground = ImportAssimpModel("Resources/plane.3ds");
	crazyModel = ImportAssimpModel("Resources/Kalahk.ms3d");
	
}

void MediaManager::ShutDown()
{
	//delete helper;

	delete crazyModel;
	delete boxModel;
	delete ground;
	delete playerTex;
	delete defaultTex;

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	if (tex->bpp==24)													// Was The TGA 24 Bits
	{
		type=GL_RGB;														// If So Set The 'type' To GL_RGB
		std::cout << "The TGA has no alpha channel" << std::endl;
	}
	
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, tex->width, tex->height, type, GL_UNSIGNED_BYTE, tex->imageData );
 
	textures.push_back(tex);

	std::cout << "The TGA has been loaded successfully" << std::endl;
	return tex;															// Success - Texture Building Went Ok, Return True
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

}

