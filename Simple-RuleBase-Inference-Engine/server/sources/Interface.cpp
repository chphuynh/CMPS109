#include "../headers/Interface.h"


//default constructor just creates new objects
Interface::Interface(){
	KB = new KnowledgeBase();
	RB = new RuleBase();
}


/* parse seg takes a block and seperates it into a string vector */
std::vector<std::string> Interface::parseSeg(std::string target) {
	std::vector<std::string> segment;
	auto rName = target.substr(0, target.find('('));
	segment.push_back(rName);
	target.erase(0, target.find('(') + 1);
	auto rParams = target.substr(0, target.find(')'));
	size_t pos = 0;
	std::string token;
	while ((pos = rParams.find(',')) != std::string::npos) {
		token = rParams.substr(0,pos);
		segment.push_back(token);
		rParams.erase(0, pos + 1);
	}
	if(!rParams.empty()) segment.push_back(rParams);
	return segment;
}

/* 
 * parse takes in a string and will parse it into readable format.
 * Once it has the type of statement it will format it further and
 * call executeCommand().
 */
char * Interface::parse(std::string p_statement){
	std::vector<std::string> result; 
	std::istringstream strinput(p_statement);
	
	// Seperates line into words seperated by whitespace
	// Inserts into vector
	while(strinput){
		std::string next_word;
		strinput >> next_word;
		result.push_back(next_word);
	}

	// RULE COMMAND
	if(result[0] == "RULE") {
		std::vector<std::vector<std::string>> rule = {{"RULE"}};
		// create an executable rule
		int step = 0;

		std::string stream;
		for(auto &str : result) {
			if(step == 0){
				step++;
				continue;
			} else if (step == 1) { // Parses Rule/Fact Name
				if(str.find(')') == std::string::npos){
					stream += str;
					continue;
				} else {
					stream += str;
					stream.erase(std::remove(stream.begin(), stream.end(), ' '), stream.end());
					rule.push_back(parseSeg(stream));
					stream = "";
					step++;
				}
			} else if (step == 2) { // Parse Operators
				if(str == "AND" | str == "OR") {
					std::vector<std::string> oper;
					oper.push_back(str);
					rule.push_back(oper);
					step++;
				} else {
					return NULL;
				}
			}  else { //step == 3 // Parse Targets
				if(str.find(')') == std::string::npos){
					stream += str;
					continue;
				} else {
					stream += str;
					stream.erase(std::remove(stream.begin(), stream.end(), ' '), stream.end());
					rule.push_back(parseSeg(stream));
					stream = "";
				}
			}
		}
		// rule is now a formatted rule command, execute it and return bool upwards
		return format(executeCommand(rule));
	// FACT COMMAND
	} else if (result[0] == "FACT") {
		std::vector<std::vector<std::string>> fact = {{"FACT"}};
		// create an executable fact
		int step = 0;
		std::string stream;
		for(auto &str : result) {
			if(step == 0){
				step++;
				continue;
			} else if (step == 1) { // Parses Rule/Fact Name
				if(str.find(')') == std::string::npos){
					stream += str;
					continue;
				} else {
					stream += str;
					stream.erase(std::remove(stream.begin(), stream.end(), ' '), stream.end());
					fact.push_back(parseSeg(stream));
					stream = "";
				}
			}
		}
		// fact is now an executable fact
		return format(executeCommand(fact));
	// INFERENCE COMMAND
	} else if (result[0] == "INFERENCE") {
		std::vector<std::vector<std::string>> query ={{"INFERENCE"}};
		// inference formatting
		int step = 0;
		for(auto &str : result) {
			if(step == 0){
				step++;
				continue;
			} else if (step == 1) { // Parses Rule/Fact Name
				query.push_back(parseSeg(str));
				step++;
			} else if (step == 2) {
				std::vector<std::string> resName;
				resName.push_back(str);
				query.push_back(resName);
			}
		}
		// input into buffer the formatted reslts of a query
		char * temp = (char*)calloc(150,sizeof(char));
		temp = format(executeCommand(query));
		return temp;
	// DROP COMMAND
	} else if (result[0] == "DROP") {
		std::vector<std::vector<std::string>> drop = {{"DROP"}};
		// further formatting
		for(auto &str : result) {
			if(str == "DROP") continue;
			std::vector<std::string> rfName;
			rfName.push_back(str);
			drop.push_back(rfName);
		}
		return format(executeCommand(drop));
	// LOAD COMMAND
	} else if (result[0] == "LOAD") {
		std::vector<std::vector<std::string>> load = {{"LOAD"}};

		// further formatting
		for(auto &str : result) {
			if(str == "LOAD") continue;
			std::vector<std::string> fileName;
			fileName.push_back(str);
			load.push_back(fileName);
		}
		return format(executeCommand(load));
	// DUMP COMMAND
	} else if (result[0] == "DUMP") {
		std::vector<std::vector<std::string>> dump = {{"DUMP"}};

		// further formatting
		std::vector<std::string> outputFile;
		outputFile.push_back(result[1]);
		dump.push_back(outputFile);

		return format(executeCommand(dump));
	} else {
		std::cout << "Unkown Command" << std::endl;
		return NULL;
	}
}

// takes a 2d string vector and properly handles the execution of it
std::vector<std::vector<std::string>> Interface:: (std::vector<std::vector<std::string>> p_command){
	std::vector<std::vector<std::string>> results;
	//creates fact object and adds it to KB
	if (p_command[0][0] == "FACT") {
		// remove indicator 
		p_command.erase(p_command.begin());
		// create new fact and add it
		Fact * f1 = new Fact(p_command);
		KB->addContent(f1);
		return results;
	}
	//creates rule object and adds it to RB
	else if (p_command[0][0] == "RULE") {
		// remove indicator
		p_command.erase(p_command.begin());
		Rule * r1 = new Rule(p_command);
		RB->addContent(r1);
		return results;
	}
	else if (p_command[0][0] == "INFERENCE") {
		// create a new inference object
		Inference * infer = new Inference(KB, RB);
		//second arguement taken as query
		std::vector<std::string> q1 = p_command[1];
		//prints out extra $x and $y, don't know why tf it does
		results =  infer->query(q1);

		// if the user specifies a name to store the results under, store them 
		// in KB

		if(p_command.size() > 3){
			for(int i = 1; i < results[0].size();i++){
				std::vector<std::string> temp;
				temp.push_back(p_command[p_command.size()-2][0]);
				for(int j = 0; j < results.size();j++){
					temp.push_back(results[j][i]);
				}
				std::vector<std::vector<std::string >> v;
				v.push_back(temp);
				Fact * f1 = new Fact(v);
				KB->addContent(f1);
			}
		}
		return results;
	}else if (p_command[0][0] == "DROP") {
		// drop from rb and kb 
		RB->dropContent(p_command[1][0]);
		KB->dropContent(p_command[1][0]);
		return results;
	}
	return results;
}

// format takes the 2d vector set and creates a header for the flat char * it become
char * Interface::format(std::vector<std::vector<std::string>> result){
	if(result.size() > 0){
		std::string temp;
		temp += formatSize((int)result.size());
		temp += formatSize(((int)result[0].size())-1);
		for(auto &i : result)
		{
			for(auto &j : i)
			{
				temp += j;
				temp += "|";
			}
		}
		char * buffer = new char[temp.size() + 1];
		std::copy(temp.begin(), temp.end(), buffer);
		buffer[temp.size()] = '\0'; // don't forget the terminating 0
		return buffer;
	}else{
		char * buffer = (char*)calloc(4,sizeof(char));
		buffer[0] = 'n'; buffer[1] = 'u'; buffer[2] = 'l'; buffer[3] = 'l';
		return buffer;
	}
}

std::string Interface::formatSize(int size)
{
	std::string temp;
	int zeros = 3 - floor(log10(size));
	for(int i = 0; i < zeros; i++)
	{
		temp += "0";
	}
	temp += std::to_string(size);
	return temp;
}


Interface::~Interface(){
	delete(KB);
	delete(RB);
	delete(serverSocket);
}


// grab returns a set of all rules and facts
std::vector<char *> Interface::grab(){
	std::vector<char*> results;
	std::vector<std::string> kbKeys = KB->getKeys();

	
	for(auto &key : kbKeys){
		// Grabs fact Vector using key
		std::vector<Fact*> factVector = KB->getContent(key);

		// Iterates through every fact in factVector
		for(auto &fact : factVector){
			std::string factString = "FACT ";
			//Iterates over each vector of the Fact Vector
			bool factName = true;

			for(auto &factData : fact->getFact()) {
				// Iterates over each element in fact
				for(auto &factELement : factData) {
					if(factName) {
						factString += factELement + "(";
						factName = false;
					} else {
						factString += factELement + ",";
					}
				}
				factString.erase(factString.size() - 1);
				factString += ")";

				char *cstr = new char[factString.length() + 1];
				strcpy(cstr, factString.c_str());
				results.push_back(cstr);
				break;
			}
		}
	}

	// Grabs keys from RB
	std::vector<std::string> rbKeys = RB->getKeys();

	// Iterates over each key
	for(auto &key : rbKeys){
		Rule rule = RB->getContent(key);
		std::string ruleString = "RULE ";
		bool ruleName = true;
		bool isOp = false;
		// Iterates through each data of rule vector
		for(auto &ruleData : rule.getRule()) {
			bool targetName = true;

			// Bandaid fix for empty vector
			if(ruleData[0] == "") {
				break;
			}

			// Iterates through each element of Data
			for(auto &ruleElement : ruleData) {
				if(targetName) {
					ruleString += ruleElement + "(";
					targetName = false;
					continue;
				} else if(isOp) {
					ruleString += ruleElement;
					continue;
				} else {
					ruleString += ruleElement + ",";
					continue;
				}
			}

			// Formatting
			if(ruleName) {
				ruleString.erase(ruleString.size() - 1);
				ruleString += "):- ";
				ruleName = false;
				isOp = true;
			} else if(isOp) {
				ruleString.erase(ruleString.size() - 1);
				ruleString += " ";
				isOp = false;
			} else {
				ruleString.erase(ruleString.size() - 1);
				ruleString += ") ";

			}
		}

		char *cstr = new char[ruleString.length() + 1];
		strcpy(cstr, ruleString.c_str());
		results.push_back(cstr);

	}
	char *cstr = (char*)calloc(1,sizeof(char));
	cstr[0] = '\0';
	results.push_back(cstr);
	return results;
}