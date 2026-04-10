#ifndef FOOD_H
#define FOOD_H

#include "Item.h"

class Food : public Item {
private:


public:
	Food(int itemId, double weight, bool isFragile);

	// 기본정보 확인
	void showInfo() override;
	
	// 유효성 확인
	bool isValid() override;
};

#endif