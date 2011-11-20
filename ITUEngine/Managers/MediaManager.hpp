#ifndef ITUENGINE_MEDIA_MANAGER_H
#define ITUENGINE_MEDIA_MANAGER_H

#include <list>
#include <vector>
#include <Game/Texture.hpp>
#include <Game/GfxModel.hpp>
#include <Templates/TSingleton.hpp>
#include <string>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags


class MediaManager
{
	SINGLETON( MediaManager )

public:
	
	const aiScene* scene;
	Texture* warrior;
	Texture* playerTex;
	GfxModel *playerModel;
	std::vector<Texture*> textures;
	Texture* LoadTexture(char *filename, char* name);
	GfxModel* LoadModel(const char *filename);
	Texture* FindTexture(const char *name);
	void reloadTextures(GfxModel* model);

	bool DoTheImportThing( const std::string& pFile);

	void StartUp();
	void ShutDown();
	
};

#endif
