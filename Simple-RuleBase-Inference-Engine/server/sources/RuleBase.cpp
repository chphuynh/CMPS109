/* RuleBase.cpp */
#include "../headers/RuleBase.h"

/* Default RuleBase Constructor */
RuleBase::RuleBase(){}

/*
 * Parameterized Constructor. Takes in a vector of 
 * rules and will add all to RuleBase. 
 */
RuleBase::RuleBase(std::vector<Rule *> p_items){
	for(int i = 0; i < p_items.size(); ++i){
		addContent(p_items[i]);
	}
}

/*
 * getkeys
 * This will return a vector containing all
 * keys in data
 */
std::vector<std::string> RuleBase::getKeys() {
	std::vector<std::string> keys;

	for(const auto &pair : data) {
		keys.push_back(pair.first);
	}

	return keys;
}

/*
 * addContent
 * This will take a Rule Object in and attempt
  * to add it to the RuleBase.
 */
bool RuleBase::addContent(Rule * p_item){
	std::string ruleName = p_item->getRuleName();
	if(data.count(ruleName) == 0){
		data[ruleName] = p_item;
		return true;
	}
	return false;
}

/*
 * getContent
 * This will take in a string p_name and attempt to
 * return a copy of a Rule Object.  If the Rule
 * doesn't exist in the RuleBase, a ExistenceException 
 * will be thrown. 
 */
Rule RuleBase::getContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		return *data[p_name];
	}
	throw ExistenceException(p_name);
}

/*
 * dropContent
 * Returns a bool on the success or failure of 
 * attempting to drop a ruel from the RuleBase.
 * Will return 0 if failed or rule DNE. 1 on 
 * success.
 */
bool RuleBase::dropContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		data[p_name]->~Rule();
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
 * RuleBase Destructor
 * Will Iterate through each Rule in the RuleBase
 * and will call its destructor.
 */
RuleBase::~RuleBase(){
	for ( auto i = data.begin(); i != data.end(); ++i ){
			i->second->~Rule();
	}
}