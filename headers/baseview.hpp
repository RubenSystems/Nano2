#pragma once

#include <string>
#include <unordered_map>

class BaseView {
public:
	virtual std::unordered_map<std::string, std::string> generate() = 0;
};