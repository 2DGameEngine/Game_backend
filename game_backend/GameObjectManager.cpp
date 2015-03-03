#include "GameObjectManager.h"
void GameObjectManager::addObject(GameObject* game_object){
	game_object_list.push_back(game_object);
}
GameObjectManager* GameObjectManager::s_pInstance=0;