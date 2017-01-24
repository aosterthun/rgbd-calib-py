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

	class_<KinectService>("KinectService",
		init<const std::string>())
		.def("play", &KinectService::play)
		.def("play_frames", &KinectService::play_frames)
		.def("record", &KinectService::record)
		.def("record_play", &KinectService::record_play);
}


