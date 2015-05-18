#include "Parser.h"
#include <string>
#include <sstream>

float get_variable(std::string object_id,std::string variable_name){
	return GameObjectManager::Instance()->getObject(object_id)->return_variable_value(variable_name);
}

void set_variable(std::string object_id,std::string variable_name, float op2){
	GameObjectManager::Instance()->getObject(object_id)->change_variable(variable_name, op2);
}
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
	else if(operand=="Play_Sound"){
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
bool editorParserExt(std::map<std::string, retJSON> ast){
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
	if(operand=="if"){
		return (op1==op2);
		}
	else if(operand=="ifL"){
		return (op1<op2);
			}
	else if(operand=="ifLE"){
		return (op1<=op2);
	}
	else if(operand=="ifG"){
		return (op1>op2);
	}
	else if(operand=="ifGE"){
		return (op1>=op2);
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
Parser* Parser::s_pInstance=0;