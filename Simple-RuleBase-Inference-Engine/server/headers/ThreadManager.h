/* 
	ThreadManager.h
	Original Implementaton: Professor Karim Sobh
	Modified by: Daniel Thurau

 */


#ifndef THREADMANAGER_H
#define THREADMANAGER_H


#include "common.h"
// Forward declaration of two classes
class ORThread;
class ANDThread;

// Templated class
// Defintion of the methods is done in the header to deal with implicit declaration
template <typename T>
class ThreadManager{
	private:
		// the vector of threads of type T
		std::vector<T *> threads;
	public:
		ThreadManager(){};
		// Add a thread to a the vector
		void addThread(T * p_thread){
			threads.push_back(p_thread);
		}

		// Start each thread
		void start(){
				for(int i = 0; i < threads.size();++i){
				threads[i]->start();
			}
		}

		// wait for each thread to finish
		void barrier(){
			for(int i = 0; i < threads.size(); ++i){
				threads[i]->waitForRunToFinish();
			}
		}

		// Combine sets returned from a thread
		std::vector<std::vector<std::string>> SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B){
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
			// return the now combined 2D struct
			return data;
		}


		// get each data set from a thread and combine them 
 		std::vector<std::vector<std::string>> combineResults(std::vector<std::vector<std::string>> results){
 			for(int i = 0; i < threads.size(); i++){
				results = SET_OR(results, threads[i]->getData());
			}
			return results;
 		}

 		// destroy all threads and free pointers
		virtual ~ThreadManager(){
			for(int i = 0; i < threads.size();i++){
				delete(threads[i]);
			}
		}
};

#endif