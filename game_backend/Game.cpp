#include "Game.h"
#include "GameObject.h"
#include <algorithm>
#include <cmath>
#include "SDL_ttf.h"
#include "Camera.h"
bool Game::init(const char* title,int xpos,int ypos,int width,int height, bool fullscreen){
	int flags=0;
	gravity=.1;
	if(fullscreen==true)
		flags=SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING)==0&&(m_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags))&&(m_pRenderer=SDL_CreateRenderer(m_pWindow,-1,0))&&(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) ==0)&&(TTF_Init() != -1)){
		std::cout<< "success\n";
		SDL_SetRenderDrawColor(m_pRenderer,255,255,0,255);

		camera = new Camera(1000,1000,Vector2D(50,50),"dynamic","dude1",Vector2D(50,50));

		TextObject * test = new TextObject(Vector2D(600,200),"test","Feathergun","assets/monofonto.ttf",40);
		TextObjectManager::Instance()->addObject(test);


		m_bRunning=true;
		
		Model* dude=new Model();
		dude->load_texture("assets/dude.png");
		dude->set_width_and_height_frame(500/6,378/3);
		std::vector<std::pair<int,int>> seq1;
		seq1.push_back(std::make_pair(3,1));
		seq1.push_back(std::make_pair(3,2));
		std::vector<std::pair<int,int>> seq2;
		seq2.push_back(std::make_pair(1,1));
		seq2.push_back(std::make_pair(1,2));
		seq2.push_back(std::make_pair(1,3));
		seq2.push_back(std::make_pair(1,4));
		seq2.push_back(std::make_pair(1,5));
		seq2.push_back(std::make_pair(1,6));
		std::vector<std::pair<int,int>> seq3;
		seq3.push_back(std::make_pair(2,1));
		seq3.push_back(std::make_pair(2,2));
		seq3.push_back(std::make_pair(2,3));
		seq3.push_back(std::make_pair(2,4));
		seq3.push_back(std::make_pair(2,5));
		seq3.push_back(std::make_pair(2,6));
		dude->addAnimation(new Animation("standing",seq1,.1));
		dude->addAnimation(new Animation("walk_right",seq2,.8));
		dude->addAnimation(new Animation("walk_left",seq3,.8));
		
		GameObject* go;
		GameObject* go2;
		GameObject* go3;
		GameObject* go1;
		GameObject* go21;
		GameObject* go31;
		Event* e;

		


			go=new GameObject("standing",dude,500/6,378/3,20,20,0,0,0,0,"dude1",true,false);
			go2=new GameObject("standing",dude,500/6,378/3,200,200,0,0,0,0,"dude2",true,false);
			go3=new GameObject("standing",dude,5000/6,3780/3,0,200,0,0,0,0,"dude3",true,true);

			GameObjectManager::Instance()->addObject(go2);
			GameObjectManager::Instance()->addObject(go);
			GameObjectManager::Instance()->addObject(go3);
			go->add_state_animation_pair("standing","standing");
			go->add_state_animation_pair("walk_left","walk_left");
			go3->add_state_animation_pair("standing","standing");
			go2->add_state_animation_pair("walk_left","walk_left");
			go2->add_state_animation_pair("standing","standing");
			go1=new GameObject("standing",dude,500/6,378/3,600,-30,0,0,0,0,"dude4",true,false);
			go21=new GameObject("standing",dude,500/6,378/3,200,0,0,0,0,0,"dude5",true,false);
			go31=new GameObject("standing",dude,500/6,378/3,800,0,0,0,0,0,"dude6",true,false);
			GameObjectManager::Instance()->addObject(go21);
			//GameObjectManager::Instance()->addObject(go1);
			//GameObjectManager::Instance()->addObject(go31);
			
			go21->add_state_animation_pair("standing","standing");
			go31->add_state_animation_pair("standing","standing");
			go1->add_state_animation_pair("standing","standing");

		Sound* s=new Sound("effect");
		s->load("assets/footsteps-4.wav");
		Sound* s2=new Sound("effect");
		s2->load("assets/a.wav");
		SoundManager::Instance()->addSound(s,"walking_sound");
		SoundManager::Instance()->addSound(s2,"walking_sound1");
		go->add_variable("health",100);
			e= new Event();
			e->setEvent(VARIABLE_VALUE_TRIGGER,"dude1","health",80);
			e->addAction(new Action("play_sound","walking_sound1"));
			go->addEvent(e);
			
			go->add_state_animation_pair("standing","standing");
			go->add_state_animation_pair("walk_right","walk_right");
			go->add_state_animation_pair("walk_left","walk_left");
			e= new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_D);
			e->addAction(new Action("set_velocity_x","dude1",4));
			e->addAction(new Action("set_state","dude1","walk_right"));
			e->addAction(new Action("change_variable","dude1","health",80));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_A);
			e->addAction(new Action("set_velocity_x","dude1",-4));
			e->addAction(new Action("set_state","dude1","walk_left"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_D);
			e->addAction(new Action("set_velocity_x","dude2",-4));
			e->addAction(new Action("set_state","dude2","walk_left"));
			go2->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_W);
			e->addAction(new Action("set_velocity_y","dude1",-4));
			e->addAction(new Action("set_state","dude1","walk_left"));
			e->addAction(new Action("play_sound","walking_sound1"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_S);
			e->addAction(new Action("set_position_y","dude1",2));
			e->addAction(new Action("set_state","dude1","walk_left"));
			e->addAction(new Action("play_sound","walking_sound"));
			go->addEvent(e);

			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_P);
			e->addAction(new Action("change_text_visibility","test",true));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_O);
			e->addAction(new Action("change_text_visibility","test",false));
			go->addEvent(e);

			e=new Event();
			e->setEvent(BUTTON_RELEASE,SDL_SCANCODE_A);
			e->addAction(new Action("set_velocity_x","dude1",0));
			e->addAction(new Action("set_state","dude1","standing"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_RELEASE,SDL_SCANCODE_D);
			e->addAction(new Action("set_velocity_x","dude1",0));
			e->addAction(new Action("set_state","dude1","standing"));
			go->addEvent(e);
			


			e=new Event();
			e->setEvent(COLLISION,"dude5");

			e->addAction(new Action("set_velocity_x","dude1",-4));
			e->addAction(new Action("set_state","dude1","walk_left"));
			//e->addAction(new Action("play_sound","walking_sound1"));

			//e->addAction(new Action("delete_object",go));
			go->addEvent(e);
		return true;
	}
	else{
		std::cout<<"failed\n";
		return false;
	}
}
void Game::render(){
	SDL_RenderClear(m_pRenderer);
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		if(GameObjectManager::Instance()->getObjectList()[i]->is_alive==false)
			continue;
		GameObjectManager::Instance()->getObjectList()[i]->draw();
	}

	for(std::vector<int>::size_type i = 0; i != TextObjectManager::Instance()->getObjectList().size(); i++) {
		if(TextObjectManager::Instance()->getObjectList()[i]->visible==false)
			continue;
		TextObjectManager::Instance()->getObjectList()[i]->draw();
	}
		
	
	SDL_RenderPresent(m_pRenderer);
}
void Game::update(){
	InputHandler::Instance()->update();
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size()&&GameObjectManager::Instance()->getObjectList()[i]->updated==false; i++) {
		if(GameObjectManager::Instance()->getObjectList()[i]->is_alive==false)
			continue;
		GameObjectManager::Instance()->getObjectList()[i]->defaultUpdate();
	}
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		if(GameObjectManager::Instance()->getObjectList()[i]->is_alive==false)
			continue;
		GameObjectManager::Instance()->getObjectList()[i]->update(false);
	}
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		if(GameObjectManager::Instance()->getObjectList()[i]->is_alive==false)
			continue;
		GameObjectManager::Instance()->getObjectList()[i]->update(true);
	}
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		if(GameObjectManager::Instance()->getObjectList()[i]->is_alive==false)
			continue;
		GameObjectManager::Instance()->getObjectList()[i]->updatePosition();
	}
	
	collisionResolution();
	deleteObjects();
	
}

void Game::clean(){
	std::cout<<"cleaning\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::collisionResolution(){
	std::cout<<"checking"<<"\n";
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObject* go1=GameObjectManager::Instance()->getObjectList()[i];
			if(go1->rigid==false||go1->is_alive==false)
				continue;
		for(std::vector<int>::size_type j = 0; j != i; j++) {
			GameObject* go2=GameObjectManager::Instance()->getObjectList()[j];
			if(go2->rigid==false||go2->is_alive==false)
				continue;
			/*if(go1==go2)
				continue;*/
			std::cout<<go1->object_id+" checks "+go2->object_id<<"\n";
			if(CollisionManager::Instance()->isColliding(go1->collision_polygon,go2->collision_polygon)){
				std::cout<<go1->object_id+" collides "+go2->object_id<<"\n";
				
				float x_overlap=std::min(std::abs(go1->getPosition().getX()+go1->width-go2->getPosition().getX()),std::abs(go2->getPosition().getX()+go2->width-go1->getPosition().getX()));
				float y_overlap=std::min(std::abs(go1->getPosition().getY()+go1->height-go2->getPosition().getY()),std::abs(go2->getPosition().getY()+go2->height-go1->getPosition().getY()));
				if(x_overlap<y_overlap){
					GameObject* left_go;
					GameObject* right_go;
					if(go1->getPosition().getX()<go2->getPosition().getX()){
						left_go=go1;
						right_go=go2;
					}
					else{
						left_go=go2;
						right_go=go1;
					}
					if((right_go->is_static==true||right_go->getVelocity().getX()==0)&&left_go->getVelocity().getX()>0){
						left_go->translateX(-x_overlap);
						left_go->setVelocityX(0);
					}
					else if((right_go->is_static==true||right_go->getVelocity().getX()==0)&&left_go->getVelocity().getX()<0){
						left_go->translateX(-x_overlap);
						//left_go->setVelocityX(0);
					}
					else if((left_go->is_static==true||left_go->getVelocity().getX()==0)&&right_go->getVelocity().getX()>0){
						right_go->translateX(y_overlap);
					}
					else if((left_go->is_static==true||left_go->getVelocity().getX()==0)&&right_go->getVelocity().getX()<0){
						right_go->translateX(x_overlap);
						right_go->setVelocityX(0);
					}
					else if(left_go->velocity.getX()>0&&right_go->getVelocity().getX()<0){
						left_go->translateX(-left_go->getVelocity().getX());
						right_go->translateX(-right_go->getVelocity().getX());
						left_go->setVelocityX(0);
						right_go->setVelocityX(0);
					}
					else if(left_go->velocity.getX()<0&&right_go->getVelocity().getX()>0){
						
					}
					else if(left_go->velocity.getX()>0&&right_go->getVelocity().getX()>0){
						left_go->translateX(-x_overlap);
						left_go->setVelocityX(0);
					}
					else if(left_go->velocity.getX()<0&&right_go->getVelocity().getX()<0){
						right_go->translateX(x_overlap);
						right_go->setVelocityX(0);
					}
				}
				else{
					GameObject* top_go;
					GameObject* bot_go;
					if(go1->getPosition().getY()<go2->getPosition().getY()){
						top_go=go1;
						bot_go=go2;
					}
					else{
						bot_go=go1;
						top_go=go2;
					}
					if((bot_go->is_static==true||bot_go->getVelocity().getY()==0)&&top_go->getVelocity().getY()>0){
						top_go->translateY(-y_overlap);
						top_go->setVelocityY(0);
					}
					else if((bot_go->is_static==true||bot_go->getVelocity().getY()==0)&&top_go->getVelocity().getY()<0){
						top_go->translateY(-y_overlap);
					}
					else if((top_go->is_static==true||top_go->getVelocity().getY()==0)&&bot_go->getVelocity().getY()>0){
						bot_go->translateY(y_overlap);
					}
					else if((top_go->is_static==true||top_go->getVelocity().getY()==0)&&bot_go->getVelocity().getY()<0){
						bot_go->translateY(y_overlap);
						bot_go->setVelocityY(0);
					}
					else if(top_go->velocity.getY()>0&&bot_go->getVelocity().getY()<0){
						top_go->translateY(-top_go->getVelocity().getY());
						bot_go->translateY(-bot_go->getVelocity().getY());
						top_go->setVelocityY(0);
						bot_go->setVelocityY(0);
					}
					else if(top_go->velocity.getY()<0&&bot_go->getVelocity().getY()>0){
						
					}
					else if(top_go->velocity.getY()>0&&bot_go->getVelocity().getY()>0){
						top_go->translateY(-y_overlap);
						top_go->setVelocityY(0);
					}
					else if(top_go->velocity.getY()<0&&bot_go->getVelocity().getY()<0){
						bot_go->translateY(y_overlap);
						bot_go->setVelocityY(0);
					}
				}
				/*float go1_x_adj;
				float go2_x_adj;
				if(go1->velocity.getX()==go2->velocity.getX() && go1->velocity.getX()==0){
					go2_x_adj=go1_x_adj=0;
				}
				else{
					go1_x_adj=x_overlap*(std::abs(go1->velocity.getX())/(std::abs(go1->velocity.getX())+std::abs(go2->velocity.getX())));
					go2_x_adj=x_overlap-go1_x_adj;
				}
				
				float go1_y_adj;
				float go2_y_adj;
				if(go1->velocity.getY()==go2->velocity.getY() && go1->velocity.getY()==0){
					go2_y_adj=go1_y_adj=0;
				}
				else{
					go1_y_adj=y_overlap*(std::abs(go1->velocity.getY())/(std::abs(go1->velocity.getY())+std::abs(go2->velocity.getY())));
					go2_y_adj=y_overlap-go1_y_adj;
		
				}
				if(go1->position.getX()<go2->position.getX()){
					go1->translateX(-go1_x_adj);
					go2->translateX(go2_x_adj);
				}
				else{
					go2->translateX(-go2_x_adj);
					go1->translateX(go1_x_adj);
				}
				if(go1->position.getY()<go2->position.getY()){
					go1->translateY(-go1_y_adj);
					go2->translateY(go2_y_adj);
				}
				else{
					go2->translateY(-go2_y_adj);
					go1->translateY(go1_y_adj);
				}*/
			}
			
		}
	}
	std::cout<<"resolved"<<"\n";
}
void Game::deleteObjects(){
	std::vector<GameObject*>::iterator it;
	for ( it = GameObjectManager::Instance()->getObjectsToDeleteList().begin(); it != GameObjectManager::Instance()->getObjectsToDeleteList().end();it++ ){
		(*it)->is_alive=false;
	}
	GameObjectManager::Instance()->getObjectsToDeleteList().clear();
}
Game* Game::s_pInstance=0;