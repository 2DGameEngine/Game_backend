#include "Game.h"
#include "GameObject.h"
#include <algorithm>
#include <cmath>
#include <string.h>
#include "FileManager.h"

float editorParserRec(std::map<std::string, retJSON> ast){
	struct retJSON tmpJSON;
	std::string operand, strFn;
	float op1, op2;
	tmpJSON = ast["0"];
	if(tmpJSON.type == "string"){
		operand = tmpJSON.retVal.stringVal;
	}
	else
		return 0;
	tmpJSON = ast["1"];
	if(tmpJSON.type == "array" || tmpJSON.type == "object"){
		op1 = editorParserRec(tmpJSON.mapVal);
	}
	else if(tmpJSON.type == "string"){
		strFn = tmpJSON.retVal.stringVal;
		op1 = set_variable(strtok(strFn, "."), strtok(NULL, "."));
	}
	else if(tmpJSON.type == "int")
		op1 = tmpJSON.retVal.intVal;
	else if(tmpJSON.type == "float")
		op1 = tmpJSON.retVal.floatVal;
	tmpJSON = ast["2"];
	if(tmpJSON.type == "array" || tmpJSON.type == "object"){
		op2 = editorParserRec(tmpJSON.mapVal);
	}
	else if(tmpJSON.type == "string"){
		strFn = tmpJSON.retVal.stringVal;
		op2 = set_variable(strtok(strFn, "."), strtok(NULL, "."));
	}
	else if(tmpJSON.type == "int")
		op2 = tmpJSON.retVal.intVal;
	else if(tmpJSON.type == "float")
		op2 = tmpJSON.retVal.floatVal;
	if(operand == "/"){
		return (op1/op2);
	}
	else if(operand == "*"){
		return (op1*op2);
	}
	else if(operand == "+"){
		return (op1+op2);
	}
	else if(operand == "-"){
		return (op1-op2);
	}
	return 0;
}

bool editorParser(struct retJSON ast){
	struct retJSON tmpJSON;
	std::string operand;
	float op1, op2;
	tmpJSON = FileManager::Instance()->returnVALUE(ast, "0");
	if(tmpJSON.type == "string"){
		operand = tmpJSON.retVal.stringVal;
	}
	else
		return false;
	tmpJSON = FileManager::Instance()->returnVALUE(ast, "1");
	if(tmpJSON.type == "array" || tmpJSON.type == "object"){
		op1 = editorParserRec(tmpJSON.mapVal);
	}
	else if(tmpJSON.type == "string"){
		strFn = tmpJSON.retVal.stringVal;
		op1 = set_variable(strtok(strFn, "."), strtok(NULL, "."));
	}
	else if(tmpJSON.type == "int")
		op1 = tmpJSON.retVal.intVal;
	else if(tmpJSON.type == "float")
		op1 = tmpJSON.retVal.floatVal;
	tmpJSON = FileManager::Instance()->returnVALUE(ast, "2");
	if(tmpJSON.type == "array" || tmpJSON.type == "object"){
		op2 = editorParserRec(tmpJSON.mapVal);
	}
	else if(tmpJSON.type == "string"){
		strFn = tmpJSON.retVal.stringVal;
		op2 = set_variable(strtok(strFn, "."), strtok(NULL, "."));
	}
	else if(tmpJSON.type == "int")
		op2 = tmpJSON.retVal.intVal;
	else if(tmpJSON.type == "float")
		op2 = tmpJSON.retVal.floatVal;
	if(mapVal["0"]=="Assign"){
		strFn = tmpJSON.retVal.stringVal;
		set_variable(strtok(strFn, "."), strtok(NULL, "."), op2);
		return true;
	}
	else if(mapVal["0"]=="if"){
		if(op1==op2){
			tmpJSON = FileManager::Instance()->returnVALUE(ast, "3");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(mapVal["0"]=="ifL"){
		if(op1<op2){
			tmpJSON = FileManager::Instance()->returnVALUE(ast, "3");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(mapVal["0"]=="ifLE"){
		if(op1<=op2){
			tmpJSON = FileManager::Instance()->returnVALUE(ast, "3");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(mapVal["0"]=="ifG"){
		if(op1>op2){
			tmpJSON = FileManager::Instance()->returnVALUE(ast, "3");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(mapVal["0"]=="ifGE"){
		if(op1>=op2){
			tmpJSON = FileManager::Instance()->returnVALUE(ast, "3");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	return false;
}

bool Game::init(const char* title,int xpos,int ypos,int width,int height, bool fullscreen){
	int flags=0;
	if(fullscreen==true)
		flags=SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING)==0&&(m_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags))&&(m_pRenderer=SDL_CreateRenderer(m_pWindow,-1,0))&&(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) ==0)){
		std::cout<< "success\n";
		SDL_SetRenderDrawColor(m_pRenderer,255,255,0,255);
		m_bRunning=true;
		/*Model* dude=new Model();
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
		dude->addAnimation(new Animation("walk_left",seq3,.8));*/


		//Initializing Models from model jsons

		std::map<std::string, Model*> Models;
		std::map<int, retJSON> js;
		struct retJSON tmpJSON;
		float mwidth=0, mheight=0, seq_X=0, seq_Y=0, speed=0;
		std::string mname = "", sprite="", spriteLoc="", statesName="";
		std::string source = "\.\.\\json\\models";
		js = FileManager::Instance()->initializeObjects(source.c_str());
		for(std::map<int, retJSON>::const_iterator it = js.begin(); it != js.end(); ++it){
			mname="";
			sprite="assets\\";
			mwidth=0;
			mheight=0;
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Name");
			if(tmpJSON.type == "string"){
				mname.assign(tmpJSON.stringVal);
				std::cout<<"ModelName:"<<mname<<"\n";
			}
			Models[mname]=new Model();
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Sprite");
			if(tmpJSON.type == "string"){
				sprite+=tmpJSON.stringVal;
				std::cout<<"Sprite:"<<sprite<<"\n";
			}
			Models[mname]->load_texture(sprite);
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Width");
			if(tmpJSON.type == "int"){
				mwidth = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				mwidth = tmpJSON.retVal.floatVal;
			}
			std::cout<<"Width:"<<mwidth<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Height");
			if(tmpJSON.type == "int"){
				mheight = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				mheight = tmpJSON.retVal.floatVal;
			}
			std::cout<<"Height:"<<mheight<<"\n";
			Models[mname]->set_width_and_height_frame(mwidth,mheight);
			std::map<std::string, retJSON> mapVal, seqVal;
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "modelStates");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				mapVal = tmpJSON.mapVal;
			}
			for(std::map<std::string, retJSON>::const_iterator itt = mapVal.begin(); itt != mapVal.end(); ++itt){
				statesName="";
				speed=0;
				tmpJSON = FileManager::Instance()->returnVALUE(itt->second, "Name");
				if(tmpJSON.type == "string"){
					statesName.assign(tmpJSON.stringVal);
				}
				std::cout<<"StateName:"<<statesName<<"\n";
				tmpJSON = FileManager::Instance()->returnVALUE(itt->second, "Speed");
				if(tmpJSON.type == "int"){
					speed = tmpJSON.retVal.intVal;
				}
				else if(tmpJSON.type == "float"){
					speed = tmpJSON.retVal.floatVal;
				}
				std::cout<<"Speed:"<<speed<<"\n";
				tmpJSON = FileManager::Instance()->returnVALUE(itt->second, "Seq");
				if(tmpJSON.type == "array" || tmpJSON.type == "object"){
					seqVal = tmpJSON.mapVal;
				}
				std::vector<std::pair<int,int>> seq1;
				for(std::map<std::string, retJSON>::const_iterator iitt = seqVal.begin(); iitt != seqVal.end(); ++iitt){
					tmpJSON = FileManager::Instance()->returnVALUE(iitt->second, "X");
					if(tmpJSON.type == "int"){
						seq_X = tmpJSON.retVal.intVal;
					}
					else if(tmpJSON.type == "float"){
						seq_X = tmpJSON.retVal.floatVal;
					}
					std::cout<<"X:"<<seq_X<<"\n";
					tmpJSON = FileManager::Instance()->returnVALUE(iitt->second, "Y");
					if(tmpJSON.type == "int"){
						seq_Y = tmpJSON.retVal.intVal;
					}
					else if(tmpJSON.type == "float"){
						seq_Y = tmpJSON.retVal.floatVal;
					}
					std::cout<<"Y:"<<seq_Y<<"\n";
					seq1.push_back(std::make_pair(seq_X,seq_Y));
				}
				Models[mname]->addAnimation(new Animation(statesName,seq1,speed));
			}
		}


		//Initializing the sound

		std::string soundname="", soundfile="", soundtype="";
		source = "\.\.\\json\\sounds";
		Sound *s;
		js = FileManager::Instance()->initializeObjects(source.c_str());
		for(std::map<int, retJSON>::const_iterator it = js.begin(); it != js.end(); ++it){
			soundname="";
			soundfile="assets\\";
			soundtype="effect";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Name");
			if(tmpJSON.type == "string"){
				soundname.assign(tmpJSON.stringVal);
				std::cout<<"SoundName:"<<soundname<<"\n";
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "File");
			if(tmpJSON.type == "string"){
				soundfile+=tmpJSON.stringVal;
				std::cout<<"File:"<<soundfile<<"\n";
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Music");
			if(tmpJSON.type == "string"){
				soundtype=tmpJSON.stringVal;
				std::cout<<"soundtype:"<<soundtype<<"\n";
			}
			s = new Sound(soundtype);
			s->load(soundfile);
			SoundManager::Instance()->addSound(s,soundname);
		}
		/*Sound* s=new Sound("effect");
		s->load("assets/footsteps-4.wav");
		Sound* s2=new Sound("effect");
		s2->load("assets/a.wav");
		SoundManager::Instance()->addSound(s,"walking_sound");
		SoundManager::Instance()->addSound(s2,"walking_sound1");*/


		//Initializing the objects from object json

		GameObject* go;
		Event* e;
		source = "\.\.\\json\\objects";
		float width=0, height=0, pos_X=0, pos_Y=0,vel_X=0,vel_Y=0,acc_X=0,acc_Y=0;
		std::string obname = "", defaultAnim="",rigid_value="false";
		bool rigid=false;
		js = FileManager::Instance()->initializeObjects(source.c_str());
		for(std::map<int, retJSON>::const_iterator it = js.begin(); it != js.end(); ++it){
			
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Width");
			if(tmpJSON.type == "int"){
				width = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				width = tmpJSON.retVal.floatVal;
			}
			std::cout<<"Width:"<<width<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Height");
			if(tmpJSON.type == "int"){
				height = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				height = tmpJSON.retVal.floatVal;
			}
			std::cout<<"height:"<<height<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "pos_X");
			if(tmpJSON.type == "int"){
				pos_X = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				pos_X = tmpJSON.retVal.floatVal;
			}
			std::cout<<"X:"<<pos_X<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "pos_Y");
			if(tmpJSON.type == "int"){
				pos_Y = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				pos_Y = tmpJSON.retVal.floatVal;
			}
			std::cout<<"Y:"<<pos_Y<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "vel_X");
			if(tmpJSON.type == "int"){
				vel_X = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				vel_X = tmpJSON.retVal.floatVal;
			}
			std::cout<<"X:"<<vel_X<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "vel_Y");
			if(tmpJSON.type == "int"){
				vel_Y = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				vel_Y = tmpJSON.retVal.floatVal;
			}
			std::cout<<"Y:"<<vel_Y<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "acc_X");
			if(tmpJSON.type == "int"){
				acc_X = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				acc_X = tmpJSON.retVal.floatVal;
			}
			std::cout<<"X:"<<acc_X<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "acc_Y");
			if(tmpJSON.type == "int"){
				acc_Y = tmpJSON.retVal.intVal;
			}
			else if(tmpJSON.type == "float"){
				acc_Y = tmpJSON.retVal.floatVal;
			}
			std::cout<<"Y:"<<acc_Y<<"\n";
			rigid=false;
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Rigid");
			if(tmpJSON.type == "string"){
				rigid_value.assign(tmpJSON.stringVal);
			if(rigid_value=="true")
				rigid=true;
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Name");
			if(tmpJSON.type == "string"){
				obname.assign(tmpJSON.stringVal);
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "ModelName");
			if(tmpJSON.type == "string"){
				mname.assign(tmpJSON.stringVal);
			}
			std::cout<<"ModelName:"<<mname<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "ModelDefaultAnim");
			if(tmpJSON.type == "string"){
				defaultAnim.assign(tmpJSON.stringVal);
			}
			std::cout<<"defaultAnim:"<<defaultAnim<<"\n";
			go=new GameObject(defaultAnim, Models[mname], width, height, pos_X, pos_Y, vel_X, vel_Y, acc_X, acc_Y, obname.c_str(), rigid);
			std::map<std::string, retJSON> mapVal;
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "ModelListAnim");
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				mapVal = tmpJSON.mapVal;
			}
			for(std::map<std::string, retJSON>::const_iterator itt = mapVal.begin(); itt != mapVal.end(); ++itt){
				if(itt->second.type == "string"){
					defaultAnim.assign(itt->second.stringVal);
				}
				std::cout<<"AnimState:"<<defaultAnim<<"\n";
				go->add_state_animation_pair(defaultAnim,defaultAnim);
			}
			/*go->add_state_animation_pair("standing","standing");*/
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




		GameObject* go;
		GameObject* go2;
		Event* e;
		
			go=new GameObject("standing",dude,500/6,378/3,Vector2D(20,20),"dude1",true);
			go2=new GameObject("standing",dude,500/6,378/3,Vector2D(400,0),"dude2",true);
			
			GameObjectManager::Instance()->addObject(go2);
			GameObjectManager::Instance()->addObject(go);
			go2->add_state_animation_pair("standing","standing");
			go2->add_state_animation_pair("walk_left","walk_left");

		

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
			e->addAction(new Action("delete_object",go));
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
		if(GameObjectManager::Instance()->getObjectList()[i]->is_alive==false)
			continue;
		GameObjectManager::Instance()->getObjectList()[i]->draw();
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
		GameObjectManager::Instance()->getObjectList()[i]->updated=false;
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
	for(std::vector<int>::size_type i = 0; i != GameObjectManager::Instance()->getObjectList().size(); i++) {
		GameObject* go1=GameObjectManager::Instance()->getObjectList()[i];
		if(go1->rigid==true||go1->is_alive==false)
			continue;
		for(std::vector<int>::size_type j = 0; j != i; j++) {
			GameObject* go2=GameObjectManager::Instance()->getObjectList()[j];
			if(go2->rigid==true||go2->is_alive==false)
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
void Game::deleteObjects(){
	std::vector<GameObject*>::iterator it;
	for ( it = GameObjectManager::Instance()->getObjectsToDeleteList().begin(); it != GameObjectManager::Instance()->getObjectsToDeleteList().end();it++ ){
		(*it)->is_alive=false;
	}
	GameObjectManager::Instance()->getObjectsToDeleteList().clear();
}
Game* Game::s_pInstance=0;