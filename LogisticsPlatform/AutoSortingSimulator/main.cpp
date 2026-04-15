// 스마트 물류 자동 분류 시뮬레이터

#include "LogisticsService.h"
#include "DatabaseManager.h"
#include "ReportPrinter.h"

int main(void) {
	//ItemFactory itemFactory;
	//ConveyorSystem conveyorSystem;
	//Sorter sorter;
	DatabaseManager databaseManager;
	ReportPrinter printer;

	if (!databaseManager.connect()) return 1;

	LogisticsService logisticsService(databaseManager);
	logisticsService.runAutoMode(3);

	std::cout << "===== Statistics =====" << std::endl;
	printer.printLineStatistics(databaseManager.getLineStatistics());
	printer.printTypeStatistics(databaseManager.getTypeStatistics());
	printer.printWeightStatistics(databaseManager.getWeightStatistics());

	std::cout << "===== Query Results =====" << std::endl;
	printer.printItemsByLine(databaseManager.getItemsByLine("FragileLine"), "FragileLine");
	printer.printTopNHeaviestItems(databaseManager.getTopNHeaviestItems(3), 3);
	printer.printRecentItems(databaseManager.getRecentItems(5), 5);

	databaseManager.disconnect();
	
	return 0;
}