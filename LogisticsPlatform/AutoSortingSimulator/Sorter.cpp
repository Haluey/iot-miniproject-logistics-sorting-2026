#include "Sorter.h"
#include "Fragile.h"

SortingLine Sorter::sortItem(const std::shared_ptr<Item>& targetItem) {
	// Fragile 객체인지 확인, 맞으면 shared_ptr<Fragile>로 바꿔서 fragileItem에 담는다.
	std::shared_ptr<Fragile> fragileItem = std::dynamic_pointer_cast<Fragile>(targetItem);
	
	if (fragileItem) {
		return SortingLine::FragileLine;
	}
	else if (targetItem->getIsFragile()) {
		return SortingLine::CautionLine;
	}
	else if (targetItem->getWeight() < 5) {
		return SortingLine::SmallLine;
	}
	else {
		return SortingLine::LargeLine;
	}
}