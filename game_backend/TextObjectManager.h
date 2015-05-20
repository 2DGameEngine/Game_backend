#ifndef _TEXTOBJECTMANAGER_
#define _TEXTOBJECTMANAGER_
#include "TextObject.h"
#include <vector>
#include <map>
class TextObject;
class TextObjectManager{
public:
	static TextObjectManager* Instance(){
		if(s_pInstance==0){
			s_pInstance=new TextObjectManager();
		}
		return s_pInstance;
	}
	void addObject(TextObject*);
	 std::vector<TextObject*> &getObjectList() {
		return text_object_list;
	}
	 std::vector<TextObject*> &getObjectsToDeleteList() {
		return objects_to_delete;
	}
	TextObject* getObject(std::string);
	void addObjectToDelete(std::string);
private:
	std::vector<TextObject*> text_object_list;
	static TextObjectManager* s_pInstance;
	std::map <std::string,TextObject*> id_object_map;
	std::vector<TextObject*> objects_to_delete;
};
#endif