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
		player= new GameObject("flying",128,55);
		player->loadSprite("assets/helicopter.png");
		std::vector<int> seq;
		seq.push_back(1);
		seq.push_back(2);
		seq.push_back(2);
		seq.push_back(1);
		player->define_animation("flying",seq);
		return true;
	}
	else{
		std::cout<<"failed\n";
		return false;
	}
}
void Game::render(){
	SDL_RenderClear(m_pRenderer);
	player->draw();
	SDL_RenderPresent(m_pRenderer);
}
void Game::update(){
	player->update();
}
void Game::clean(){
	std::cout<<"cleaning\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
Game* Game::s_pInstance=0;