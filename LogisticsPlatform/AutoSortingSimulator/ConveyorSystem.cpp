#include "ConveyorSystem.h"

// 비었는지 확인 함수
bool ConveyorSystem::isEmpty() const {
	return conveyorQueue.empty();
}

// 현재 개수 확인 함수
size_t ConveyorSystem::getSize() const {
	return conveyorQueue.size();
}

// 물품 등록 함수
void ConveyorSystem::enqueueItem(std::shared_ptr<Item> incomingItem) {
	if (incomingItem == nullptr) {
		std::cout << "유효하지 않은 물품입니다" << std::endl;
		return;
	}
	else {
		incomingItem->setStatus(ItemStatus::Queued);
		conveyorQueue.push(incomingItem);
		return;
	}
}

// 다음 물품 추출 함수
std::shared_ptr<Item> ConveyorSystem::dequeueItem() {
	if (!isEmpty()) {
		std::shared_ptr<Item> item = conveyorQueue.front();
		item->setStatus(ItemStatus::Processing);
		conveyorQueue.pop();
		return item;
	}
	else {
		std::cout << "현재 큐는 비어있습니다." << std::endl;
		return nullptr;
	}
}

// 맨 앞 확인 - 디버깅용. 나중에 반환?
void ConveyorSystem::peekItem() {
	if (!isEmpty()) {
		std::cout << "현재 큐의 맨 앞 데이터 : ";
		(conveyorQueue.front())->showInfo();
	}
	else {
		std::cout << "현재 큐는 비어있습니다." << std::endl;
	}	
}

// 전체 초기화 - 테스트용
void ConveyorSystem::clear() {
	conveyorQueue = std::queue<std::shared_ptr<Item>>();
}