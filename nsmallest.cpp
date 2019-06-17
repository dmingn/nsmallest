#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <queue>

namespace py = pybind11;

template <typename T>
py::array_t<T> nsmallest(const py::array_t<T> a, int k) {
    const auto data = a.data();
    const auto n = a.size();

    if (n < k) {
        k = n;
    }

    std::priority_queue<T> pq;

    // k log(k)
    for (int i = 0; i < k; i++) {
        pq.push(data[i]);
    }

    // (n - k) log(k) in worst case
    for (int i = k; i < n; i++) {
        if (data[i] < pq.top()) {
            pq.pop();
            pq.push(data[i]);
        }
    }

    py::array_t<T> ret(k);

    // k log(k)
    for (int i = k - 1; i >= 0; i--) {
        ret.mutable_data()[i] = pq.top();
        pq.pop();
    }

    return ret;
}

template <typename T>
py::array_t<int> argnsmallest(const py::array_t<T> a, int k) {
    const auto data = a.data();
    const auto n = a.size();

    if (n < k) {
        k = n;
    }

    std::priority_queue<std::pair<T, int>> pq;

    // k log(k)
    for (int i = 0; i < k; i++) {
        pq.push(std::make_pair(data[i], i));
    }

    // // (n - k) log(k) in worst case
    for (int i = k; i < n; i++) {
        if (data[i] < std::get<0>(pq.top())) {
            pq.pop();
            pq.push(std::make_pair(data[i], i));
        }
    }

    py::array_t<int> ret(k);

    // k log(k)
    for (int i = k - 1; i >= 0; i--) {
        ret.mutable_data()[i] = std::get<1>(pq.top());
        pq.pop();
    }

    return ret;
}

PYBIND11_MODULE(nsmallest, m) {
    m.def("nsmallest", &nsmallest<int8_t>);
    m.def("nsmallest", &nsmallest<int16_t>);
    m.def("nsmallest", &nsmallest<int32_t>);
    m.def("nsmallest", &nsmallest<int64_t>);
    m.def("nsmallest", &nsmallest<uint8_t>);
    m.def("nsmallest", &nsmallest<uint16_t>);
    m.def("nsmallest", &nsmallest<uint32_t>);
    m.def("nsmallest", &nsmallest<uint64_t>);
    m.def("nsmallest", &nsmallest<float>);
    m.def("nsmallest", &nsmallest<double>);
    m.def("argnsmallest", &argnsmallest<int8_t>);
    m.def("argnsmallest", &argnsmallest<int16_t>);
    m.def("argnsmallest", &argnsmallest<int32_t>);
    m.def("argnsmallest", &argnsmallest<int64_t>);
    m.def("argnsmallest", &argnsmallest<uint8_t>);
    m.def("argnsmallest", &argnsmallest<uint16_t>);
    m.def("argnsmallest", &argnsmallest<uint32_t>);
    m.def("argnsmallest", &argnsmallest<uint64_t>);
    m.def("argnsmallest", &argnsmallest<float>);
    m.def("argnsmallest", &argnsmallest<double>);
}
