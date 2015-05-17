#include <SDL.h>
#include <stdio.h>
#include <Windows.h>
#include "Game.h"
#include "FileManager.h"
#include <iostream>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS=60;
const int DELAY_TIME=1000.0f/FPS;

int main(int argc,char* argv[]){
	UINT32 frameStart,frameTime;
	AllocConsole();
	freopen("CON","w",stdout);
	struct retJSON GameJSON, tmpJSON;
	GameJSON = FileManager::Instance()->readJSON("\.\.\\Game.json");
	int width=640, height=480;

	std::string gname = ""; 
	tmpJSON = FileManager::Instance()->returnVALUE(GameJSON, "Width");
	if(tmpJSON.type == "int"){
		width = tmpJSON.retVal.intVal;
	}
	tmpJSON = FileManager::Instance()->returnVALUE(GameJSON, "Height");
	if(tmpJSON.type == "int"){
		height = tmpJSON.retVal.intVal;
	}
	tmpJSON = FileManager::Instance()->returnVALUE(GameJSON, "Name");
	if(tmpJSON.type == "string"){
		gname.assign(tmpJSON.retVal.stringVal);
	}
	std::cout<<width<<" "<<height<<" "<<gname;
	TheGame::Instance()->init(gname.c_str(),100,100,width,height,false);
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