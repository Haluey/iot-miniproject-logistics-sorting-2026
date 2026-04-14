#include "Item.h"
#include <cmath>

// Item 클래스 멤버 함수
Item::Item(ItemType type, double weight, bool isFragile) {
	this->type = type;
	this->weight = round(weight * 100) / 100;
	this->isFragile = isFragile;
	status = ItemStatus::Created;
	sortingLine = SortingLine::Unassigned;
}

Item::~Item() {}

// 기본정보 확인
void Item::showInfo() {
	std::cout << "[Item] " << "Type : " << toString(type) << ", Weight : " << weight 
			<< "kg, Fragile : " << toString(isFragile) << ", Status : " << toString(status) << std::endl;
}

// 유효성 확인
bool Item::isValid() {
	/*
	bool idValid = false, typeValid = false, weightValid = false;

	// 공통 유효성 검사
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
	return (type != ItemType::Unknown) && (weight > 0);
}

// Setter
void Item::setStatus(ItemStatus newStatus) { status = newStatus; }

void Item::setSortingLine(SortingLine newsortingLine) { sortingLine = newsortingLine; }

// Getter
ItemType Item::getType() const { return type; }

double Item::getWeight() const { return weight; }

bool Item::getIsFragile() const { return isFragile; }

ItemStatus Item::getStatus() const { return status; }

SortingLine Item::getSortingLine() const { return sortingLine; }