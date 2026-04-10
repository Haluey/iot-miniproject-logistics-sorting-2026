#include "Food.h"
#include "ItemUtils.h"

Food::Food(int itemId, double weight, bool isFragile)
	:Item(itemId, ItemType::Food, weight, isFragile) {}

// 기본정보 확인
void Food::showInfo() {
	std::cout << "[Food] ID : " << itemId << ", Type : " << toString(type) << ", Weight : " << weight
			<< "kg, Fragile : " << toString(isFragile) << ", Status : " << toString(status) << std::endl;
	std::cout << "Info : Standard food item" << std::endl;
}

// 유효성 확인
bool Food::isValid() { return Item::isValid(); }