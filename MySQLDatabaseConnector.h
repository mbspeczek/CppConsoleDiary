#pragma once

#include "mysql_connection.h"

#include <cppconn/driver.h>

struct DatabaseConnectorParams
{
	std::string login;
	std::string password;
	std::string host;
	std::string database;
};

class MySQLDatabaseConnector {
public:
	MySQLDatabaseConnector(DatabaseConnectorParams connectionParams);
	MySQLDatabaseConnector(std::string _login, std::string _password, std::string _host, std::string _database);
	MySQLDatabaseConnector& getDriverInstance();
	MySQLDatabaseConnector& connect();
	MySQLDatabaseConnector& createStatement();
	MySQLDatabaseConnector& setSchema();
	void closeConnection();
	sql::Statement& getStatement();
	bool connectToDatabase();
private:
	sql::Driver* driver;
	sql::Statement* statement;
	sql::Connection* connection;
	
	std::string login;
	std::string password;
	std::string host;
	std::string database;
};