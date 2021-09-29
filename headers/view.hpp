#pragma once
#include "baseview.hpp"

#include <vector>
#include <unordered_map>
#include <iostream>

#include "uuid.hpp"

class View: public BaseView {
 
	public: 

		View (const std::string & tag, const std::vector< BaseView * > & children, bool close);	

		~View() ;

		std::unordered_map<std::string, std::string> generate() override {

			std::string cssGen = "";
			//HTML Generateion
			std::string tagGen = "<" + this->tag + " ";


			for (auto & i : this->attributes) {
				tagGen += i.first + "='";
				for (int c = 0; c < i.second.size(); c++) {
					auto item = i.second[c];
					tagGen += item;
					if (c + 1 > item.size()){
						tagGen += " ";
					}
				}
				tagGen += "' ";
			}

			if (!this->close) {tagGen += "/";}
			tagGen += ">";

			for(auto & i : this->children) {
				auto generated = i->generate();
				if (generated.find("css") != generated.end()){
					cssGen += i->generate()["css"];
				}
				tagGen += i->generate()["html"];
			}

			if (this->close) {tagGen += "</" + this->tag + ">";}

			//CSS Generateion
			if (this->styles.size() > 0 ) {
				cssGen += "#" + this->id + "{";
				for (auto & i : this->styles){
					cssGen += i.first + ": " + i.second + ";";
				}
				cssGen += "} ";
			}

			return {{"html", tagGen}, {"css", cssGen}};
		};

		View * attr(const std::string & key, const std::string & value) {
			if (this->attributes.find(key) != this->attributes.end()) {
				this->attributes[key].push_back(value);
			} else {
				this->attributes[key] = {value};
			}
			return this;
		}

		View * style(const std::string & key, const std::string & value) {
			this->styles[key] = value;
			return this;
		}

		void addChild(BaseView * child) {
			this->children.push_back(child);
		}




	private:
		std::string id;
		std::string tag;
		std::vector<BaseView *> children;
		bool close;
		
		std::unordered_map<std::string, std::vector<std::string>> attributes;
		std::unordered_map<std::string, std::string> styles;


};


View::View (const std::string & tag, const std::vector<BaseView *> & children, bool close): tag(tag), children(children), close(close) {
	auto viewID = UUID::uuid();
	this->id = viewID;
	this->attr("id", viewID);
}


View::~View(){
	for (int i = 0; i < this->children.size(); i ++){
		if (children[i] != nullptr ){
			delete children[i];
		}
	} 
}


BaseView * view(const std::string & tag, const std::vector<BaseView *> & children, bool close) {
	return new View(tag, children, close);
}