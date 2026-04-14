#ifndef FRAGILE_H
#define FRAGILE_H

#include "Item.h"

class Fragile : public Item {
private:


public:
	Fragile(double weight, bool isFragile);

	// 기본정보 확인
	void showInfo() override;

	// 유효성 확인
	bool isValid() override;
};

#endif