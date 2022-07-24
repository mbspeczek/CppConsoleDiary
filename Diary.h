#pragma once

#include <memory>

#include "MySQLDatabaseConnector.h"
#include "SQLQueryExecutor.h"
#include "ConsoleCommandExecutor.h"
class Diary {
public:
	Diary();
	~Diary();
	DatabaseConnectorParams login();
	bool runDiary();
	std::string getDiaryUser(DatabaseConnectorParams& data);
private:
	std::shared_ptr<MySQLDatabaseConnector> dbConnector;
	std::shared_ptr<SQLQueryExecutor> SQLCommandExecutor;
	std::shared_ptr<ConsoleCommandExecutor> consoleCommandExecutor;
	std::string user;
};