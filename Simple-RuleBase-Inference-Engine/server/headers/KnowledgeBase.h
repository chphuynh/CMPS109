/* KnowledgeBase.h */

#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

#include "common.h"
#include "Fact.h"

class KnowledgeBase{
	
	private:
		/* Struct to hold our facts */
		std::unordered_map< std::string , std::vector<Fact *> > data;
		/* Private method that checks if a vector of facts contains fact F2 */
		bool check(std::vector<Fact*> data, Fact * f2);
	public:
		/* Default constuctor */
		KnowledgeBase();
		/* Paramaterized constructor */
		KnowledgeBase(std::vector<Fact*> p_items);

		/*
		 * public method. Returns a vector with
		 * all keys in data
		 */
		std::vector<std::string> getKeys();

		/*
		 * public method.  Returns a vector with any
		 * instances of a fact 
		 */
		std::vector<Fact*> getContent(const std::string & p_name);
		
		/*
		 * public method.  Returns a bool on success
		 * of inserting the ptr to the fact obj passed to it
		 */
		bool addContent(Fact * p_item);

		/*
		 * public method.  Returns a bool on success of 
		 * deleting all instances of a fact
		 */
		bool dropContent(const std::string & p_name);
		~KnowledgeBase();

};
#endif