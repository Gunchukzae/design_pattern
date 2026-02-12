#pragma once
#include <iostream>
#include <mutex>
#include <string>

class CafeManager
{
public:
	static CafeManager& getInstance();

	void processOrder(std::string menu);

	CafeManager(const CafeManager&) = delete;
	CafeManager& operator=(const CafeManager&) = delete;

private:
	CafeManager();
	~CafeManager();

	int orderCount;
	std::mutex mtx;
};

