#include "ConsoleCommandExecutor.h"

ConsoleCommandExecutor::ConsoleCommandExecutor(SQLQueryExecutor& ref)
	:sqlExecutor(ref)
{}

bool ConsoleCommandExecutor::addNewCommand(std::string command, std::function<void(SQLQueryExecutor&, std::vector<std::string>&)> function) {
	functions.insert(std::pair<std::string, std::function<void(SQLQueryExecutor&, std::vector<std::string>&)>>(command, function));
}
void ConsoleCommandExecutor::executeCommand(std::string command) {
	try {
		std::vector<std::string> params;
		std::string token;
		std::string delimiter = " ";
		std::string s = command;
		
		size_t pos = 0;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			params.push_back(s.substr(0, pos));
			s.erase(0, pos + delimiter.length());
		}
		params.push_back(s);

		functions.find(params.at(0))->second(sqlExecutor, params);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}