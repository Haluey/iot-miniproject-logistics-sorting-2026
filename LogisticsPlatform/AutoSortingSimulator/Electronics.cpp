#include "Electronics.h"

Electronics::Electronics(double weight, bool isFragile)
	:Item(ItemType::Electronics, weight, isFragile) {}

// 기본정보 확인
void Electronics::showInfo() const {
	std::cout << "[Electronics] " << "Type: " << toString(type)
		<< ", Weight: " << weight << " kg"
		<< ", Fragile: " << toString(isFragile)
		<< ", Status: " << toString(status) 
		<< ", Note: Requires careful handling." << std::endl;
}

// 유효성 확인
bool Electronics::isValid() const { return Item::isValid(); }