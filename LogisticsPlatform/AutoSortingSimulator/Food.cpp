#include "Food.h"

Food::Food(double weight, bool isFragile)
	:Item(ItemType::Food, weight, isFragile) {}

// 기본정보 확인
void Food::showInfo() const {
	std::cout << "[Food] " << "Type: " << toString(type)
		<< ", Weight: " << weight << " kg"
		<< ", Fragile: " << toString(isFragile)
		<< ", Status: " << toString(status)
		<< ", Note: Standard food item" << std::endl;
}

// 유효성 확인
bool Food::isValid() const { return Item::isValid(); }