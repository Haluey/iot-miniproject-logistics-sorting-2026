#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Item.h"
// MySQL Connector/C++ 헤더 
#include <mysql/jdbc.h>

class DatabaseManager {
private:
	sql::Driver* driver;
	std::unique_ptr<sql::Connection> conn;

	std::string dbUrl;
	std::string dbUser;
	std::string dbPassword;
	std::string schemaName;

public:
	DatabaseManager();

	// DB 연결 함수
	void connect();

	// DB 종료 함수
	void disconnect();

	// DB 저장 함수
	void saveItem(const Item& item);

	// 추후. getAllItems(), getItemsByLine(), clearTable(), createItemsTable(), isConnected()
};

#endif