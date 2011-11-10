#ifndef ITUENGINE_MEDIA_MANAGER_H
#define ITUENGINE_MEDIA_MANAGER_H

#include <list>
#include <vector>
#include <Game/Texture.hpp>
#include <Templates/TSingleton.hpp>

class MediaManager
{
	SINGLETON( MediaManager )

public:
	
	Texture* warrior;
	//std::list<Texture*> *textures;
	Texture* LoadTexture(char *filename, char* name);

	void Init();
};

#endif
