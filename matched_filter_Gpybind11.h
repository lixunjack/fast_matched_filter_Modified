

// Jack on 9，JUNE, 2024. WARNING: Such script cannot be distributed privately as it is adapted from a open-access github repository
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

void matched_filter(
    float* templates, float* sum_square_templates,
    int* moveouts, float* data, float* weights, size_t step,
    size_t n_samples_template, size_t n_samples_data,
    size_t n_templates, size_t n_stations,
    size_t n_components, size_t n_corr,
    float* cc_out);

namespace py = pybind11;

void wrap_matched_filter(py::module_& m) {
    m.def("matched_filter", [](py::array_t<float> templates,
        py::array_t<float> sum_square_templates,
        py::array_t<int> moveouts,
        py::array_t<float> data,
        py::array_t<float> weights,
        size_t step,
        size_t n_samples_template,
        size_t n_samples_data,
        size_t n_templates,
        size_t n_stations,
        size_t n_components,
        size_t n_corr,
        py::array_t<float> cc_out) {
            // Ensure we pass the mutable data pointers from the numpy arrays
            matched_filter(templates.mutable_data(),
            sum_square_templates.mutable_data(),
            moveouts.mutable_data(),
            data.mutable_data(),
            weights.mutable_data(),
            step,
            n_samples_template,
            n_samples_data,
            n_templates,
            n_stations,
            n_components,
            n_corr,
            cc_out.mutable_data());

        }, py::arg("templates"), py::arg("sum_square_templates"), py::arg("moveouts"),
            py::arg("data"), py::arg("weights"), py::arg("step"), py::arg("n_samples_template"),
            py::arg("n_samples_data"), py::arg("n_templates"), py::arg("n_stations"),
            py::arg("n_components"), py::arg("n_corr"), py::arg("cc_out") );
}

PYBIND11_MODULE(matchedfilterGPU, m) {
    wrap_matched_filter(m);
}

