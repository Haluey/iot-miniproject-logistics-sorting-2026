#include "Fragile.h"

Fragile::Fragile(int itemId, enum ItemType type, double weight, bool isFragile) :
	Item(itemId, type, weight, isFragile) {
}

bool Fragile::isValid() {
	//bool fragileValid = false;

	//// 타입별 유효성 검사
	//// Fragile 타입이면 isFragile가 true인지
	//if (isFragile == true) {
	//	fragileValid = true;
	//}

	//// 최종 유효성 확인
	//if (Item::isValid() && fragileValid) {
	//	return true;
	//}
	//else {
	//	return false;
	//}

	return Item::isValid() && isFragile;
}