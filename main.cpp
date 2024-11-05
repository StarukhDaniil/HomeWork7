#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>
#include <vector>
#include <set>
#include <list>
#pragma warning(disable: 4996)
#include "hw5.h"

template <typename Container>
void Logger::logContainer(const Container& container) const {
	std::fstream logFile("log.txt", std::ios::app);
	if (logFile.is_open()) {
		for (auto item : container) {
			logFile << item << " ";
		}
		logFile << std::endl;
		logFile.close();
	}
	else {
		std::cerr << "Unable to open log file :(" << std::endl;
	}
}

template <typename T>
void Logger::logContainer(const std::initializer_list<T>& ilist) const {
	std::ofstream logFile("log.txt", std::ios::app);
	if (logFile.is_open()) {
		for (T item : ilist) {
			logFile << item << " ";
		}
		logFile << std::endl;
		logFile.close();
	}
	else {
		std::cerr << "Unable to open log file :(" << std::endl;
	}
}

int main() {
	std::vector<int> a = { 10, 20, 30 };
	std::set<int> b = {5, 4, 3, 2, 1};
	std::list<int> c = { 11, 22, 33, 44 };

	Logger::getInstance().logContainer<int>({ 1, 2, 3 });
	Logger::getInstance().logContainer<std::vector<int>>(a);
	Logger::getInstance().logContainer<std::set<int>>(b);
	Logger::getInstance().logContainer<std::list<int>>(c);

	return 0;
}