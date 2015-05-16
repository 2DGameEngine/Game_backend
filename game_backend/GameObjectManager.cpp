#include "GameObjectManager.h"
void GameObjectManager::addObject(GameObject* game_object){
	game_object_list.push_back(game_object);
	//id_object_map[game_object->object_id]=game_object;
}
GameObject* GameObjectManager::getObject(std::string object_id){
	for(std::vector<int>::size_type i = 0; i != game_object_list.size(); i++) {
		if(!game_object_list[i]->object_id.compare(object_id)){
			return game_object_list[i];
		}
	}
}
void GameObjectManager::addObjectToDelete(std::string object_id){
	objects_to_delete.push_back(GameObjectManager::getObject(object_id));
}
GameObjectManager* GameObjectManager::s_pInstance=0;