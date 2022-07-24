# CppConsoleDiary
Simple diary application in console. The application must be connected to database via db account.

You can:
- add new diary log,
- delete diary log,
- get diary log.

How to connect:
- create new account with privileges to remote connection,
- create database and table,
- connect to MySQL server via login, password, host and database.

Application uses:
- MySQL database.
- MySQL Connector/C++ version 8.0.
- Console.

Table schema:
- id_diary int auto_increment, 
- date text,
- content text. 
