#include "Fragile.h"

Fragile::Fragile(int itemId, double weight, bool isFragile)
	:Item(itemId, ItemType::Fragile, weight, isFragile) {}

// 기본정보 확인
void Fragile::showInfo() {
	std::cout << "[Fragile] ID : " << itemId << ", Type : " << toString(type) << ", Weight : " << weight
		<< "kg, Fragile : " << toString(isFragile) << ", Status : " << toString(status) << std::endl;
	std::cout << "Warning : Handle with care" << std::endl;
}

// 유효성 확인
bool Fragile::isValid() {
	/*
	bool fragileValid = false;

	// 타입별 유효성 검사
	// Fragile 타입이면 isFragile가 true인지
	if (isFragile == true) {
		fragileValid = true;
	}

	// 최종 유효성 확인
	if (Item::isValid() && fragileValid) {
		return true;
	}
	else {
		return false;
	}
	*/
	return Item::isValid() && isFragile;
}