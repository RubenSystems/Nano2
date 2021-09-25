#pragma once

#include "baseview.hpp"

class Text : public BaseView{
	public:
		Text(const std::string & text);
		

		std::unordered_map<std::string, std::string> generate() override {
			return {{"html", this->text}};
		}
	
	private:
		std::string text;
};

Text::Text(const std::string & text) : text(text){}

BaseView * text(const std::string & text) {
	return new Text(text);
}