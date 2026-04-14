// 스마트 물류 자동 분류 시뮬레이터

#include "ItemFactory.h"
#include "ConveyorSystem.h"
#include "Sorter.h"
#include "DatabaseManager.h"

int main(void) {
	ItemFactory itemFactory;
	ConveyorSystem conveyorSystem;
	Sorter sorter;
	DatabaseManager databaseManager;
	
	int processedCount = 1;

	if (!databaseManager.connect()) return 1;

	std::cout << "===== Creation Phase =====" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::shared_ptr<Item> createdItem = itemFactory.createRandomItem();
		std::cout << "[CREATE] Item generated" << std::endl;		

		conveyorSystem.enqueueItem(createdItem);	// 큐에 적재중
		std::cout << "[ENQUEUE] Added to conveyor (Queue Size: " << conveyorSystem.getSize() << ")" << std::endl;
		std::cout << std::endl;
	}

	std::cout << "===== Processing Phase =====" << std::endl;
	while (!conveyorSystem.isEmpty()) {
		std::cout << "===== Item #" << processedCount++ << " =====" << std::endl;

		std::shared_ptr<Item> currentItem = conveyorSystem.dequeueItem();
		std::cout << "[PROCESS] Item processing started" << std::endl;

		std::cout << "[INFO] ";
		currentItem->showInfo();
		
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

		std::cout << "----------------------------------------" << std::endl;
	}

	std::cout << "===== Statistics =====" << std::endl;
	databaseManager.printLineStatistics();
	databaseManager.printTypeStatistics();
	databaseManager.printWeightStatistics();

	std::cout << "===== Query Results =====" << std::endl;
	databaseManager.printItemsByLine("FragileLine");
	databaseManager.printTopNHeaviestItems(3);
	databaseManager.printRecentItems(5);

	databaseManager.disconnect();
	
	return 0;
}