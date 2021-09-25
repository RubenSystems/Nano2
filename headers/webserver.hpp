#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector> 

#include "baseview.hpp"

#define PORT 8080


typedef std::function< BaseView * (std::vector<std::string>)> Callback;

class Webserver {

	

	public:
		void start();

		void route(const std::pair<std::vector<std::string>, Callback> & callback);

	private: 

		

		std::string msgGen(const std::string & message);

		std::vector<std::string> split(const std::string & text, const char & breaker);

		std::pair<int, std::vector<std::string>> getPath(const std::string & text);

		std::vector<std::pair<std::vector<std::string>, Callback>> handlers;

		
};


void Webserver::route(const std::pair<std::vector<std::string>, Callback> & callback) {
	this->handlers.push_back(callback);
}

void Webserver::start () {

	int server_fd, new_socket; long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int opt = 1;
	
	// Only this line has been changed. Everything is same.
	
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("In socket");
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	} else if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	


	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
		perror("In bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 10) < 0){
		perror("In listen");
		exit(EXIT_FAILURE);
	}

	while (true) {

		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
			perror("In accept");
			exit(EXIT_FAILURE);
		}

		
		char buffer[30000] = {0};
		valread = read( new_socket , buffer, 30000 );

		std::cout << buffer << "--\n\n";

		auto path = this->getPath(std::string(buffer));

		std::string result;
		if (path.first == -1) {
			result = msgGen("404 error");
		} else {
			result = this->msgGen(((this->handlers[path.first].second)(path.second))->generate()["app"]);
		}

		write(new_socket , result.c_str() , result.size());
		close(new_socket);
	}
}

std::string Webserver::msgGen(const std::string & message) {
	return "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + std::to_string(message.size()) + "\n\n" + message;
}



std::vector<std::string> Webserver::split(const std::string & text, const char & breaker) {
	std::string tmp;
	std::vector<std::string> stk;
	std::stringstream ss(text);
	while(getline(ss, tmp, breaker)) {
		stk.push_back(tmp);
	}
	return stk;
}

std::pair<int, std::vector<std::string>> Webserver::getPath(const std::string & text){
	auto textSplit = this->split(text, '\n');
	auto spaceSplit = this->split(textSplit[0], ' ');
	auto path = this->split(spaceSplit[1], '/');
	path.erase(path.begin());
	// path.erase(path.end());
	for(auto & i : path) {std::cout << i << "/";}
	for (int i = 0; i < this->handlers.size(); i++) {
		auto item = this->handlers[i].first;
		if (path.size() == item.size()) {
			bool fits = true;
			std::vector<std::string> vars;
			for (int c = 0; c < path.size(); c++) {
				if (path[c] == item[c]) {
					continue;
				} else if (item[c] == "$") {
					vars.push_back(path[c]);
				}else {
					fits = false;
					break;
				}
			}
			if (fits) {
				return {i, vars }; 
			}
		} 
	}

	return {-1, {}};
}
