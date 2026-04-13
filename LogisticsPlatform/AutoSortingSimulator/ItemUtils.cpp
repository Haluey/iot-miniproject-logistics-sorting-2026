#include "ItemUtils.h"

// 문자열 변환 함수(오버로딩)
std::string toString(ItemType type) {
	switch (type) {
	case ItemType::Unknown:
		return "Unknown";
	case ItemType::Food:
		return "Food";
	case ItemType::Electronics:
		return "Electronics";
	case ItemType::Fragile:
		return "Fragile";
	default:
		return "InvalidType";
	}
}

std::string toString(ItemStatus status) {
	switch (status) {
	case ItemStatus::Created:
		return "Created";
	case ItemStatus::Queued:
		return "Queued";
	case ItemStatus::Processing:
		return "Processing";
	case ItemStatus::Sorted:
		return "Sorted";
	case ItemStatus::Saved:
		return "Saved";
	default:
		return "InvalidStatus";
	}
}

std::string toString(bool flag) {
	return flag ? "TRUE" : "FALSE";
}

std::string toString(SortingLine line) {
	switch (line) {
	case SortingLine::Unassigned:
		return "Unassigned";
	case SortingLine::FragileLine:
		return "FragileLine";
	case SortingLine::CautionLine:
		return "CautionLine";
	case SortingLine::SmallLine:
		return "SmallLine";
	case SortingLine::LargeLine:
		return "LargeLine";
	default:
		return "InvalidLine";
	}
}