#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
	: driver(nullptr),
	dbUrl("tcp://127.0.0.1"),
	dbUser("root"),
	dbPassword("my123456"),
	schemaName("logistics_db") {}

// DB 연결 함수
bool DatabaseManager::connect() {
	try {
		// MySQL Connector 내부에서 DB 연결을 만들어주는 객체
		driver = sql::mysql::get_driver_instance();
		// MySQL 서버에 실제 접속 시도.	성공하면 Connection 객체 반환
		// conn.reset(...) -> conn은 unique_ptr이기 때문에
		// 해당 함수를 쓰면 기존 객체 있을경우 자동 삭제되고, 새 연결 객체로 교체됨
		conn.reset(driver->connect(dbUrl, dbUser, dbPassword));
		// 사용할 DB선택
		conn->setSchema(schemaName);

		std::cout << "[DB] Connection established." << std::endl;
		std::cout << std::endl;
		
		return true;
	}
	catch (sql::SQLException& e) {
		std::cout << "[DB] Connection failed." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;	// 에러 메시지
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;	// MySQL 에러 번호
		std::cout << "SQLState: " << e.getSQLState() << std::endl;	// SQL 상태 코드

		return false;
	}
}

// DB 종료 함수
void DatabaseManager::disconnect() {
	if (conn) {
		conn->close();	// DB 연결 종료
		conn.reset();	// 포인터 제거, 메모리 해제
		std::cout << "[DB] Connection closed." << std::endl;
	}
}

// DB 저장 함수
void DatabaseManager::saveItem(const Item& item) {
	if (!conn) {
		std::cout << "[SAVE] No database connection." << std::endl;
		return;
	}

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(
			conn->prepareStatement(	// SQL 문을 미리 준비
				"INSERT INTO items "
				"(item_type, weight, is_fragile, status, sorting_line) "
				"VALUES (?, ?, ?, ?, ?)"
			)
		);

		// ?에 C++값으로 채워넣기
		pstmt->setString(1, toString(item.getType()));
		pstmt->setDouble(2, item.getWeight());
		pstmt->setBoolean(3, item.getIsFragile());
		pstmt->setString(4, toString(item.getStatus()));
		pstmt->setString(5, toString(item.getSortingLine()));

		// 실제로 INSERT실행 여기서 DB 저장
		pstmt->executeUpdate();

		std::cout << "[SAVE] Item saved to database" << std::endl;
	}
	catch (sql::SQLException& e) {
		std::cout << "[SAVE] Failed to save item to database." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;
	}
}

// 통계 조회 함수
// 라인별 개수 조회
std::vector<LineStatistic> DatabaseManager::getLineStatistics() {
	std::vector<LineStatistic> results;

	if (!conn) {
		std::cout << "[STAT] No database connection." << std::endl;
		return results;
	}

	try {
		// SQL을 실행할 Statement 객체 생성
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());

		std::unique_ptr<sql::ResultSet> res(
			stmt->executeQuery( // 결과 집합 반환(SELECT용 실행 함수)
				"SELECT sorting_line, COUNT(*)"
				"  FROM items"
				" GROUP BY sorting_line"
				" ORDER BY COUNT(*) DESC"
			)
		);		

		// res->next() : 다음 행으로 이동하는 함수
		while (res->next()) {
			LineStatistic stat;
			stat.lineName = res->getString(1);
			stat.itemCount = res->getInt(2);

			results.push_back(stat);
		}

		return results;
	}
	catch (sql::SQLException& e) {
		std::cout << "[STAT] Failed to retrieve statistics." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;

		return results;
	}
}

// 타입별 개수 조회
std::vector<TypeStatistic> DatabaseManager::getTypeStatistics() {
	std::vector<TypeStatistic> results;

	if (!conn) {
		std::cout << "[STAT] No database connection." << std::endl;
		return results;
	}

	try {
		// SQL을 실행할 Statement 객체 생성
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());

		std::unique_ptr<sql::ResultSet> res(
			stmt->executeQuery( // 결과 집합 반환(SELECT용 실행 함수)
				"SELECT item_type, COUNT(*)"
				"  FROM items"
				" GROUP BY item_type"
				" ORDER BY COUNT(*) DESC"
			)
		);

		// res->next() : 다음 행으로 이동하는 함수
		while (res->next()) {
			TypeStatistic stat;
			stat.typeName = res->getString(1);
			stat.itemCount = res->getInt(2);

			results.push_back(stat);
		}

		return results;
	}
	catch (sql::SQLException& e) {
		std::cout << "[STAT] Failed to retrieve statistics." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;

		return results;
	}
}

// 라인별 평균 무게 조회
std::vector<WeightStatistic> DatabaseManager::getWeightStatistics() {
	std::vector<WeightStatistic> results;

	if (!conn) {
		std::cout << "[STAT] No database connection." << std::endl;
		return results;
	}

	try {
		// SQL을 실행할 Statement 객체 생성
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());

		std::unique_ptr<sql::ResultSet> res(
			stmt->executeQuery( // 결과 집합 반환(SELECT용 실행 함수)
				"SELECT sorting_line, AVG(weight) AS avg_weight"
				"  FROM items"
				" GROUP BY sorting_line"
				" ORDER BY avg_weight DESC"
			)
		);

		// res->next() : 다음 행으로 이동하는 함수
		while (res->next()) {
			WeightStatistic stat;
			stat.lineName = res->getString(1);
			stat.averageWeight = res->getDouble(2);

			results.push_back(stat);
		}

		return results;
	}
	catch (sql::SQLException& e) {
		std::cout << "[STAT] Failed to retrieve statistics." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;

		return results;
	}	
}

// 조건 기반 조회 함수
// 특정 라인에 배정된 물품 조회
std::vector<ItemRecord> DatabaseManager::getItemsByLine(const std::string& lineName) {
	std::vector<ItemRecord> results;
	
	if (!conn) {
		std::cout << "[QUERY] No database connection." << std::endl;
		return results;
	}

	try {
		// SQL을 실행할 PreparedStatement 객체 생성
		std::unique_ptr<sql::PreparedStatement> pstmt(
			conn->prepareStatement(
				"SELECT item_type, weight, is_fragile"
				"     , status, sorting_line"
				// CONVERT_TZ(시간, 원래시간대, 바꿀시간대)
				// DB 저장 시간은 UTC 기준, 조회 시 KST 변환
				"	  , CONVERT_TZ(saved_at, '+00:00', '+09:00')"	
				"  FROM items"
				" WHERE sorting_line = ?"
				" ORDER BY saved_at DESC"
			)
		);
		pstmt->setString(1, lineName);

		std::unique_ptr<sql::ResultSet> res(
			pstmt->executeQuery()
		);

		// res->next() : 다음 행으로 이동하는 함수
		while (res->next()) {
			ItemRecord record;

			record.typeName = res->getString(1);
			record.weight = res->getDouble(2);
			record.fragileFlag = res->getBoolean(3);
			record.statusName = res->getString(4);
			record.lineName = res->getString(5);
			record.savedAt = res->getString(6);

			results.push_back(record);
		}

		return results;
	}
	catch (sql::SQLException& e) {
		std::cout << "[QUERY] Failed to retrieve data." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;

		return results;
	}
}

// 무게 상위 N개 물품 조회
std::vector<ItemRecord> DatabaseManager::getTopNHeaviestItems(int limit) {
	std::vector<ItemRecord> results;
	
	if (!conn) {
		std::cout << "[QUERY] No database connection." << std::endl;
		return results;
	}

	try {
		// SQL을 실행할 PreparedStatement 객체 생성
		std::unique_ptr<sql::PreparedStatement> pstmt(
			conn->prepareStatement(
				"SELECT item_type, weight, sorting_line"
				// CONVERT_TZ(시간, 원래시간대, 바꿀시간대)
				// DB 저장 시간은 UTC 기준, 조회 시 KST 변환
				"     , CONVERT_TZ(saved_at, '+00:00', '+09:00')"
				"  FROM items"
				" ORDER BY weight DESC"
				" LIMIT ?"
			)
		);
		pstmt->setInt(1, limit);

		std::unique_ptr<sql::ResultSet> res(
			pstmt->executeQuery()
		);

		// res->next() : 다음 행으로 이동하는 함수
		while (res->next()) {
			ItemRecord record;

			record.typeName = res->getString(1);
			record.weight = res->getDouble(2);
			record.lineName = res->getString(3);
			record.savedAt = res->getString(4);

			results.push_back(record);
		}

		return results;
	}
	catch (sql::SQLException& e) {
		std::cout << "[QUERY] Failed to retrieve data." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;

		return results;
	}
}

// 최근 저장된 물품 조회
std::vector<ItemRecord> DatabaseManager::getRecentItems(int limit) {
	std::vector<ItemRecord> results;

	if (!conn) {
		std::cout << "[QUERY] No database connection." << std::endl;
		return results;
	}

	try {
		// SQL을 실행할 PreparedStatement 객체 생성
		std::unique_ptr<sql::PreparedStatement> pstmt(
			conn->prepareStatement(
				"SELECT item_type, weight, sorting_line, status"
				// CONVERT_TZ(시간, 원래시간대, 바꿀시간대)
				// DB 저장 시간은 UTC 기준, 조회 시 KST 변환
				"	  , CONVERT_TZ(saved_at, '+00:00', '+09:00')"
				"  FROM items"
				" ORDER BY saved_at DESC"
				" LIMIT ?"
			)
		);
		pstmt->setInt(1, limit);

		std::unique_ptr<sql::ResultSet> res(
			pstmt->executeQuery()
		);

		// res->next() : 다음 행으로 이동하는 함수
		while (res->next()) {
			ItemRecord record;

			record.typeName = res->getString(1);
			record.weight = res->getDouble(2);
			record.lineName = res->getString(3);
			record.statusName = res->getString(4);
			record.savedAt = res->getString(5);

			results.push_back(record);
		}

		return results;
	}
	catch (sql::SQLException& e) {
		std::cout << "[QUERY] Failed to retrieve data." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;

		return results;
	}
}