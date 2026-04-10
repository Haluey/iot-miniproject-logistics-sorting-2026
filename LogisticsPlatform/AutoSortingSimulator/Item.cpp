#include "Item.h"
#include "ItemUtils.h"

// Item 클래스 멤버 함수
Item::Item(int itemId, ItemType type, double weight, bool isFragile) {
	this->itemId = itemId;
	this->type = type;
	this->weight = weight;
	this->isFragile = isFragile;
	status = ItemStatus::Created;
}

Item::~Item() {}

// 기본정보 확인
void Item::showInfo() {
	std::cout << "[Item] ID : " << itemId << ", Type : " << toString(type) << ", Weight : " << weight 
			<< "kg, Fragile : " << toString(isFragile) << ", Status : " << toString(status) << std::endl;
}

// 상태 변경
void Item::setStatus(ItemStatus newStatus) {
	status = newStatus;
}

// 유효성 확인
bool Item::isValid() {
	/*
	bool idValid = false, typeValid = false, weightValid = false;

	// 공통 유효성 검사
	// itemId가 음수가 아닌지
	if (itemId >= 0) {
		idValid = true;
	}

	// type이 Unknown이 아닌지
	if (type != ItemType::Unknown) {
		typeValid = true;
	}

	// weight가 0보다 큰지
	if (weight > 0) {
		weightValid = true;
	}

	// 최종 유효성 확인
	if (idValid && typeValid && weightValid) {
		return true;
	}
	else {
		return false;
	}
	*/
	return (itemId >= 0) && (type != ItemType::Unknown) && (weight > 0);
}

// Getter
double Item::getWeight() const { return weight; }

bool Item::getIsFragile() const { return isFragile; }