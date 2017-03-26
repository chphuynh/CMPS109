#ifndef INFERENCE_H
#define INFERENCE_H
#include "common.h"
#include "KnowledgeBase.h"  /* This includes Fact.h as well */
#include "RuleBase.h"  /* This includes Rule.h as well */
template <class T>
class ThreadManager;
class ORThread;
class ANDThread;
class Inference{


	
	private:
		/* These are the ptrs tp the KnowledgeBase and RuleBase */
		RuleBase * RB;
		KnowledgeBase * KB;
		/* print_query is a method that nicely formats the results from a query and writes them to stdout */
		void print_query(std::vector<std::vector<std::string>> p_set);
		/* SET_OR takes two sets and combines them on matching signifier's */ 
		std::vector<std::vector<std::string>> SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B);
		/* Remove_duplicates remove duplicate sets from our data */
		std::vector<std::vector<std::string>> remove_duplicates(std::vector<std::vector<std::string >> data);
		/* filter takes in a vector of strings and returns a bool if it passes the filter test */
		bool filter(std::vector<std::string> p_filter, std::vector<std::string > data );
		/* For pipelining, substitute will evalute given data in its next sequence */
		std::vector<std::vector<std::string>> subsitute(std::vector<std::vector<std::string>> test, std::vector<std::vector<std::string>> rule_data, int i);
		/* Filter_rb will prune results depending on the rule its evalutating */
		std::vector<std::vector<std::string>> filter_rb(std::vector<std::string> p_filter,  std::vector<std::vector<std::string>> data);
		/* query_KB will return a set of data from the KnowledgeBase based upon what the p_Inference is */
		std::vector<std::vector<std::string>> query_KB(std::vector<std::string> p_Inference);
		/* query_RB will return a set of data from the RuleBase evaluated based upon p_inference */
		std::vector<std::vector<std::string>> query_RB(std::vector<std::string> p_Inference);



	public:
		/* The Inference constructor takes two pointers as arguments and assigns them to RB and KB */
		Inference(KnowledgeBase * p_KB, RuleBase * p_RB);
		/* 
		 *Query returns a set of data to the caller will all legal values dependent on p_Inference. Default value
		 * of 1 requires query to print results at the top of the stack.
		 */
		std::vector<std::vector<std::string>> query(std::vector<std::string> p_Inference, int flag = 1);
		/* Interface Destructor */
		~Inference();
};
#endif