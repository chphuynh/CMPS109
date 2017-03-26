#ifndef EXISTENCEEXCEPTION_H
#define EXISTENCEEXCEPTION_H

#include <exception>
#include <stdexcept>
#include "common.h"

class ExistenceException{
	private:
		std::string exception_str;
		std::string entry;
	public:
		ExistenceException(const std::string & p_entry);
		void printException();
		virtual ~ExistenceException();
};

#endif