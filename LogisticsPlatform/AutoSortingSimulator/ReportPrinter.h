#ifndef REPORTPRINTER_H
#define REPORTPRINTER_H

#include "QueryResultTypes.h"
#include <iostream>
#include <vector>

class ReportPrinter {
private:


public:
	// 통계 출력 함수
	void printLineStatistics(const std::vector<LineStatistic>& stats);

	void printTypeStatistics(const std::vector<TypeStatistic>& stats);

	void printWeightStatistics(const std::vector<WeightStatistic>& stats);

	// 상세 조회 결과 출력 함수
	void printItemsByLine(const std::vector<ItemRecord>& items, const std::string& lineName);

	void printTopNHeaviestItems(const std::vector<ItemRecord>& items, int limit);

	void printRecentItems(const std::vector<ItemRecord>& items, int limit);
};

#endif