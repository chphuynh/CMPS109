#include "../headers/NonExistentEntry.h"

ExistenceException::ExistenceException(const std::string & p_entry){
	exception_str = "Non Existence Exception: ";
	entry = p_entry;
}

void ExistenceException::printException(){
	std::cout << exception_str << entry << std::endl;
}

ExistenceException::~ExistenceException(){

}