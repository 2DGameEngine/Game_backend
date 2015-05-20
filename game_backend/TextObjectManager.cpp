#include "TextObjectManager.h"
void TextObjectManager::addObject(TextObject* text_object){
	text_object_list.push_back(text_object);
	//id_object_map[text_object->object_id]=text_object;
}
TextObject* TextObjectManager::getObject(std::string object_id){
	for(std::vector<int>::size_type i = 0; i != text_object_list.size(); i++) {
		if(!text_object_list[i]->id.compare(object_id)){
			return text_object_list[i];
		}
	}
}
void TextObjectManager::addObjectToDelete(std::string object_id){
	objects_to_delete.push_back(TextObjectManager::getObject(object_id));
}
TextObjectManager* TextObjectManager::s_pInstance=0;