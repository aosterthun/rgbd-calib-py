/*
 * This inclusion should be put at the beginning.  It will include <Python.h>.
 */

// #include <RemoteRecorder.hpp>

#include <KinectService.hpp>
#include <boost/python.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>


/*
 * This is a macro Boost.Python provides to signify a Python extension module.
 */
BOOST_PYTHON_MODULE(pykinecting) {
    // An established convention for using boost.python.
    using namespace boost::python;
    // using namespace pyrgbdcalib;
    using namespace pykinecting;

    // expose the class RemoteRecorder
    // class_<RemoteRecorder>("RemoteRecorder",
    //     init<std::string const &, std::string const &>())
    //     .def("record", &RemoteRecorder::record)
    //     .def("stop", &RemoteRecorder::stop)
    //     .def("is_paused", &RemoteRecorder::is_paused)
    //     .add_property("filename", &RemoteRecorder::get_filename, &RemoteRecorder::set_filename)
    // ;

    class_<KinectService>("KinectService",
        init<const std::string>())
        .def("play", &KinectService::play)
        .def("play_frames", &KinectService::play_frames)
        .def("record", &KinectService::record)
        .def("play_record_in_sync", &KinectService::play_record_in_sync)
        .def("pause", &KinectService::pause)
        .add_property("socket", &KinectService::get_socket, &KinectService::set_socket)
        .add_property("paused", &KinectService::is_paused, &KinectService::set_paused);
}


