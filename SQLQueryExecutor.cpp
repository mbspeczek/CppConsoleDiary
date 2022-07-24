#include "SQLQueryExecutor.h"

SQLQueryExecutor::SQLQueryExecutor(sql::Statement& stmt)
	:statement(stmt)
{}


sql::ResultSet* SQLQueryExecutor::executeSelect(std::string query) {
	sql::ResultSet* set;
	try {
		set = statement.executeQuery(query);
		return set;
	}
	catch (sql::SQLException& e) {
		std::cout << e.what();
		return nullptr;
	}
}

int SQLQueryExecutor::executeUpdate(std::string query) {
	try {
		return statement.executeUpdate(query);
	}
	catch (sql::SQLException& e) {
		std::cout << e.what();
		return 0;
	}
}

sql::ResultSet* SQLQueryExecutor::executeQuery(std::string query) {
	sql::ResultSet* set;
	try {
		set = statement.executeQuery(query);
		return set;
	}
	catch (sql::SQLException& e) {
		std::cout << e.what();
		return nullptr;
	}
}

int SQLQueryExecutor::execute(std::string query) {
	try {
		statement.execute(query);
		return 1;
	}
	catch (sql::SQLException& e) {
		std::cout << e.what();
		return 0;
	}
}
