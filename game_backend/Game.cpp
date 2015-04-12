#include "Game.h"
#include "GameObject.h"
bool Game::init(const char* title,int xpos,int ypos,int width,int height, bool fullscreen){
	int flags=0;
	if(fullscreen==true)
		flags=SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING)==0&&(m_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags))&&(m_pRenderer=SDL_CreateRenderer(m_pWindow,-1,0))){
		std::cout<< "success\n";
		SDL_SetRenderDrawColor(m_pRenderer,255,255,0,255);
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
		Event* e;
		for(int i=0;i<50;i++){
			go=new GameObject("standing",dude,500/6,378/3,Vector2D((i*500/6 +5)%600,(i*500/6 +5)/600*378/3));
			go->add_state_animation_pair("standing","standing");
			go->add_state_animation_pair("walk_right","walk_right");
			go->add_state_animation_pair("walk_left","walk_left");
			e= new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_D);
			e->addAction(new Action("set_velocity",go,Vector2D(1,0)));
			e->addAction(new Action("set_state",go,"walk_right"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_A);
			e->addAction(new Action("set_velocity",go,Vector2D(-1,0)));
			e->addAction(new Action("set_state",go,"walk_left"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_W);
			e->addAction(new Action("set_velocity",go,Vector2D(0,-1)));
			e->addAction(new Action("set_state",go,"walk_left"));
			go->addEvent(e);
			e=new Event();
			e->setEvent(BUTTON_CLICK,SDL_SCANCODE_S);
			e->addAction(new Action("set_velocity",go,Vector2D(0,2)));
			e->addAction(new Action("set_state",go,"walk_left"));
			go->addEvent(e);
			GameObjectManager::Instance()->addObject(go);
		}

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
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObjectManager::Instance()->getObjectList()[i]->update();
	}
}
void Game::clean(){
	std::cout<<"cleaning\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
Game* Game::s_pInstance=0;