#ifndef ITUENGINE_MEDIA_MANAGER_H
#define ITUENGINE_MEDIA_MANAGER_H

#include <list>
#include <vector>
#include <Game/Texture.hpp>
#include <Game/Model.hpp>
#include <Templates/TSingleton.hpp>
#include <string>



class MediaManager
{
	SINGLETON( MediaManager )

public:
	

	const aiScene* helper;

	Model* crazyModel;
	Model* boxModel;
	Model* ground;
	Texture* playerTex;
	Texture* defaultTex;
	std::vector<Texture*> textures;

	Texture* LoadTexture(char *filename, char* name);
	Texture* FindTexture(const char *name);

	Model* ImportAssimpModel( const std::string& pFile);

	void StartUp();
	void ShutDown();
	
};

#endif
