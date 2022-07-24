#pragma once
#include <string>
class DiaryLog {
public:
	DiaryLog();
private:
	std::string id;
	std::string date;
	std::string content;
};