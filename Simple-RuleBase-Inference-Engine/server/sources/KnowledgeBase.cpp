/* KnowledgeBase.cpp */
#include "../headers/KnowledgeBase.h"

/*
 * Default constructor of KnowledgeBase.  Used when 
 * creating an empty KnowledgBase.
 */
KnowledgeBase::KnowledgeBase(){
}

/*
 * Parameterized Default constructor
 * Used when a KnowledgeBase is substantiated
 * with pre-condifgured data
 */
KnowledgeBase::KnowledgeBase(std::vector<Fact*> p_items){
	for(int i = 0; i < p_items.size(); ++i){
		addContent(p_items[i]);
	}
}

/*
 * getkeys
 * This will return a vector containing all
 * keys in data
 */
std::vector<std::string> KnowledgeBase::getKeys() {
	std::vector<std::string> keys;

	for(const auto &pair : data) {
		keys.push_back(pair.first);
	}

	return keys;
}


/* 
 * addContent will take a ptr to a Fact obj
 * and try to insert it in a vector with the same fact name.
 * Complexity: O(m) where m = the number of similar facts 
 * already in the KB
 */
bool KnowledgeBase::addContent(Fact * p_item){
	std::string factName = p_item->getFactName();
	if(data.count(factName) == 0){
		data[factName].push_back(p_item);
		return true;
	}else if(check(data[factName], p_item) == false){
		data[factName].push_back(p_item);
		return true;
	}
	return false;
}

/* 
 * getContent 
 * Returns a vector of all facts with the factname: p_name
 */ 
std::vector<Fact*> KnowledgeBase::getContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		return data[p_name];
	}
	return std::vector<Fact*>();
		
}

/*
 * dropcontent
 * Checks if p_name is a fact in KB, then calls Fact 
 * destructor on all facts associated with p_name
 * and removes key entry from map.
 */ 
bool KnowledgeBase::dropContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		for(int i = 0; i < data[p_name].size(); ++i){
			data[p_name][i]->~Fact();
		}

		data.erase(p_name);

		if(data.count(p_name) == 0){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

/*
 * check
 * internal method that returns true if a fact exists in a given vector
 */
bool KnowledgeBase::check(std::vector<Fact*> data, Fact * f2){
	std::vector<std::vector<std::string>> cmp = f2->getFact();
	for(int i = 0; i < data.size(); ++i){
		if(data[i]->getFact() == cmp){
			return true;
		}
	}
	return false;
}



/*
 * ~KnowledgeBase()
 * Iterates through map and calls fact destructor on all facts
 */
KnowledgeBase::~KnowledgeBase(){
	for ( auto i = data.begin(); i != data.end(); ++i ){
		for(int j = 0; j < i->second.size(); j++){
			i->second[j]->~Fact();
		}
	}
}

