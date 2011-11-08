#ifndef ITUENGINE_SCENEDATA_H
#define ITUENGINE_SCENEDATA_H

#include <Managers/SceneGraphManager.hpp>

SceneGraphManager *createGraph();
SceneGraphManager *createGraphVBO();

void deleteGraphVBO(Object *root);

#endif