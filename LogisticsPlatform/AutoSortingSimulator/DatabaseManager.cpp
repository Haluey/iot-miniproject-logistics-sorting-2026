#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
	: driver(nullptr),
	dbUrl("tcp://127.0.0.1"),
	dbUser("root"),
	dbPassword("my123456"),
	schemaName("logistics_db") {}

// DB 연결 함수
void DatabaseManager::connect() {
	try {
		// MySQL Connector 내부에서 DB 연결을 만들어주는 객체
		driver = sql::mysql::get_driver_instance();
		// MySQL 서버에 실제 접속 시도.	성공하면 Connection 객체 반환
		// conn.reset(...) -> conn은 unique_ptr이기 때문에
		// 해당 함수를 쓰면 기존 객체 있을경우 자동 삭제되고, 새 연결 객체로 교체됨
		conn.reset(driver->connect(dbUrl, dbUser, dbPassword));
		// 사용할 DB선택
		conn->setSchema(schemaName);

		std::cout << "DB 연결 성공!" << std::endl;
	}
	catch (sql::SQLException& e) {
		std::cout << "DB 연결 실패" << std::endl;
		std::cout << "Error: " << e.what() << std::endl;	// 에러 메시지
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;	// MySQL 에러 번호
		std::cout << "SQLState: " << e.getSQLState() << std::endl;	// SQL 상태 코드
	}
}

// DB 종료 함수
void DatabaseManager::disconnect() {
	if (conn) {
		conn->close();	// DB 연결 종료
		conn.reset();	// 포인터 제거, 메모리 해제
		std::cout << "DB 연결 종료" << std::endl;
	}
}

// DB 저장 함수
void DatabaseManager::saveItem(const Item& item) {
	if (!conn) {
		std::cout << "[SAVE] DB 연결이 없습니다." << std::endl;
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
		std::cout << "[SAVE] DB 저장 실패" << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Error Code: " << e.getErrorCode() << std::endl;
		std::cout << "SQLState: " << e.getSQLState() << std::endl;
	}
}