#ifndef _PARSER_
#define _PARSER_
#include <map>
#include "FileManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include <iostream>
class Parser{
	class FileManager;
public:
	
	float get_variable(std::string,std::string);
	void set_variable(std::string,std::string,float);
	float editorParserRec(std::map<std::string,retJSON>);
	bool editorParser(std::map<std::string,retJSON>);
	bool editorParserExt(std::map<std::string,retJSON>);
	void editorEval(std::map<std::string,retJSON>);
	static Parser* Instance(){
		if(s_pInstance==0){
			s_pInstance=new Parser();
		}
		return s_pInstance;
	}
private:
	static Parser* s_pInstance;
};
#endif