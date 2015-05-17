#include "Game.h"
#include "GameObject.h"
#include <algorithm>
#include <cmath>
#include "Camera.h"
bool Game::init(const char* title,int xpos,int ypos,int width,int height, bool fullscreen){
	int flags=0;
	if(fullscreen==true)
		flags=SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING)==0&&(m_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags))&&(m_pRenderer=SDL_CreateRenderer(m_pWindow,-1,0))&&(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) ==0)){
		std::cout<< "success\n";
		SDL_SetRenderDrawColor(m_pRenderer,255,255,0,255);
		camera = new Camera(500,500,Vector2D(50,50),"dynamic","dude1",Vector2D(50,50));
		m_bRunning=true;
		SDL_SetWindowSize(m_pWindow,camera->width,camera->height);
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
		Event* e;

		
			go=new GameObject("standing",dude,500/6,378/3,Vector2D(20,20),"dude1",false);
			go2=new GameObject("standing",dude,500/6,378/3,Vector2D(400,0),"dude2",false);
			
			GameObjectManager::Instance()->addObject(go2);
			GameObjectManager::Instance()->addObject(go);
			go2->add_state_animation_pair("standing","standing");
			go2->add_state_animation_pair("walk_left","walk_left");

		Sound* s=new Sound("effect");
		s->load("assets/footsteps-4.wav");
		Sound* s2=new Sound("effect");
		s2->load("assets/a.wav");
		SoundManager::Instance()->addSound(s,"walking_sound");
		SoundManager::Instance()->addSound(s2,"walking_sound1");
		

			go->add_state_animation_pair("standing","standing");
			go->add_state_animation_pair("walk_right","walk_right");
			go->add_state_animation_pair("walk_left","walk_left");
			e= new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_D);
			e->addAction(new Action("set_velocity_x",go,4));
			e->addAction(new Action("set_state",go,"walk_right"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_A);
			e->addAction(new Action("set_velocity_x",go,-4));
			e->addAction(new Action("set_state",go,"walk_left"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_D);
			e->addAction(new Action("set_velocity_x",go2,-4));
			e->addAction(new Action("set_state",go2,"walk_left"));
			go2->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_W);
			e->addAction(new Action("set_velocity_y",go,-4));
			e->addAction(new Action("set_state",go,"walk_left"));
			e->addAction(new Action("play_sound","walking_sound1"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_S);
			e->addAction(new Action("set_velocity_y",go,2));
			e->addAction(new Action("set_state",go,"walk_left"));
			e->addAction(new Action("play_sound","walking_sound"));
			go->addEvent(e);

			e=new Event();
			e->setEvent(COLLISION,"dude1");
			e->addAction(new Action("set_state",go2,"walk_left"));
			e->addAction(new Action("play_sound","walking_sound"));
			go2->addEvent(e);
			
		


			
		
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
		GameObjectManager::Instance()->getObjectList()[i]->draw();
	}
	SDL_RenderPresent(m_pRenderer);
}
void Game::update(){
	InputHandler::Instance()->update();
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size()&&GameObjectManager::Instance()->getObjectList()[i]->updated==false; i++) {
		GameObjectManager::Instance()->getObjectList()[i]->defaultUpdate();
	}
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObjectManager::Instance()->getObjectList()[i]->update(false);
	}

	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObjectManager::Instance()->getObjectList()[i]->update(true);
	}
	
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObjectManager::Instance()->getObjectList()[i]->updated=false;
	}
	collisionResolution();
}
void Game::clean(){
	std::cout<<"cleaning\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::collisionResolution(){
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObject* go1=GameObjectManager::Instance()->getObjectList()[i];
		if(go1->rigid==true)
			continue;
		for(std::vector<int>::size_type j = 0; j != i; j++) {
			GameObject* go2=GameObjectManager::Instance()->getObjectList()[j];
			if(go2->rigid==true)
				continue;
			if(go1==go2)
				continue;
			if(CollisionManager::Instance()->isColliding(go1->collision_polygon,go2->collision_polygon)){
				go1->translateX(-go1->velocity.getX());
				go2->translateX(-go2->velocity.getX());
				go1->translateY(-go1->velocity.getY());
				go2->translateY(-go2->velocity.getY());
			}
		}
	}
}
Game* Game::s_pInstance=0;