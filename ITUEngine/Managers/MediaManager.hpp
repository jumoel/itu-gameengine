#ifndef ITUENGINE_MEDIA_MANAGER_H
#define ITUENGINE_MEDIA_MANAGER_H

#include <list>
#include <vector>
#include <Game/Texture.hpp>
#include <Game/GfxModel.hpp>
#include <Game/Model.hpp>
#include <Templates/TSingleton.hpp>
#include <string>



class MediaManager
{
	SINGLETON( MediaManager )

public:
	

	const aiScene* helper;

	const aiScene* playerScene;

	Model* crazyModel;
	Model* carModel;
	Model* boxModel;
	Model* ground;
	Texture* boxTex1;
	Texture* boxTex2;
	Texture* boxTex3;
	Texture* carTexture1;
	Texture* carTexture2;
	Texture* warrior;
	Texture* playerTex;
	Texture* defaultTex;
	Texture* Hud;
	GfxModel *playerModel;
	std::vector<Texture*> textures;

	Texture* LoadTexture(char *filename, char* name);
	GfxModel* LoadModel(const char *filename);
	Texture* FindTexture(const char *name);
	void reloadTextures(GfxModel* model);

	Model* ImportAssimpModel( const std::string& pFile);

	void StartUp();
	void ShutDown();
	
};

#endif
