// 스마트 물류 자동 분류 시뮬레이터

#include "ItemFactory.h"
#include "ConveyorSystem.h"

int main(void) {
	ItemFactory itemFactory;
	ConveyorSystem conveyorSystem;

	for (int i = 0; i < 5; i++) {
		std::shared_ptr<Item> createdItem = itemFactory.createRandomItem();
		conveyorSystem.enqueueItem(createdItem);	// 큐에 적재중
		createdItem->showInfo();
		std::cout << conveyorSystem.getSize() << std::endl;
	}

	while (!conveyorSystem.isEmpty()) {
		std::shared_ptr<Item> currentItem = conveyorSystem.dequeueItem();
		currentItem->showInfo();
		std::cout << "유효 :" << currentItem->isValid() << std::endl;
	}

	return 0;
}