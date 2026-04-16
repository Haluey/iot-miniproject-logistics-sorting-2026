// 물류 자동 분류 시뮬레이터

#include "LogisticsService.h"

int main(void) {
	//ItemFactory itemFactory;
	//ConveyorSystem conveyorSystem;
	//Sorter sorter;
	DatabaseManager databaseManager;
	//ReportPrinter printer;

	if (!databaseManager.connect()) return 1;

	LogisticsService logisticsService(databaseManager);
	logisticsService.runInteractiveAutoMode(2);

	databaseManager.disconnect();
	
	return 0;
}