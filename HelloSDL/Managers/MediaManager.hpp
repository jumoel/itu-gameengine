#ifndef ITUENGINE_MEDIA_MANAGER_H
#define ITUENGINE_MEDIA_MANAGER_H

#include <list>
#include <vector>
#include <Game/Texture.hpp>
#include <Game/GfxModel.hpp>
#include <Templates/TSingleton.hpp>

class MediaManager
{
	SINGLETON( MediaManager )

public:
	
	
	Texture* warrior;
	GfxModel *someModel;
	std::vector<Texture*> textures;
	Texture* LoadTexture(char *filename, char* name);
	GfxModel* LoadModel(const char *filename);
	Texture* FindTexture(const char *name);
	void reloadTextures(GfxModel* model);

	void Init();
};

#endif
