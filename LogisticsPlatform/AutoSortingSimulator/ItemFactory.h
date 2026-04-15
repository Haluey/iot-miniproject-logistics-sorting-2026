// ItemFactory를 통해 객체 생성 책임을 별도 클래스로 분리하였으며,
// Factory 패턴의 아이디어를 반영한 구조로 구현

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"
#include <random>

class ItemFactory {
private:
	std::mt19937 gen;	// 랜덤 엔진

	// 랜덤 타입 함수
	ItemType generateRandomType();

	// 랜덤 무게 함수
	double generateRandomWeight();

	// 랜덤 bool 함수
	bool generateRandomBool();

public:
	ItemFactory();

	// 타입 지정 생성함수
	std::shared_ptr<Item> createItemByType(ItemType type, double weight, bool isFragile);

	// 랜덤 물품 생성함수
	std::shared_ptr<Item> createRandomItem();
};

#endif