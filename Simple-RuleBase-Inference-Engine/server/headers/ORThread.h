#ifndef ORTHREAD_H
#define ORTHREAD_H

#include "Thread.h"
#include "common.h"

// Forward declaration of the inference class
class Inference;

// public inheritence of the Thread class
class ORThread : public Thread {
	private:
		// pointer to the object that called the thread
		Inference * inferenceObject;
		// the inference for the thread
		std::vector<std::string> thisInference;
		// the set that will be populated by the query
		std::vector<std::vector<std::string>> data;
	public:
		// constructor of class ORThread
		ORThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference);
		// returns the set of data to a caller
		std::vector<std::vector<std::string>> getData();
		// implemented virtual method
		virtual void * threadMainBody(void * arg);
		~ORThread();
};

#endif