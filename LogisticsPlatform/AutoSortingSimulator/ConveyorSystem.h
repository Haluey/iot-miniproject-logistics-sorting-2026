#ifndef CONVEYORSYSTEM_H
#define CONVEYORSYSTEM_H

#include "Item.h"
#include <queue>

// 물품 등록, 추출, 상태 변경을 담당하는 클래스
class ConveyorSystem {
private:
	std::queue<std::shared_ptr<Item>> conveyorQueue;

public:
	// 물품 등록 함수
	void enqueueItem(std::shared_ptr<Item> incomingItem);

	// 다음 물품 추출 함수
	std::shared_ptr<Item> dequeueItem();

	// 비었는지 확인 함수
	bool isEmpty() const;

	// 현재 개수 확인 함수
	size_t getSize() const;

	// 맨 앞 확인 - 디버깅용
	void peekItem();

	// 전체 초기화 - 테스트용
	void clear();
};

#endif