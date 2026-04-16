// 물류 처리 시뮬레이션의 전체 흐름을 관리하는 클래스
// 물품 생성, 큐 적재, 처리, 분류, 저장까지의 자동 실행 흐름을 담당

#ifndef LOGISTICSSERVICE_H
#define LOGISTICSSERVICE_H

#include "ItemFactory.h"
#include "ConveyorSystem.h"
#include "Sorter.h"
#include "DatabaseManager.h"
#include "ReportPrinter.h"

class LogisticsService {
private:
	ItemFactory itemFactory;
	ConveyorSystem conveyorSystem;
	Sorter sorter;
	DatabaseManager& databaseManager;
	ReportPrinter reportPrinter;
	int cycleCount;

	void clearScreen();
	void pauseScreen();
	void clearInputBuffer();

	// 물품을 1개 생성하고 컨베이어 큐에 적재하는 함수
	void generateAndEnqueueItem();

	// 큐에서 물품을 1개 꺼내 처리(분류, 유효성 검사, DB 저장)하는 함수
	void processNextItem();

	// 자동 실행의 한 사이클
	// (물품 생성 → 큐 적재 → 1개 처리)
	void runOneCycle();


	// 관리자 메인 메뉴 출력 함수
	void showAdminMenu();

	// 통계 조회 메뉴 출력 함수
	void showStatisticsMenu();
	// 통계 조회 메뉴 입력 처리 함수
	void handleStatisticsMenu();

	// 조건 기반 조회 메뉴 출력 함수
	void showQueryMenu();
	// 조건 기반 조회 메뉴 입력 처리 함수
	void handleQueryMenu();

	// 특정 라인 물품 조회 처리 함수
	void handleItemsByLineQuery();
	// 무게 상위 N개 조회 처리 함수
	void handleTopNQuery();
	// 최근 저장된 물품 조회 처리 함수
	void handleRecentItemsQuery();

public:
	LogisticsService(DatabaseManager& databaseManager);	

	// 일정 시간 간격으로 runOneCycle을 반복 실행하는 함수
	// (intervalSeconds: 실행 주기(초))
	void runAutoMode(int intervalSeconds);

	// 관리자 메인 메뉴 입력 처리 함수
	void handleAdminMenu();

	void runInteractiveAutoMode(int intervalSeconds);
};

#endif