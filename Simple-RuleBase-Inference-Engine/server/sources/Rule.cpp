/* Rule.cpp */
#include "../headers/Rule.h"

Rule::Rule(std::vector<std::vector<std::string>> p_data){
	data = p_data;
	ruleName = data[0][0];
}

std::string Rule::getRuleName(){
	return ruleName;
}

std::vector<std::vector<std::string>> Rule::getRule(){
	return data;
}

Rule::~Rule(){

}