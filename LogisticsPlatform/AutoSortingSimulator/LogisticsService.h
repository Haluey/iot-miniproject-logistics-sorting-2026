// 물류 처리 시뮬레이션의 전체 흐름을 관리하는 클래스
// 물품 생성, 큐 적재, 처리, 분류, 저장까지의 자동 실행 흐름을 담당

#ifndef LOGISTICSSERVICE_H
#define LOGISTICSSERVICE_H

#include "ItemFactory.h"
#include "ConveyorSystem.h"
#include "Sorter.h"
#include "DatabaseManager.h"

class LogisticsService {
private:
	ItemFactory itemFactory;
	ConveyorSystem conveyorSystem;
	Sorter sorter;
	DatabaseManager& databaseManager;
	//ReportPrinter
	int cycleCount;

public:
	LogisticsService(DatabaseManager& databaseManager);

	// 물품을 1개 생성하고 컨베이어 큐에 적재하는 함수
	void generateAndEnqueueItem();

	// 큐에서 물품을 1개 꺼내 처리(분류, 유효성 검사, DB 저장)하는 함수
	void processNextItem();

	// 자동 실행의 한 사이클
	// (물품 생성 → 큐 적재 → 1개 처리)
	void runOneCycle();

	// 일정 시간 간격으로 runOneCycle을 반복 실행하는 함수
	// (intervalSeconds: 실행 주기(초))
	void runAutoMode(int intervalSeconds);
};

#endif