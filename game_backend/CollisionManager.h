#ifndef _COLLISIONMANAGER_
#define _COLLISIONMANAGER_
#include "CollisionPolygon.h"
class CollisionManager{
public:
	static CollisionManager* Instance(){
		if(s_pInstance==0){
			s_pInstance=new CollisionManager();
		}
		return s_pInstance;
	}
	bool isColliding(CollisionPolygon *C1,CollisionPolygon *C2);
private:
	static CollisionManager* s_pInstance;
	
};
#endif