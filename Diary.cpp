#include "Diary.h"
#include "DiaryLog.h"
#include <functional>
#include <map>

Diary::Diary() {}

Diary::~Diary() {
	dbConnector->closeConnection();
}

bool Diary::runDiary() {
	DatabaseConnectorParams connectionParams = login();
	dbConnector = std::make_shared<MySQLDatabaseConnector>(connectionParams);
	if (!dbConnector->connectToDatabase()) {
		return 0;
	}
	
	std::cout << "Connected!" << std::endl << std::endl;
	SQLCommandExecutor = std::make_shared<SQLQueryExecutor>(dbConnector->getStatement());
	consoleCommandExecutor = std::make_shared<ConsoleCommandExecutor>(*SQLCommandExecutor);
	user = connectionParams.login;

	try {
		consoleCommandExecutor->addNewCommand("all", [](SQLQueryExecutor &t, std::vector<std::string> &params) {
				sql::ResultSet* res = t.executeSelect("SELECT id_diary, data FROM Diary;");
				if (res == nullptr) {
					std::cout << "No data." << std::endl;
				}
				while (res->next()) {
					std::cout << res->getString(1)<< ". " << res->getString(2) << std::endl;
				}
			});
		consoleCommandExecutor->addNewCommand("help", [](SQLQueryExecutor& t, std::vector<std::string> &params) {
				std::cout << "Commands:" << std::endl;
				std::cout << " all - show all diary logs." << std::endl;
				std::cout << " get - get diary log by ID." << std::endl;
				std::cout << " add - open new add form to create diary log." << std::endl;
				std::cout << " delete - delete diary log by ID." << std::endl;
				std::cout << " help - this." << std::endl;
				std::cout << " exit - to exit." << std::endl;
			});
		consoleCommandExecutor->addNewCommand("get", [](SQLQueryExecutor& t, std::vector<std::string>& params) {
				std::string query = "SELECT data, content FROM Diary WHERE id_diary="+params.at(1)+";";
				sql::ResultSet* res = t.executeSelect(query);
				if (res == nullptr) {
					std::cout << "No data." << std::endl;
				}
				while (res->next()) {
					std::cout << res->getString(1) << " - '" << res->getString(2) << "'" << std::endl;
				}
			});
		consoleCommandExecutor->addNewCommand("add", [](SQLQueryExecutor& t, std::vector<std::string>& params) {
				std::string date;
				std::string content;
			
				std::cout << "  Date: ";
				std::getline(std::cin, date);
				std::cout << "  Content: ";
				std::getline(std::cin, content);

				std::string query = "INSERT INTO Diary(data, content) VALUES ('"+ date +"','"+ content +"');";
			
				if (t.execute(query)) {
					std::cout << "Log added." << std::endl;
				}
				else {
					std::cout << "Can't add new log." << std::endl;
				}
			});
		consoleCommandExecutor->addNewCommand("delete", [](SQLQueryExecutor& t, std::vector<std::string>& params) {
				std::string query = "DELETE FROM Diary WHERE id_diary=" + params.at(1) +";";
				if (t.execute(query)) {
					std::cout << "Log deleted." << std::endl;
				}
				else {
					std::cout << "Can't delete log." << std::endl;
				}
			});
	}
	catch (std::exception& e) {
		std::cout << e.what();
		return 0;
	}
	
	std::string cmd;
	std::getline(std::cin, cmd); /* clear potencialy issue */
	while (1)
	{
		std::cout << user << ": ";
		std::getline(std::cin, cmd);
		if (cmd == "exit") {
			return 0;
		}
		else {
			consoleCommandExecutor->executeCommand(cmd);
		}
		std::cout << std::endl;
	}

	

}


DatabaseConnectorParams Diary::login() {
	DatabaseConnectorParams connectionParams;
	std::string param;
	try {
		std::cout << "Login:";
		std::cin >> connectionParams.login;
		std::cout << "Password:";
		std::cin >> connectionParams.password;
		std::cout << "Host:";
		std::cin >> param;
		connectionParams.host = "tcp://" + param + ":3306";
		std::cout << "Database:";
		std::cin >> connectionParams.database;

		return connectionParams;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		connectionParams.login = connectionParams.password = connectionParams.database = connectionParams.host = "";
		
		return connectionParams;
	}
}

std::string Diary::getDiaryUser(DatabaseConnectorParams& data) {
	return data.login;
}