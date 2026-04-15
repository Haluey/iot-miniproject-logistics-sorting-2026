#include "LogisticsService.h"
#include <thread>
#include <chrono>

// 생성자
LogisticsService::LogisticsService(DatabaseManager& databaseManager)
	: databaseManager(databaseManager), cycleCount(0) {}

// 물품을 1개 생성하고 컨베이어 큐에 적재하는 함수
void LogisticsService::generateAndEnqueueItem() {
	std::shared_ptr<Item> createdItem = itemFactory.createRandomItem();
	std::cout << "[CREATE] Item generated." << std::endl;

	conveyorSystem.enqueueItem(createdItem);	// 큐에 적재중
	std::cout << "[ENQUEUE] Added to conveyor (Queue Size: " << conveyorSystem.getSize() << ")" << std::endl;
}

// 큐에서 물품을 1개 꺼내 처리(분류, 유효성 검사, DB 저장)하는 함수
void LogisticsService::processNextItem() {
	if (conveyorSystem.isEmpty()) {
		std::cout << "[PROCESS] No item to process. Queue is empty." << std::endl;
		return;
	}

	std::shared_ptr<Item> currentItem = conveyorSystem.dequeueItem();
	std::cout << "[PROCESS] Item processing started." << std::endl;

	std::cout << "[INFO] ";	currentItem->showInfo();

	currentItem->setSortingLine(sorter.sortItem(currentItem));
	currentItem->setStatus(ItemStatus::Sorted);
	std::cout << "[SORT] Assigned Line: " << toString(currentItem->getSortingLine()) << std::endl;

	bool isItemValid = currentItem->isValid();
	std::cout << "[VALID] " << toString(isItemValid) << std::endl;

	if (isItemValid) {
		currentItem->setStatus(ItemStatus::Saved);
		// 매개변수는 참조자가 맞지만, currentItem의 타입이 포인터기 때문에
		// 실제 Item 객체를 참조로 받겠다라는 의미로 *(포인터 연산자)를 붙임
		databaseManager.saveItem(*currentItem);
	}
	else {
		std::cout << "[SAVE] Invalid item. Save skipped." << std::endl;
	}	
}

// 자동 실행의 한 사이클
// (물품 생성 → 큐 적재 → 1개 처리)
void LogisticsService::runOneCycle() {
	std::cout << "===== Auto Cycle #" << ++cycleCount << " =====" << std::endl;

	generateAndEnqueueItem();
	processNextItem();

	std::cout << "----------------------------------------" << std::endl;
}

// 일정 시간 간격으로 runOneCycle을 반복 실행하는 함수
// (intervalSeconds: 실행 주기(초))
void LogisticsService::runAutoMode(int intervalSeconds) {
	for (int i = 0; i < 5; i++) {
		runOneCycle();
		std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));
	}
}