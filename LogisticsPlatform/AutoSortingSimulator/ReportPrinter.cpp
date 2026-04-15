#include "ReportPrinter.h"
#include "ItemUtils.h"
#include <iomanip>

// 통계 출력 함수
void ReportPrinter::printLineStatistics(const std::vector<LineStatistic>& stats) {
	std::cout << "===== Line Statistics =====" << std::endl;

	if (stats.empty()) {
		std::cout << "[QUERY] No results found." << std::endl;
		return;
	}

	for (const LineStatistic& stat : stats) {
		std::cout << stat.lineName << " : " << stat.itemCount << std::endl;
	}

	std::cout << std::endl;
}

void ReportPrinter::printTypeStatistics(const std::vector<TypeStatistic>& stats) {
	std::cout << "===== Type Statistics =====" << std::endl;

	if (stats.empty()) {
		std::cout << "[QUERY] No results found." << std::endl;
		return;
	}

	for (const TypeStatistic& stat : stats) {
		std::cout << stat.typeName << " : " << stat.itemCount << std::endl;
	}

	std::cout << std::endl;
}

void ReportPrinter::printWeightStatistics(const std::vector<WeightStatistic>& stats) {
	std::cout << "===== Weight Statistics =====" << std::endl;

	if (stats.empty()) {
		std::cout << "[QUERY] No results found." << std::endl;
		return;
	}

	for (const WeightStatistic& stat : stats) {
		std::cout << stat.lineName << " : "
			<< std::fixed << std::setprecision(2) // 소수점 2자리로 고정
			<< stat.averageWeight << " kg" << std::endl;
	}

	std::cout << std::endl;
}

// 목록 출력 함수
void ReportPrinter::printItemsByLine(const std::vector<ItemRecord>& items, const std::string& lineName) {
	std::cout << "===== Items in " << lineName << " =====" << std::endl;

	if (items.empty()) {
		std::cout << "[QUERY] No results found." << std::endl;
		return;
	}

	for (const ItemRecord& record : items) {
		std::cout << "Type: " << record.typeName
			<< ", Weight: "
			<< std::fixed << std::setprecision(2)
			<< record.weight << " kg"
			<< ", Fragile: " << toString(record.fragileFlag)
			<< ", Status: " << record.statusName
			<< ", Line: " << record.lineName
			<< ", Saved At: " << record.savedAt << std::endl;
	}

	std::cout << std::endl;
}

void ReportPrinter::printTopNHeaviestItems(const std::vector<ItemRecord>& items, int limit) {
	std::cout << "===== Top " << limit << " Heaviest Items =====" << std::endl;

	if (items.empty()) {
		std::cout << "[QUERY] No results found." << std::endl;
		return;
	}

	for (const ItemRecord& record : items) {
		std::cout << "Type: " << record.typeName
			<< ", Weight: "
			<< std::fixed << std::setprecision(2)
			<< record.weight << " kg"
			<< ", Line: " << record.lineName
			<< ", Saved At: " << record.savedAt << std::endl;
	}

	std::cout << std::endl;
}

void ReportPrinter::printRecentItems(const std::vector<ItemRecord>& items, int limit) {
	std::cout << "===== Recent " << limit << " Items =====" << std::endl;

	if (items.empty()) {
		std::cout << "[QUERY] No results found." << std::endl;
		return;
	}

	for (const ItemRecord& record : items) {
		std::cout << "Type: " << record.typeName
			<< ", Weight: "
			<< std::fixed << std::setprecision(2)
			<< record.weight << " kg"
			<< ", Status: " << record.statusName
			<< ", Line: " << record.lineName
			<< ", Saved At: " << record.savedAt << std::endl;
	}

	std::cout << std::endl;
}