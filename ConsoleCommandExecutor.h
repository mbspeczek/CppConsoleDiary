#pragma once
#include <functional>
#include <string>
#include <map>
#include <vector>

#include "SQLQueryExecutor.h"

class ConsoleCommandExecutor {
public:
	ConsoleCommandExecutor(SQLQueryExecutor& ref);
	bool addNewCommand(std::string command, std::function<void(SQLQueryExecutor&, std::vector<std::string>&)> function);
	void executeCommand(std::string command);
private:
	std::map<std::string, std::function<void(SQLQueryExecutor&, std::vector<std::string>&)>> functions;
	SQLQueryExecutor& sqlExecutor;
};