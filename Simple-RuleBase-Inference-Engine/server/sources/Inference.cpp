#include "../headers/Inference.h"
#include "../headers/ORThread.h"
#include "../headers/ANDThread.h"
#include "../headers/ThreadManager.h"
/* 
 * Constructor
 * Inference needs two pointers to perfrom its queries on.
 */ 
Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
}

/*
 * query will take in a vector of strings representing the Inference that wants to be made against
 * this objects RB and KB. This is a recursive function so there is a flag that represents the top 
 * of the stack for printing (defaulted to 1). This will return a 2D string vector with the first 
 * index of each element being the signifier.
 */
std::vector<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference, int flag){
	/* results of querying the KB and RB with no repeats */
	std::vector<std::vector<std::string>> results;

	/* Query the KnowledgeBase with this p_Inference */
	std::vector<std::vector<std::string>> kb_results = query_KB(p_Inference);
	/* Query the RuleBase with this p_Inference */
	std::vector<std::vector<std::string>> rb_results = query_RB(p_Inference);
	/* 
	 * Results will now be the combined set of the results from the KB and results from the RB
	 * with no duplicates.
	 */
	results = SET_OR(rb_results, kb_results);

	/* If flag is 1 (at the top of the stack), print the set of results */
	if(flag){
		print_query(results);
	}
	
	/* return the results upwards. */ 
	return results;
}

/*
 * query_kb returns a 2D string vector. Each index of the first layer contains a vector with it's 0th 
 * elelment being the signifier it belongs to.  The rest of the elements are values that
 * are legal.  These values match up with other values in other vectors based on their index 
 */
std::vector<std::vector<std::string>> Inference::query_KB(std::vector<std::string> p_Inference){
	/* Get the size of the inference vector */
	int inferenceSize = p_Inference.size();

	/* 
	 * Create new packaging array.  This will hold the vectors containing legal values represented
	 * by the queries 
	 */
	std::vector<std::vector<std::string>> data;


	/* Populate the data vector with legal signifiers */
	for(int i = 1; i < inferenceSize; ++i){
		if(p_Inference[i][0]=='$'){
			std::vector<std::string > temp_vector;
			temp_vector.push_back(p_Inference[i]);
			data.push_back(temp_vector);
		}
	}


	/* Now that the data structure is set up, we retrieve possible values for the inference */
	std::vector<Fact*> fact_data = KB->getContent(p_Inference[0]);

	/* For every fact add legal values to the data structure*/
	for(int i = 0; i < fact_data.size(); ++i){
		/* 
		 * If the fact has the correct number of predicates and when filtered, has the correct data values for
		 * paramatarized search
		 */
		if(fact_data[i]->getFact()[0].size() == inferenceSize && filter(p_Inference, fact_data[i]->getFact()[0])){
			// If it passed that test, create a vector to hold the data of the fact
			std::vector<std::string > this_fact = fact_data[i]->getFact()[0];
			// start the iterator past the the fact name, starting on predicate 0
			int fact_iter = 1;
			int data_iter = 0;
			// overall we only want to add from the fact, the values that arent paramterized we already passed the 
			// test to make sure the fact was the corret size, and had any given predicates in the right place and 
			// had the right value s so only adding the number of variable predicates
			while(data_iter < data.size()){
				if(p_Inference[fact_iter][0] == '$'){
					// add the fact value for that predicate
					data[data_iter].push_back(this_fact[fact_iter]);
					fact_iter++;
					data_iter++;
				}else{
					// if its a non-variable predicate
					fact_iter++;
				}
			}

		}
	}

	// return all values of that data
	return data;
}

/* query_rb will evaluate rules and recursivley call any rules that may also need to be evaluted */
std::vector<std::vector<std::string>> Inference::query_RB(std::vector<std::string> p_Inference){
	/* Data structure to hold legal values */
	std::vector<std::vector<std::string>> data;

	int inferenceSize = p_Inference.size();

	/* Data structure to hold the rule so there isn't function overhead */
    std::vector<std::vector<std::string>>rule_data;

    /* It is possible that there is no rule in the RB with this name, return empty set if so. */
    try{
        Rule this_rule = RB->getContent(p_Inference[0]);
        rule_data = this_rule.getRule();
    }catch(ExistenceException e){
        return data;
    }

    /* Populate the data structure with signifiers */
    for(int i = 1; i < rule_data[0].size();i++){
            std::vector<std::string > temp;
            temp.push_back(rule_data[0][i]);
            data.push_back(temp);
    }


    // Data structure to hold possible values from inferencing with a new inference
    std::vector<std::vector<std::string>> query_data;





    // If the rule has the OR operator
    if(rule_data[1][0] == "OR"){
    	// instantiate a ThreadManager Template object with type ORThread
    	ThreadManager<ORThread> * threadManager = new ThreadManager<ORThread>();


    	// a query will be performed on every rule target in rule data
    	for(int i = 2; i < rule_data.size()-1; ++i){

    		// It is possible that the new inference will have non_variable predicate values
    		// grab original p_inference without values substitued, and create something
    		// we can modify to make a new inference
    		std::vector<std::string > default_rule_name = rule_data[0];
	    	std::vector<std::string > new_inference = rule_data[i];


	    	// if something in p_infence was a value, see if it needs to be inserted into the
	    	// new_inference and insert
    		for(int j = 1; j < p_Inference.size();j++){
				if(p_Inference[j][0] !=  '$'){
					for(int k = 1; k < new_inference.size();k++){
						if(new_inference[k] == default_rule_name[j]){
							new_inference[k] = p_Inference[j];
						}
					}
				}
			}
			// For every rule target, add a thread with its inference
			threadManager->addThread(new ORThread(this, new_inference));
		}
		// start the execution of the threads
		threadManager->start();

		// wait for all threads to finish
		threadManager->barrier();
		// combine all the data of the threads into one coherent thread
		data = threadManager->combineResults(data);
		// delete the threadmanager and all its associated threads
		delete(threadManager);

		
		// Add this set of data to data
        // data = SET_OR(data, query_data);
        bool needToUpdate = false;
	    for(int i = 1; i < p_Inference[i].size(); i++){
	    	bool this_sig = false;
	    	for(int j = 0; j < data.size();j++){
	    		if(p_Inference[i] == data[j][0]){
	    			this_sig = true;
	    		}
	    	}
	    	if(!this_sig){
	    		needToUpdate = true;
	    	}
	    }
	    if(needToUpdate){
		    int i = 0;
		    int j = 1;
		    while(j!=p_Inference.size()){
		    	if(p_Inference[j][0]!='$'){
		    		j++;
		    	}else{
		    		if(p_Inference[j]!=data[i][0]){
		    			data[i][0] = p_Inference[j];
		    		}
	    			j++;
	    			i++;
		    	}
		    }
		}
        return data;
        



    // if rule operator is AND
    }else{
    	// Grab the position of the rule target in rule
    	int position = 2;
    	// Create the strctures to hold dat
    	std::vector<std::string > default_rule_name = rule_data[0];
    	std::vector<std::string > new_inference = rule_data[position];

    	// Adjust the new inference to hold any substituted values
		for(int j = 1; j < p_Inference.size();j++){
			if(p_Inference[j][0] !=  '$'){
				for(int k = 1; k < new_inference.size();k++){
					if(new_inference[k] == default_rule_name[j]){
						new_inference[k] = p_Inference[j];
					}
				}
			}
		}

		// query the new inference
		
    	query_data = query(new_inference, 0);
    	
    	// If position isnt the last rule target in the rule, substitute the results from the previous 
    	// query into the next rule target 
		if(position != rule_data.size()-1){
			query_data = subsitute(query_data, rule_data, position);
		}
		data = SET_OR(data, query_data);
	    data = filter_rb(p_Inference, data);
    }

    // Evaluating rules can lead to different signifiers being inserted into the datat, and returned upwards
    // this loop will change those signifiers back to the orginial p_inference signifiers


    bool needToUpdate = false;
    for(int i = 1; i < p_Inference[i].size(); i++){
    	bool this_sig = false;
    	for(int j = 0; j < data.size();j++){
    		if(p_Inference[i] == data[j][0]){
    			this_sig = true;
    		}
    	}
    	if(!this_sig){
    		needToUpdate = true;
    	}
    }

    if(needToUpdate){
	    int i = 0;
	    int j = 1;
	    while(j!=p_Inference.size()){
	    	if(p_Inference[j][0]!='$'){
	    		j++;
	    	}else{
	    		if(p_Inference[j]!=data[i][0]){
	    			data[i][0] = p_Inference[j];
	    			j++;
	    			i++;
	    		}
	    	}
	    }
	}
    return data;
}

/* Print query formats a 2D string vector and prints to stdout */
void Inference::print_query(std::vector<std::vector<std::string>> p_set){
	for(int i = 1; i < p_set[0].size(); ++i){
		for (int j = 0; j < p_set.size(); ++j){
			if(j == p_set.size()-1){
				std::cout << p_set[j][0] << ":" << p_set[j][i];
			}else{
				std::cout << p_set[j][0] << ":" << p_set[j][i] << ", ";
			}
		}
		std::cout << '\n';
	}
}


/*
 * SET_OR, given 2 unique 2d string vectors, return a single 2D string vector containing only the values of both 2D vectors where their 
 * signifiers match. 
 */
std::vector<std::vector<std::string>> Inference::SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B){
	// This is the data strcuture of the returning object
	std::vector<std::vector<std::string>> data;

	// If A is empty (i.e no an empty 2d structre)
	if(A.empty()){
		// And b is not 
		if(!B.empty()){
			// return B, there is nothing to compare too.  All of B is correct
			return B;
		}
	// vice versa
	}else if(B.empty()){
		if(!A.empty()){
			return A;
		}
	}

	// starting at the first vector in A (we dont need to start at the smaller one)
	// because if A[i] doesnt exist in B we dont use it, and if B[i] doesnt exist in A
	// we dont use it. So using either structure is arbirtary
	for(auto it = A.begin(); it != A.end(); it++ ){
		// break out the structure located at the *it loation in A
		std::vector<std::string > temp = *it;
		// iterating through every second layer in B
		for(int i = 0; i < B.size(); i++){
			// if the signifier matches in temps structue and one of B's 2nd layer structure
			// (temp is a second layer structure), then these results can be or'd.
			if(temp[0] == B[i][0]){
				// To keep the index the same we need to set a standard, since the size of the second layer
				// structure is uniform in B (A's can be different, but every second layer strcutre is still
				// the same size) we just need to always add A or B first. Here i choose A.  Every insertion 
				// will have A[i].size() number of values , theb B[i].size() number of values
			 	std::vector<std::string > to_be;
			 	// add the signifier to the vector
			 	to_be.push_back(temp[0]);
			 	// copy all of temp's values into it
			 	for(int j = 1; j < temp.size(); j++){
			 		to_be.push_back(temp[j]);
			 	}
			 	// copy all of B[i]'s values into it
			 	for(int j = 1; j < B[i].size(); j++){
			 		to_be.push_back(B[i][j]);
			 	}
			 	// add it to the data data struct
			 	data.push_back(to_be);

			}
		}
	}
	data = remove_duplicates(data);
	// return the now combined 2D struct
	return data;

}
/* filter returns true if the values match the filter given */
bool Inference::filter(std::vector<std::string> p_filter, std::vector<std::string > data ){
	for(int i = 1; i < p_filter.size(); ++i){
		if(p_filter[i][0] != '$'){
			if(data[i] != p_filter[i]){
				return false;
			}
		}
	}
	return true;
}




// Removing duplicates
// Takes in a 2D string vector, and needs to iterate through the entire thing and check for duplicates
// if there is a duplicates it means that every predicate item it has, will be somehwere else.  I only need to
// check one column, but when a match comes up i have to check N amout of predicates. 
std::vector<std::vector<std::string>> Inference::remove_duplicates(std::vector<std::vector<std::string >> data){
	// data struct holding all the non duplicate values
	std::vector<std::vector<std::string>> final;
	// get the size
	int size = data.size();
	// for all the signifiers, add them in order to the final data struct
	for(int i = 0; i < size; i++){
		std::vector<std::string > v;
		v.push_back(data[i][0]);
		final.push_back(v);
	}


	// for every item passed the signifier in column one
	for(int i = 1; i < data[0].size(); ++i){
		// create a 1D string vector
		std::vector<std::string> comparing;

		for(int j = 0; j < data.size();j++){
			comparing.push_back(data[j][i]);
		}
		// set the flag to true.  Will evaluate to false if theres a duplicate later in the list
		bool flag = true;
		// For every value past comparing's point in the list (no need to recheck valuea)
		for(int k = i+1; k < data[0].size(); k++){
			// if the first element's are equal
			if(comparing[0] == data[0][k]){
				// copy all of the values of the possible
				std::vector<std::string> compared_to;
				for(int j = 0; j < data.size();j++){
					compared_to.push_back(data[j][k]);
				}
				// if theyre equal switch the flag
				if(comparing == compared_to){
					flag = false;
				}
			}
		}
		if(flag){
			for(int j = 0; j < final.size();j++){
				final[j].push_back(comparing[j]);
			}
		}
	}
	return final;

}

/* substitute will take in data, rule_data, and a position and substitute any reused predicates into the next rule_target */
std::vector<std::vector<std::string>> Inference::subsitute(std::vector<std::vector<std::string>> data, std::vector<std::vector<std::string>> rule_data, int i){
	std::vector<std::vector<std::string >> results;

	// take the vector of the rule target located at given i
	// and add the predicates to results

	for(int j = 1; j < rule_data[i].size(); j++){
		std::vector<std::string> temp_v;
		temp_v.push_back(rule_data[i][j]);
		results.push_back(temp_v);
	}
	
	// create an p_inference vector
	std::vector<std::string> p_Inference;
	// iterate over the next item in the rule_data

	for(int j = 0; j < rule_data[i+1].size();j++){
		// if not the rule name, try to add the signifiers
		if(j!=0){
			bool canAdd = true;
			for(int q = 1; q < results.size();q++){
				if(rule_data[i+1][j]==results[q][0]){
					canAdd = false;
				}
			}
			if(canAdd){
				std::vector<std::string> temp_v;
				temp_v.push_back(rule_data[i+1][j]);
				results.push_back(temp_v);
			}
		}

		p_Inference.push_back(rule_data[i+1][j]);

	}



	// Create a new templated threadmanager object with type ANDThread  
	ThreadManager<ANDThread> * threadManager_AND = new ThreadManager<ANDThread>();

	// for every set there is in data, create a customized 
	// set of their values, and adjust p_inference for their values
	for(int j = 1; j < data[0].size(); j++){
		// temp vector this_V
		std::vector<std::vector<std::string>> this_v;
		for(int b = 0; b < results.size(); b++){
			std::vector<std::string > v = {results[b][0]};
			this_v.push_back(v);
		}
		// for every value of a signifier in data a data row
		for(int k = 0; k < data.size(); k++){
			// create a set of them in vector this_v
			for(int p = 0; p < this_v.size();p++){
				if(data[k][0] == this_v[p][0]){
					this_v[p].push_back(data[k][j]);
				}
			}


			
			// checking against rule_Data[i+1]
			for(int p = 0; p < rule_data[i+1].size(); p++){
				if(data[k][0] == rule_data[i+1][p]){
					p_Inference[p] = data[k][j];

				}
			}
		}
		// create a thread for every new query that needs to be done with substitued values
		threadManager_AND->addThread(new ANDThread(this, p_Inference, results, this_v));
	}
	// start the execution of all the threads
	threadManager_AND->start();
	// wait for all threads to complete
	threadManager_AND->barrier();
	// combine all the threads resutls into a coherent legal set
	results = threadManager_AND->combineResults(results);
	// delete the thread manager and all its associated threads
	delete(threadManager_AND);

	return results;
}

/* filter_Rb takes in p_filter and removes any signifier and their elements not included in p_filter */
std::vector<std::vector<std::string>> Inference::filter_rb(std::vector<std::string> p_filter,  std::vector<std::vector<std::string>> data){
	std::vector<std::vector<std::string >> results;
	

	for(int i = 0; i < data.size(); i++){
		std::vector<std::string> v;
		v.push_back(data[i][0]);
		results.push_back(v);

	}

	Rule this_rule = RB->getContent(p_filter[0]);
	std::vector<std::vector<std::string>> rule_data = this_rule.getRule();
	std::vector<std::string> rule_name = rule_data[0];


	for(int j = 1; j < data[0].size(); j++){
		// temp vector this_V
		std::vector<std::vector<std::string>> this_v;
		for(int b = 0; b < results.size(); b++){
			std::vector<std::string > v = {results[b][0]};
			this_v.push_back(v);
		}
		// for every value of a signifier in data a data row
		for(int k = 0; k < data.size(); k++){
			// create a set of them in vector this_v
			for(int pp = 0; pp < this_v.size();pp++){
				if(data[k][0] == this_v[pp][0]){
					this_v[pp].push_back(data[k][j]);
				}
			}
		}


		// this where i have to remove it if it sucks
		bool canAdd = true;
		for(int i = 1; i < p_filter.size(); i++){
			if(p_filter[i][0] != '$'){
				for(int k = 0; k < this_v.size();k++){
					if(this_v[k][0] == rule_name[i] && this_v[k][1] != p_filter[i]){
						canAdd = false;
					}
				}
			}
		}
		if(canAdd){
			for(int i = 0; i < this_v.size();i++){
				for(int k = 0; k < results.size();k++){
					if(this_v[i][0] == results[k][0]){
						results[k].push_back(this_v[i][1]);
					}
				}
			}
		}



	}


	return results;
}


// Destructor that frees the ptrs
Inference::~Inference(){
	free(KB);
	free(RB);
}