/* Fact.h */
#ifndef FACT_H
#define FACT_H

#include "common.h"

class Fact {
	private:
		/* factName(p1, p2...) */
		std::string factName;
		std::vector<std::vector<std::string>> data;
	public:
		Fact(std::vector<std::vector<std::string>> p_data);
		/* Getter methods */
		std::string getFactName();
		std::vector<std::vector<std::string>> getFact(); 		
		~Fact();
};
#endif
