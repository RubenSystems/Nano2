#include "headers/view.hpp"
#include "headers/text.hpp"
#include "headers/app.hpp"
#include "headers/webserver.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;


PYBIND11_MODULE(nano2, m) {
	//Bindings for view
	py::class_<BaseView>(m, "BaseView");



	py::class_<View, BaseView>(m, "View")
	.def("attr", &View::attr)
	.def("generate", &View::generate)
	.def("style", &View::style);

	m.def("view", &view, py::arg_v("tag", "div", "div"), py::arg_v("children", std::vector<BaseView *>(), "[]"), py::arg_v("close", true, "True"), py::return_value_policy::reference);


	py::class_<Text, BaseView>(m, "Text")
	.def("generate", &Text::generate);
	m.def("text", &text, py::return_value_policy::reference);

	py::class_<App, BaseView>(m, "App")
	.def("generate", &App::generate);
	m.def("app", &app, py::return_value_policy::reference);


	// py::class_<Webserver>(m, "Webserver")
	// .def("start", &Webserver::start)
	// .def("route", &Webserver::route);

	// m.def("webserver", &webserver, py::return_value_policy::reference);
}