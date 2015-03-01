#include <SDL.h>
#include <stdio.h>
#include <Windows.h>
#include "Game.h"
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include <Windows.h>
#include "Game.h"
#include <iostream>
const int FPS=60;
const int DELAY_TIME=1000.0f/FPS;

int main(int argc,char* argv[]){
	UINT32 frameStart,frameTime;
	AllocConsole();
	freopen("CON","w",stdout);
	TheGame::Instance()->init("new",100,100,800,600,false);
	while(TheGame::Instance()->running()){
		frameStart=SDL_GetTicks();
		TheGame::Instance()->update();
		TheGame::Instance()->render();
		frameTime=SDL_GetTicks()-frameStart;
		if(frameTime<DELAY_TIME){
			SDL_Delay((int)(DELAY_TIME-frameTime));
		}
	}
	TheGame::Instance()->clean();
	return 0;
}