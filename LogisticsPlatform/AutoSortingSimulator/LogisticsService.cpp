#include "LogisticsService.h"
#include <thread>
#include <chrono>
#include <limits>

// private
void LogisticsService::clearScreen() {
	system("cls");
}
void LogisticsService::pauseScreen() {
	std::cout << "\nPress Enter to return to menu...";
	std::cin.get();      // 새로운 Enter 입력 기다림
}
void LogisticsService::clearInputBuffer() {
	// 현재 입력 버퍼에 남아 있는 문자들을 줄 끝('\n')까지 전부 버림
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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
	std::cout << "\n===== Auto Cycle #" << ++cycleCount << " =====" << std::endl;

	generateAndEnqueueItem();
	processNextItem();

	std::cout << "----------------------------------------" << std::endl;
}


// 관리자 메인 메뉴 출력 함수
void LogisticsService::showAdminMenu() {
	std::cout << "===== Admin Menu =====" << std::endl;
	std::cout << "1. Statistics" << std::endl;
	std::cout << "2. Query Results" << std::endl;
	std::cout << "0. Exit" << std::endl;
	std::cout << "Select menu: ";
}

// 통계 조회 메뉴 출력 함수
void LogisticsService::showStatisticsMenu() {
	std::cout << "===== Statistics Menu =====" << std::endl;
	std::cout << "1. Line Statistics" << std::endl;
	std::cout << "2. Type Statistics" << std::endl;
	std::cout << "3. Weight Statistics" << std::endl;
	std::cout << "0. Back" << std::endl;
	std::cout << "Select menu: ";		
}
// 통계 조회 메뉴 입력 처리 함수
void LogisticsService::handleStatisticsMenu() {	
	while (true) {
		int menuChoice;
		
		clearScreen();
		showStatisticsMenu();

		if (!(std::cin >> menuChoice)) {
			std::cin.clear();
			clearInputBuffer();
			std::cout << "[MENU] Invalid input. Please enter a number." << std::endl;
			pauseScreen();
			continue;
		}
		clearInputBuffer();

		switch (menuChoice) {
		case 1:
			reportPrinter.printLineStatistics(databaseManager.getLineStatistics());
			pauseScreen();
			break;
		case 2:
			reportPrinter.printTypeStatistics(databaseManager.getTypeStatistics());
			pauseScreen();
			break;
		case 3:
			reportPrinter.printWeightStatistics(databaseManager.getWeightStatistics());
			pauseScreen();
			break;
		case 0:
			return;
		default:
			std::cout << "[MENU] Invalid input. Please try again." << std::endl;
			pauseScreen();
		}
	}
}

// 조건 기반 조회 메뉴 출력 함수
void LogisticsService::showQueryMenu() {
	std::cout << "===== Query Results Menu =====" << std::endl;
	std::cout << "1. Items By Line" << std::endl;
	std::cout << "2. Top N Heaviest Items" << std::endl;
	std::cout << "3. Recent Items" << std::endl;
	std::cout << "0. Back" << std::endl;
	std::cout << "Select menu: ";
}
// 조건 기반 조회 메뉴 입력 처리 함수
void LogisticsService::handleQueryMenu() {	
	while (true) {
		int menuChoice;
		
		clearScreen();
		showQueryMenu();

		if (!(std::cin >> menuChoice)) {
			std::cin.clear();
			clearInputBuffer();
			std::cout << "[MENU] Invalid input. Please enter a number." << std::endl;
			pauseScreen();
			continue;
		}
		clearInputBuffer();

		switch (menuChoice) {
		case 1:
			handleItemsByLineQuery();
			break;
		case 2:
			handleTopNQuery();
			break;
		case 3:
			handleRecentItemsQuery();
			break;
		case 0:
			return;
		default:
			std::cout << "[MENU] Invalid input. Please try again." << std::endl;
			pauseScreen();
		}
	}
}

// 특정 라인 물품 조회 처리 함수
void LogisticsService::handleItemsByLineQuery() {
	int lineChoice;
	std::string lineName;

	std::cout << "\n===== Items By Line =====" << std::endl;
	std::cout << "1. FragileLine" << std::endl;
	std::cout << "2. CautionLine" << std::endl;
	std::cout << "3. SmallLine" << std::endl;
	std::cout << "4. LargeLine" << std::endl;
	std::cout << "Select line: ";
	
	if (!(std::cin >> lineChoice)) {
		std::cin.clear();
		clearInputBuffer();
		std::cout << "[QUERY] Invalid input. Please enter a number." << std::endl;
		pauseScreen();
		return;
	}
	clearInputBuffer();

	switch (lineChoice) {
	case 1:
		lineName = "FragileLine";
		break;
	case 2:
		lineName = "CautionLine";
		break;
	case 3:
		lineName = "SmallLine";
		break;
	case 4:
		lineName = "LargeLine";
		break;
	default:
		std::cout << "[QUERY] Invalid line selection." << std::endl;
		return;
	}
	
	reportPrinter.printItemsByLine(databaseManager.getItemsByLine(lineName), lineName);
	pauseScreen();
}
// 무게 상위 N개 조회 처리 함수
void LogisticsService::handleTopNQuery() {
	int limit;

	std::cout << "\n===== Top N Heaviest Items =====" << std::endl;
	std::cout << "Enter N: ";

	if (!(std::cin >> limit)) {
		std::cin.clear();
		clearInputBuffer();
		std::cout << "[QUERY] Invalid input. Please enter a number." << std::endl;
		pauseScreen();
		return;
	}
	clearInputBuffer();

	if (limit > 0) {
		reportPrinter.printTopNHeaviestItems(databaseManager.getTopNHeaviestItems(limit), limit);
	}
	else {
		std::cout << "[QUERY] Limit must be greater than 0." << std::endl;
	}
	pauseScreen();
}
// 최근 저장된 물품 조회 처리 함수
void LogisticsService::handleRecentItemsQuery() {
	int limit;

	std::cout << "\n===== Recent N Items =====" << std::endl;
	std::cout << "Enter number of recent items: ";

	if (!(std::cin >> limit)) {
		std::cin.clear();
		clearInputBuffer();
		std::cout << "[QUERY] Invalid input. Please enter a number." << std::endl;
		pauseScreen();
		return;
	}
	clearInputBuffer();

	if (limit > 0) {
		reportPrinter.printRecentItems(databaseManager.getRecentItems(limit), limit);
	}
	else {
		std::cout << "[QUERY] Limit must be greater than 0." << std::endl;
	}
	pauseScreen();
}


// public
// 생성자
LogisticsService::LogisticsService(DatabaseManager& databaseManager)
	: databaseManager(databaseManager), cycleCount(0) {}

// 일정 시간 간격으로 runOneCycle을 반복 실행하는 함수
// (intervalSeconds: 실행 주기(초))
void LogisticsService::runAutoMode(int intervalSeconds) {
	for (int i = 0; i < 5; i++) {
		runOneCycle();
		std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));
	}
}

// 관리자 메인 메뉴 입력 처리 함수
void LogisticsService::handleAdminMenu() {
	while (true) {
		int menuChoice;

		clearScreen();
		showAdminMenu();

		if (!(std::cin >> menuChoice)) {
			std::cin.clear();          // fail 상태 초기화
			clearInputBuffer();        // 버퍼 비우기
			std::cout << "[MENU] Invalid input. Please enter a number." << std::endl;
			pauseScreen();
			continue;
		}
		clearInputBuffer();

		switch (menuChoice) {
		case 1:
			handleStatisticsMenu();
			break;
		case 2:
			handleQueryMenu();
			break;
		case 0:
			clearScreen();
			return;
		default:
			std::cout << "[MENU] Invalid input. Please try again." << std::endl;
			pauseScreen();
		}
	}
}

// 자동 물류 처리 시뮬레이션을 실행하면서 사용자 입력을 동시에 처리하는 함수
void LogisticsService::runInteractiveAutoMode(int intervalSeconds) {
	while (true) {
		int delayPerDot = (intervalSeconds * 1000) / 3;
		std::string command;

		runOneCycle();

		std::cout << "\nPress Enter to continue, [m] for menu, [q] to quit: ";
		std::getline(std::cin, command);

		if (command.empty()) {
			std::cout << "Processing";

			for (int i = 0; i < 3; i++) {	// 점 3개 애니메이션
				std::cout << "." << std::flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(delayPerDot));
			}
			std::cout << "\r" << std::string(30, ' ') << "\r";	// 한 줄 지우기
		}
		else if (command == "m" || command == "M") {
			handleAdminMenu();
			std::cout << "Processing";

			for (int i = 0; i < 3; i++) {	// 점 3개 애니메이션
				std::cout << "." << std::flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(delayPerDot));
			}
			std::cout << "\r" << std::string(30, ' ') << "\r";	// 한 줄 지우기
		}
		else if (command == "q" || command == "Q") {
			return;
		}
		else {
			std::cout << "[MENU] Invalid command. Press Enter to continue." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));
		}		
	}
}