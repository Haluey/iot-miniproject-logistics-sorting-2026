#ifndef SORTER_H
#define SORTER_H

#include "Item.h"

enum class SortingLine {
	FragileLine,
	CautionLine,
	SmallLine,
	LargeLine
};

class Sorter {
private:
	

public:
	// Item 하나 받아서 분류 결과 하나 반환하는 함수
	SortingLine sortItem(std::shared_ptr<Item> item);
};

#endif