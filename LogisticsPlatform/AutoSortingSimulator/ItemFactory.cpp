// ItemFactory를 통해 객체 생성 책임을 별도 클래스로 분리하였으며,
// Factory 패턴의 아이디어를 반영한 구조로 구현

#include "ItemFactory.h"
#include "Food.h"
#include "Electronics.h"
#include "Fragile.h"

// 클래스 내부 함수
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
	std::bernoulli_distribution dist(0.2);	// true가 나올 확률: 20%

	//return dist(gen) ? true : false;
	return dist(gen);
}

// 클래스 외부 함수
// 생성자
ItemFactory::ItemFactory() {
	std::random_device rd;		// seed 생성기
	gen = std::mt19937(rd());	// 엔진 초기화
}

// 타입 지정 생성함수
std::shared_ptr<Item> ItemFactory::createItemByType(ItemType type, double weight, bool isFragile) {
	switch (type) {
	case ItemType::Food:
		// 객체를 힙에 생성하고, shared_ptr로 안전하게 관리하면서 
		// 부모 타입(shared_ptr<Item>)으로 반환하기 위한 코드
		return std::make_shared<Food>(weight, isFragile);
		
	case ItemType::Electronics:
		return std::make_shared<Electronics>(weight, isFragile);

	case ItemType::Fragile:
		return std::make_shared<Fragile>(weight, isFragile);

	default:
		return nullptr;
	}
}

// 랜덤 물품 생성함수
std::shared_ptr<Item> ItemFactory::createRandomItem() {
	ItemType type = generateRandomType();
	bool isFragile = (type == ItemType::Fragile) ? true : generateRandomBool();

	return createItemByType(type, generateRandomWeight(), isFragile);
}