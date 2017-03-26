/* Fact.cpp */
#include "../headers/Fact.h"

/* 
 * Constructor that sets the data, as well as the fact name
 */
Fact::Fact(std::vector<std::vector<std::string>> p_data){
	data = p_data;
	factName = p_data[0][0];
}

/* Getter functions */

std::string Fact::getFactName(){
	return factName;
}		

std::vector<std::vector<std::string>> Fact::getFact(){
	return data;
}

Fact::~Fact(){}
