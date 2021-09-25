// #include "headers/webserver.hpp"
#include "headers/view.hpp"
#include "headers/text.hpp"
#include "headers/app.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;


PYBIND11_MODULE(nano2, m) {

	//Bindings for IndexData
	// py::class_<idx::IndexData>(m, "IndexData")
	// .def(py::init<>())
	// .def_readwrite("uid", &idx::IndexData::uid)
	// .def_readwrite("metadata", &idx::IndexData::metadata)
	// .def_readwrite("matrix", &idx::IndexData::matrix);

	// //Bindings for Page
	// py::class_<idx::Page>(m, "Page")
	// .def(py::init<const std::string &, const std::unordered_map<std::string, std::string> &, const RubenSystems::Math::Matrix &>())
	// .def("data", &idx::Page::data);

	// //Bindings for IndexConfig
	// py::class_<idx::IndexConfig>(m, "IndexConfig")
	// .def(py::init<const std::string &, int, const std::vector<std::string> &, const std::tuple<int,int,int> &>());


	//Bindings for view
	py::class_<BaseView>(m, "BaseView");



	py::class_<View, BaseView>(m, "View")
	.def("attr", &View::attr)
	.def("generate", &View::generate)
	.def("style", &View::style);

	m.def("view", &view, py::return_value_policy::reference);


	py::class_<Text, BaseView>(m, "Text")
	.def("generate", &Text::generate);
	m.def("text", &text, py::return_value_policy::reference);

	py::class_<App, BaseView>(m, "App")
	.def("generate", &App::generate);
	m.def("app", &app, py::return_value_policy::reference);
}


// #include <iostream>
/*
int main() {
	Webserver srv;


	
	srv.route({{"$"}, [](std::vector<std::string> a) -> BaseView * {
		auto x = view("body", true, {
			view("h2", true, {
				text("you took me to: "),
				text(a[0])
			})
			->attr("class", "hi-there")
			->attr("class", "hows-itgoing")
			->attr("data", "someing")
			->style("background", "green")
		});

		auto y = view("head", true, {

		});

		auto application = app(y, x);
		return application;
	}});

	srv.start();


	return 0;
}
*/