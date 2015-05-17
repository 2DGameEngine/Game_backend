#include "Game.h"
#include "GameObject.h"
#include <algorithm>
#include <cmath>
#include <string.h>
#include "FileManager.h"
#include "Camera.h"
#include <string>
#include <sstream>

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> internalL;
  std::stringstream ss(str); // Turn the string into a stream.
  std::string tok;
  std::cout<<"Split "<<str<<"=";
  while(std::getline(ss, tok, delimiter)) {
	  std::cout<<tok<<" ";
    internalL.push_back(tok);
  }
  std::cout<<"\n";
  return internalL;
}

float get_variable(std::string object_id,std::string variable_name){
	return GameObjectManager::Instance()->getObject(object_id)->return_variable_value(variable_name);
}

void set_variable(std::string object_id,std::string variable_name, float op2){
	GameObjectManager::Instance()->getObject(object_id)->change_variable(variable_name, op2);
}

float editorParserRec(std::map<std::string, retJSON> ast){
	struct retJSON tmpJSON;
	std::string operand;
	char *strFn;
	float op1, op2;
	tmpJSON = ast["0"];
	if(tmpJSON.type == "string"){
		std::cout<<tmpJSON.retVal.stringVal<<"\n";
		operand = tmpJSON.retVal.stringVal;
	}
	else
		return 0;
	tmpJSON = ast["1"];
	if(tmpJSON.type == "array" || tmpJSON.type == "object"){
		op1 = editorParserRec(tmpJSON.mapVal);
	}
	else if(tmpJSON.type == "string"){
		std::cout<<tmpJSON.retVal.stringVal<<"\n";
		std::vector<std::string> splitS = split(tmpJSON.retVal.stringVal, '.');
		op1 = get_variable(splitS[0], splitS[1]);
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
		std::cout<<tmpJSON.retVal.stringVal<<"\n";
		std::vector<std::string> splitS = split(tmpJSON.retVal.stringVal, '.');
		op2 = get_variable(splitS[0], splitS[1]);
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

bool editorParser(std::map<std::string, retJSON> ast){
	struct retJSON tmpJSON;
	std::string operand;
	char* strFn;
	float op1, op2;
	tmpJSON = ast["0"];
	if(tmpJSON.type == "string"){
		std::cout<<tmpJSON.retVal.stringVal<<"\n";
		operand = tmpJSON.retVal.stringVal;
	}
	else
		return false;
	tmpJSON = ast["1"];
	if(tmpJSON.type == "array" || tmpJSON.type == "object"){
		op1 = editorParserRec(tmpJSON.mapVal);
	}
	else if(tmpJSON.type == "string"){
		std::vector<std::string> splitS = split(tmpJSON.retVal.stringVal, '.');
		op1 = get_variable(splitS[0], splitS[1]);
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
		std::cout<<tmpJSON.retVal.stringVal<<"\n";
		std::vector<std::string> splitS = split(tmpJSON.retVal.stringVal, '.');
		op2 = get_variable(splitS[0], splitS[1]);
	}
	else if(tmpJSON.type == "int")
		op2 = tmpJSON.retVal.intVal;
	else if(tmpJSON.type == "float")
		op2 = tmpJSON.retVal.floatVal;
	if(operand=="Assign"){
		std::vector<std::string> splitS = split(ast["1"].retVal.stringVal, '.');
		set_variable(splitS[0], splitS[1], op2);
		return true;
	}
	else if(operand=="if"){
		if(op1==op2){
			tmpJSON = ast["3"];
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(operand=="ifL"){
		if(op1<op2){
			tmpJSON = ast["3"];
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(operand=="ifLE"){
		if(op1<=op2){
			tmpJSON = ast["3"];
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(operand=="ifG"){
		if(op1>op2){
			tmpJSON = ast["3"];
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	else if(operand=="ifGE"){
		if(op1>=op2){
			tmpJSON = ast["3"];
			if(tmpJSON.type == "array" || tmpJSON.type == "object"){
				return editorParser(tmpJSON.mapVal);
			}
		}
	}
	return false;
}

void editorEval(std::map<std::string, retJSON> ast){
	struct retJSON tmpJSON;
	for(std::map<std::string, retJSON>::iterator it = ast.begin(); it!=ast.end(); it++){
		tmpJSON=it->second;
		if(tmpJSON.type == "array" || tmpJSON.type == "object"){
			editorParser(tmpJSON.mapVal);
		}
	}
}

bool Game::init(const char* title,int xpos,int ypos,int width,int height, bool fullscreen){
	int flags=0;
	gravity=.1;
	if(fullscreen==true)
		flags=SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING)==0&&(m_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags))&&(m_pRenderer=SDL_CreateRenderer(m_pWindow,-1,0))&&(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) ==0)){
		std::cout<< "success\n";
		SDL_SetRenderDrawColor(m_pRenderer,255,255,0,255);

		camera = new Camera(500,500,Vector2D(50,50),"static","dude1",Vector2D(50,50));
		SDL_SetWindowSize(m_pWindow,camera->width,camera->height);
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
				mname.assign(tmpJSON.retVal.stringVal);
				std::cout<<"ModelName:"<<mname<<"\n";
			}
			Models[mname]=new Model();
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Sprite");
			if(tmpJSON.type == "string"){
				sprite+=tmpJSON.retVal.stringVal;
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
					statesName.assign(tmpJSON.retVal.stringVal);
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
				soundname.assign(tmpJSON.retVal.stringVal);
				std::cout<<"SoundName:"<<soundname<<"\n";
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "File");
			if(tmpJSON.type == "string"){
				soundfile+=tmpJSON.retVal.stringVal;
				std::cout<<"File:"<<soundfile<<"\n";
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Music");
			if(tmpJSON.type == "string"){
				soundtype=tmpJSON.retVal.stringVal;
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
		GameObject* go2;
		GameObject* go3;
		GameObject* go1;
		GameObject* go21;
		GameObject* go31;
		Event* e;
		source = "\.\.\\json\\objects";
		float width=0, height=0, pos_X=0, pos_Y=0,vel_X=0,vel_Y=0,acc_X=0,acc_Y=0;
		std::string obname = "", defaultAnim="",rigid_value="false", static_value="false";
		bool rigid=false, staticV=false;
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
				rigid_value.assign(tmpJSON.retVal.stringVal);
			if(rigid_value=="true")
				rigid=true;
			}
			staticV=false;
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Static");
			if(tmpJSON.type == "string"){
				static_value.assign(tmpJSON.retVal.stringVal);
			if(static_value=="true")
				staticV=true;
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "Name");
			if(tmpJSON.type == "string"){
				obname.assign(tmpJSON.retVal.stringVal);
			}
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "ModelName");
			if(tmpJSON.type == "string"){
				mname.assign(tmpJSON.retVal.stringVal);
			}
			std::cout<<"ModelName:"<<mname<<"\n";
			tmpJSON = FileManager::Instance()->returnVALUE(it->second, "ModelDefaultAnim");
			if(tmpJSON.type == "string"){
				defaultAnim.assign(tmpJSON.retVal.stringVal);
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
					defaultAnim.assign(itt->second.retVal.stringVal);
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