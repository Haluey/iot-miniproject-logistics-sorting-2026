#ifndef ITEM_H
#define ITEM_H

#include "ItemUtils.h"

class Item {
protected:
	ItemType type;
	double weight;
	bool isFragile;
	ItemStatus status;
	SortingLine sortingLine;
	
public:
	Item(ItemType type, double weight, bool isFragile);

	// 가상 소멸자
	virtual ~Item();

	// 기본정보 확인
	virtual void showInfo();

	// 유효성 확인
	virtual bool isValid();	

	// Setter
	void setStatus(ItemStatus newStatus);

	void setSortingLine(SortingLine newsortingLine);

	// Getter
	ItemType getType() const;

	double getWeight() const;

	bool getIsFragile() const;

	ItemStatus getStatus() const;

	SortingLine getSortingLine() const;
};

#endif