#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Item.h"

class Electronics : public Item {
private:


public:
	Electronics(int itemId, double weight, bool isFragile);

	// 기본정보 확인
	void showInfo() override;

	// 유효성 확인
	bool isValid() override;
};

#endif