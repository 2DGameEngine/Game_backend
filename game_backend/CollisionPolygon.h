#ifndef _COLLISIONPOLYGON_
#define _COLLISIONPOLYGON_
class CollisionPolygon{
public:
	float x;
	float y;
	float width;
	float height;
	CollisionPolygon(float x,float y,float width,float height){
		CollisionPolygon::x=x;
		CollisionPolygon::y=y;
		CollisionPolygon::width=width;
		CollisionPolygon::height=height;
	}
	void updatePosition(float x,float y){
		CollisionPolygon::x=x;
		CollisionPolygon::y=y;
	}
};
#endif