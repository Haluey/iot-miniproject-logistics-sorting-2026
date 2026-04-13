// 스마트 물류 자동 분류 시뮬레이터

#include "ItemFactory.h"
#include "ConveyorSystem.h"
#include "Sorter.h"
#include "DatabaseManager.h"

int main(void) {
	ItemFactory itemFactory;
	ConveyorSystem conveyorSystem;
	Sorter sorter;
	DatabaseManager databaseManeger;
	databaseManeger.connect();
	int processedCount = 1;

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

		databaseManeger.saveItem(*currentItem);
		// ItemStatus를 Saved로 바꾸어야 하지 않는가?

		std::cout << "[VALID] " << toString(currentItem->isValid()) << std::endl;

		std::cout << "----------------------------------------" << std::endl;
	}

	databaseManeger.disconnect();
	
	return 0;
}