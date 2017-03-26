/* RuleBase.h */

#ifndef RULEBASE_H
#define RULEBASE_H


#include "common.h"
#include "Rule.h"
#include "NonExistentEntry.h"

class RuleBase{
	private:

		/* Data structure to hold Rules */
		std::unordered_map< std::string, Rule * > data;
	public:

		/* Default constructor */
		RuleBase();

		/* Default paramaterized constructor */
		RuleBase(std::vector<Rule*> p_items);

		/*
		 * public method. Returns a vector with
		 * all keys in data
		 */
		std::vector<std::string> getKeys();

		/* 
		 * Returns a copy of the rule obj specified by p_name 
		 * Throws a ~ExistenceException~ if the content doesn't
		 * exist in the RuleBase.
		*/ 
		Rule getContent(const std::string & p_name);

		/* Returns a bool if the Rule is added to the RuleBase */
		bool addContent(Rule * p_item);

		/* 
		 * Returns bool if a Rule specified by p_nameis dropped 
		 * from the RuleBase.
		 */  
		bool dropContent(const std::string & p_name);
		~RuleBase();
};
#endif