#include "Sorter.h"
#include "Fragile.h"

SortingLine Sorter::sortItem(std::shared_ptr<Item> targetItem) {

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