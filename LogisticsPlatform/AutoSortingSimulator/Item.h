#ifndef ITEM_H
#define ITEM_H

#include <iostream>

enum ItemType {
	Unknown,
	Food,
	Electronics,
	Fragile
};

enum ItemStatus {
	Created,	// 생성 직후
	Queued,		// 대기열 등록
	Processing,	// 물품 분류 중
	Sorted,		// 분류 완료
	Saved		// 저장 완료
};

class Item {
protected:
	int itemId;
	enum ItemType type;
	double weight;
	bool isFragile;
	enum ItemStatus status;
	
public:
	Item(int itemId, enum ItemType type, double weight, bool isFragile);
	// 가상 소멸자
	virtual ~Item();
	// 기본정보 확인
	virtual void showInfo();
	// 상태 변경
	void setStatus(enum ItemStatus newStatus);
	// 유효성 확인
	virtual bool isValid();	
};

#endif