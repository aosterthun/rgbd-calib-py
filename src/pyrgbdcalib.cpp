/*
 * This inclusion should be put at the beginning.  It will include <Python.h>.
 */

#include <RemoteRecorder.hpp>


#include <boost/python.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>


/*
 * This is a macro Boost.Python provides to signify a Python extension module.
 */
BOOST_PYTHON_MODULE(pyrgbdcalib) {
    // An established convention for using boost.python.
    using namespace boost::python;
    using namespace pyrgbdcalib;


    // expose the class RemoteRecorder
    class_<RemoteRecorder>("RemoteRecorder",
        init<std::string const &, std::string const &>())
        .def("record", &RemoteRecorder::record)
        .def("stop", &RemoteRecorder::stop)
        .def("is_paused", &RemoteRecorder::is_paused)
        .def("play", &RemoteRecorder::play)
        .add_property("filename", &RemoteRecorder::get_filename, &RemoteRecorder::set_filename)
    ;
}


