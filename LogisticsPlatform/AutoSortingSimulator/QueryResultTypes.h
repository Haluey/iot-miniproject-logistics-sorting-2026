#ifndef QUERYRESULTTYPES_H
#define QUERYRESULTTYPES_H

#include <string>

// 통계 조회
struct LineStatistic {
	std::string lineName;
	int itemCount;
};

struct TypeStatistic {
	std::string typeName;
	int itemCount;
};

struct WeightStatistic {
	std::string lineName;
	double averageWeight;
};

// 조건 조회
struct ItemRecord {
	std::string typeName;
	double weight;
	bool fragileFlag;
	std::string statusName;
	std::string lineName;
	std::string savedAt;
};

#endif