#include <pybind11/pybind11.h>
#include <node.h>

namespace py = pybind11;

template<typename float_type>
std::shared_ptr<Node<float_type>> temp();
