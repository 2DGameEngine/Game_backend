#include "GameObject.h"
void GameObject::add_state_animation_pair(std::string state_name,std::string animation_name){
	state_animation_map[state_name]=animation_name;
}
void GameObject::add_variable(std::string variable_name,float variable_value){
	variable_value_map[variable_name]=std::make_pair(variable_value,-999999);
}
float GameObject::return_variable_value(std::string variable_name){
	return variable_value_map[variable_name].first;
}
void GameObject::change_variable(std::string variable_name,float variable_value){
	variable_value_map[variable_name]=std::make_pair(variable_value,variable_value_map[variable_name].second);
}
bool GameObject::isVariableEqual(std::string variable_name, float new_variable_value){
	if(variable_value_map[variable_name].first==new_variable_value)
	{
		variable_value_map[variable_name].second=new_variable_value;
		return true;
	}
	else
		return false;
}
void GameObject::defaultUpdate(){
	//velocity.setX(0);
	//setVelocityX(0);
	//variable_value_map["velocity_y"].first=0;
	//velocity=getVelocity();
	//setState("standing");
	//Mix_HaltChannel(-1);
}
void GameObject::update(bool coll_cond){
	for(std::vector<int>::size_type i = 0; i != events.size(); i++) {
		events[i]->handleEvent(coll_cond);
	}
	/*if(width==50){
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)){
		setState("walk_right");
		velocity.setX(1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
		setState("walk_left");
		velocity.setX(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
		setState("walk_right");
		velocity.setY(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
		setState("walk_left");
		velocity.setY(1);
	}
	if(position.getY()>400){
		position.setY(400);
	}
}
else{
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
		setState("walk_right");
		velocity.setX(1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)){
		setState("walk_left");
		velocity.setX(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
		setState("walk_right");
		velocity.setY(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
		setState("walk_left");
		velocity.setY(1);
	}
	if(position.getY()>400){
		position.setY(400);
	}
}
*/
	//acceleration.setY(6);
	if(coll_cond==false&&is_static==false){
		
		//velocity.setY(velocity.getY()+.1);
		position=getPosition();
		velocity=getVelocity();
		acceleration=getAcceleration();
		velocity+=(acceleration+Vector2D(0,TheGame::Instance()->gravity));
		position+=velocity;
		setPosition(position);
		setVelocity(velocity);
		setAcceleration(acceleration);
		collision_polygon->updatePosition(position.getX(),position.getY());
	}
}
void GameObject::draw(){
	SDL_Rect destinationRectangle;
	SDL_Rect sourceRectangle;
	Animation* animation=model->getAnimation(getAnimationName(state));
	int refresh_rate=100/(animation->speed);
	int frame_number=int((SDL_GetTicks()/refresh_rate) %(animation->frame_ids.size()));
	sourceRectangle.x = (animation->frame_ids[frame_number].second-1)*model->width_of_frame;
	sourceRectangle.y = (animation->frame_ids[frame_number].first-1)*model->height_of_frame;
	destinationRectangle.w = width;
	destinationRectangle.h = height;
	sourceRectangle.w=model->width_of_frame;
	sourceRectangle.h=model->height_of_frame;
	Vector2D relativePosition = getPosition()-TheGame::Instance()->camera->getPosition();
	destinationRectangle.x = TheGame::Instance()->camera->offset.getX()+relativePosition.getX();
	destinationRectangle.y = TheGame::Instance()->camera->offset.getY()+relativePosition.getY();

	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),model->texture,&sourceRectangle,&destinationRectangle,0,0,SDL_FLIP_NONE);
}
GameObject::GameObject(std::string state,Model* model,float width,float height,float positionX,float positionY,float velocityX,float velocityY,float accelerationX,float accelerationY,bool rigid,bool is_static):collision_polygon(new CollisionPolygon(positionX,positionY,width,height)){
		static int object_num=0;
		GameObject::state=state;
		add_variable("position_x",positionX);
		add_variable("position_y",positionY);
		add_variable("velocity_x",velocityX);
		add_variable("velocity_y",velocityY);
		add_variable("acceleration_x",accelerationX);
		add_variable("acceleration_y",accelerationY);
		//GameObject::position = position;
		GameObject::model=model;
		//GameObject::velocity = Vector2D(0,0);
		//GameObject::acceleration = Vector2D(0,0);
		GameObject::width=width;
		GameObject::height=height;
		GameObject::rigid=rigid;
		GameObject::is_static=is_static;
		GameObject::object_id="object"+std::to_string(static_cast<long long>(object_num));
		object_num++;
		updated=false;
		is_alive=true;
	}
GameObject::GameObject(std::string state,Model* model,float width,float height,float positionX,float positionY,float velocityX,float velocityY,float accelerationX,float accelerationY,std::string object_id,bool rigid,bool is_static):collision_polygon(new CollisionPolygon(positionX,positionY,width,height)){
		static int object_num=0;
		GameObject::state=state;
		add_variable("position_x",positionX);
		add_variable("position_y",positionY);
		add_variable("velocity_x",velocityX);
		add_variable("velocity_y",velocityY);
		add_variable("acceleration_x",accelerationX);
		add_variable("acceleration_y",accelerationY);
		//GameObject::position = position;
		GameObject::model=model;
		//GameObject::velocity = Vector2D(0,0);
		//GameObject::acceleration = Vector2D(0,0);
		GameObject::width=width;
		GameObject::height=height;
		GameObject::rigid=rigid;
		GameObject::is_static=is_static;
		GameObject::object_id="object"+std::to_string(static_cast<long long>(object_num));
		object_num++;
		updated=false;
		is_alive=true;
	GameObject::object_id=object_id;
}
void GameObject::addEvent(Event* event){
	events.push_back(event);
	event->parent=this;
}
void GameObject::deleteOb(){
	GameObjectManager::Instance()->addObjectToDelete(object_id);
}