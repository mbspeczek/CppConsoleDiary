#include "MySQLDatabaseConnector.h"

MySQLDatabaseConnector::MySQLDatabaseConnector(std::string _login, std::string _password, std::string _host, std::string _database)
	:login(_login)
	,password(_password)
	,host(_host)
	,database(_database)
{}

MySQLDatabaseConnector::MySQLDatabaseConnector(DatabaseConnectorParams connectionParams) {
	login = connectionParams.login;
	password = connectionParams.password;
	host = connectionParams.host;
	database = connectionParams.database;
}

MySQLDatabaseConnector& MySQLDatabaseConnector::getDriverInstance() {
	driver = get_driver_instance();
	return *this;
}

MySQLDatabaseConnector& MySQLDatabaseConnector::connect() {
	connection = driver->connect(host, login, password);
	password.erase();
	return *this;
}

MySQLDatabaseConnector& MySQLDatabaseConnector::createStatement() {
	statement = connection->createStatement();
	return *this;
}

MySQLDatabaseConnector& MySQLDatabaseConnector::setSchema() {
	connection->setSchema(database);
	return *this;
}

sql::Statement& MySQLDatabaseConnector::getStatement() {
	return *statement;
}

void MySQLDatabaseConnector::closeConnection() {
	connection->close();
}

bool MySQLDatabaseConnector::connectToDatabase() {
	try
	{
		this->getDriverInstance().connect().setSchema().createStatement();
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
}