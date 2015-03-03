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
		dude_sasi= new GameObject("standing",dude,500/6,378/3);
		dude_sasi->add_state_animation_pair("standing","standing");
		dude_sasi->add_state_animation_pair("walk_right","walk_right");
		dude_sasi->add_state_animation_pair("walk_left","walk_left");
		chick_sarala= new GameObject("standing",dude,50,50);
		chick_sarala->add_state_animation_pair("standing","standing");
		chick_sarala->add_state_animation_pair("walk_right","walk_right");
		chick_sarala->add_state_animation_pair("walk_left","walk_left");
		return true;
	}
	else{
		std::cout<<"failed\n";
		return false;
	}
}
void Game::render(){
	SDL_RenderClear(m_pRenderer);
	dude_sasi->draw();
	chick_sarala->draw();
	SDL_RenderPresent(m_pRenderer);
}
void Game::update(){
	InputHandler::Instance()->update();
	dude_sasi->update();
	chick_sarala->update();
}
void Game::clean(){
	std::cout<<"cleaning\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
Game* Game::s_pInstance=0;