#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Item.h"
#include "QueryResultTypes.h"
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
	bool connect();

	// DB 종료 함수
	void disconnect();

	// DB 저장 함수
	void saveItem(const Item& item);

	// 통계 조회 함수
	// 라인별 개수 조회
	std::vector<LineStatistic> getLineStatistics();
		
	// 타입별 개수 조회
	std::vector<TypeStatistic> getTypeStatistics();

	// 라인별 평균 무게 조회
	std::vector<WeightStatistic> getWeightStatistics();

	// 조건 기반 조회 함수
	// 특정 라인에 배정된 물품 조회
	std::vector<ItemRecord> getItemsByLine(const std::string& lineName);

	// 무게 상위 N개 물품 조회
	std::vector<ItemRecord> getTopNHeaviestItems(int limit);

	// 최근 저장된 물품 조회
	std::vector<ItemRecord> getRecentItems(int limit);

	// 추후. getAllItems(), getItemsByLine(), clearTable(), createItemsTable(), isConnected()
};

#endif