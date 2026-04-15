#ifndef FOOD_H
#define FOOD_H

#include "Item.h"

class Food : public Item {
private:


public:
	Food(double weight, bool isFragile);

	// 기본정보 확인
	void showInfo() const override;
	
	// 유효성 확인
	bool isValid() const override;
};

#endif