#pragma once

#include "baseview.hpp"
#include "text.hpp"
#include "view.hpp"


class App: public BaseView{
	public:
		App(View * head,  BaseView * body);	

		std::unordered_map<std::string, std::string> generate() override{
			
			auto bodyGenerate = this->body->generate();
			std::string htmlGen = "";

			this->head->addChild( view("style", true, {text(bodyGenerate["css"])}) );
			htmlGen += this->head->generate()["html"];
			htmlGen += bodyGenerate["html"];

			return {{"app", htmlGen}};

		}


	private:
		View * head;
		BaseView * body;

};

App::App(View * head,  BaseView * body): head(head), body(body) {}

BaseView * app(View * head,  BaseView * body) {
	return new App(head, body);
}