#ifndef SORTER_H
#define SORTER_H

#include "Item.h"

class Sorter {
private:
	

public:
	// Item 하나 받아서 분류 결과 하나 반환하는 함수
	SortingLine sortItem(std::shared_ptr<Item> item);

	// (추후)기준 확인 보조 함수(Fragile 판단, Weight 기준 판단)

};

#endif