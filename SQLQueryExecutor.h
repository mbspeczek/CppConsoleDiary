#pragma once

#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class SQLQueryExecutor {
public:
	SQLQueryExecutor(sql::Statement& stmt);
	sql::ResultSet* executeSelect(std::string query);
	int executeUpdate(std::string query);
	sql::ResultSet* executeQuery(std::string query);
	int execute(std::string query);
private:
	sql::Statement& statement;
};