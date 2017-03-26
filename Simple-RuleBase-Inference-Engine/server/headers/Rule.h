/* Rule.h */
#ifndef RULE_H
#define RULE_H

#include "common.h"


class Rule{
	private:
		/* ruleName($X, $Y):-ruleOperator factName1($X, $Y) factName2($x, $Y) */
		std::string ruleName;
		std::vector<std::vector<std::string>> data;
	public:
		Rule(std::vector<std::vector<std::string>> p_data);
		/* Getter methods */
		std::string getRuleName();
		std::vector<std::vector<std::string>> getRule();
		~Rule();
};
#endif
