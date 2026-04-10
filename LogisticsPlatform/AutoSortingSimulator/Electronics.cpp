#include "Electronics.h"
#include "ItemUtils.h"

Electronics::Electronics(int itemId, double weight, bool isFragile)
	:Item(itemId, ItemType::Electronics, weight, isFragile) {}

// 기본정보 확인
void Electronics::showInfo() {
	std::cout << "[Electronics] ID : " << itemId << ", Type : " << toString(type) << ", Weight : " << weight
		<< "kg, Fragile : " << toString(isFragile) << ", Status : " << toString(status) << std::endl;
	std::cout << "Info : Electronic item, check handling condition" << std::endl;
}

// 유효성 확인
bool Electronics::isValid() { return Item::isValid(); }