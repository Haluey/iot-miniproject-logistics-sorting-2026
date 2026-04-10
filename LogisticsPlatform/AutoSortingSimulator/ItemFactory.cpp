#include "ItemFactory.h"
#include "Food.h"
#include "Electronics.h"
#include "Fragile.h"

// 클래스 내부 함수
// ID 생성/관리 함수
int ItemFactory::generateId() {
	return nextId++;
}

// 랜덤 타입 함수
ItemType ItemFactory::generateRandomType() {
	std::uniform_int_distribution<int> dist(0, 2);
	int value = dist(gen);

	switch (value) {
	case 0:
		return ItemType::Food;
	case 1:
		return ItemType::Electronics;
	case 2:
		return ItemType::Fragile;
	default:
		return ItemType::Unknown;
	}
}

// 랜덤 무게 함수
double ItemFactory::generateRandomWeight() {
	std::uniform_real_distribution<double> dist(0.5, 20.0);

	return dist(gen);
}

// 랜덤 bool 함수
bool ItemFactory::generateRandomBool() {
	std::uniform_int_distribution<int> dist(0, 1);

	//return dist(gen) ? true : false;
	return dist(gen);
}

// 클래스 외부 함수
// 생성자
ItemFactory::ItemFactory() : nextId(1) {
	std::random_device rd;		// seed 생성기
	gen = std::mt19937(rd());	// 엔진 초기화
}

// 타입 지정 생성함수
std::shared_ptr<Item> ItemFactory::createItemByType(ItemType type, double weight, bool isFragile) {
	switch (type) {
	case ItemType::Food:
		return std::make_shared<Food>(generateId(), weight, isFragile);
		
	case ItemType::Electronics:
		return std::make_shared<Electronics>(generateId(), weight, isFragile);

	case ItemType::Fragile:
		return std::make_shared<Fragile>(generateId(), weight, isFragile);

	default:
		return nullptr;
	}
}

// 랜덤 물품 생성함수
std::shared_ptr<Item> ItemFactory::createRandomItem() {
	ItemType type = generateRandomType();
	bool isFragile = false;

	if (type == ItemType::Fragile) {
		isFragile = true;
	}
	else {
		isFragile = generateRandomBool();
	}

	return createItemByType(type, generateRandomWeight(), isFragile);
}