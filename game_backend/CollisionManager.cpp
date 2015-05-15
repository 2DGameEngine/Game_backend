#include "CollisionManager.h"
bool CollisionManager::isColliding(CollisionPolygon *rect1,CollisionPolygon *rect2){
	if (rect1->x < rect2->x + rect2->width &&
   rect1->x + rect1->width > rect2->x &&
   rect1->y < rect2->y + rect2->height &&
   rect1->height + rect1->y > rect2->y) {
		return true;
	}
	return false;
}
CollisionManager* CollisionManager::s_pInstance=0;