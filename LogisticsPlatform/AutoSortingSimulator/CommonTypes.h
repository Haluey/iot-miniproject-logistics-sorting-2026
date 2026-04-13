#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <iostream>

enum class ItemType {
	Unknown,
	Food,
	Electronics,
	Fragile
};

enum class ItemStatus {
	Created,	// 생성 직후
	Queued,		// 대기열 등록
	Processing,	// 물품 분류 중
	Sorted,		// 분류 완료
	Saved		// 저장 완료
};

enum class SortingLine {
	Unassigned,
	FragileLine,
	CautionLine,
	SmallLine,
	LargeLine
};

#endif