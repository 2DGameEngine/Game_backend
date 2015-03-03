#ifndef _GAMEOBJECTMANAGER_
#define _GAMEOBJECTMANAGER_
#include "GameObject.h"
#include <vector>
class GameObject;
class GameObjectManager{
public:
	static GameObjectManager* Instance(){
		if(s_pInstance==0){
			s_pInstance=new GameObjectManager();
		}
		return s_pInstance;
	}
	void addObject(GameObject*);
	std::vector<GameObject*> getObjectList(){
		return game_object_list;
	}
private:
	std::vector<GameObject*> game_object_list;
	static GameObjectManager* s_pInstance;
};
#endif