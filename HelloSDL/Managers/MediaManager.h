#ifndef ITUENGINE_MEDIA_MANAGER_H
#define ITUENGINE_MEDIA_MANAGER_H

#include <list>
#include <vector>
#include "../Game/Texture.h"
#include "../Templates/TSingleton.h"

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
