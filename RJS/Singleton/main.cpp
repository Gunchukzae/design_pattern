#include "CafeManager.h"

int main()
{
	CafeManager& cafeManager = CafeManager::getInstance();
	cafeManager.processOrder("Americano");
	cafeManager.processOrder("MatchaLatte");
	cafeManager.processOrder("CafeLatte");

	return 0;
}