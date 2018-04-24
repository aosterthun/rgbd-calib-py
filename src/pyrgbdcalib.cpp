/*
 * This inclusion should be put at the beginning.  It will include <Python.h>.
 */

#include <RGBDRIClient.hpp>
#include <play.hpp>
#include <record.hpp>

#include <boost/python.hpp>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

/*
 * This is a macro Boost.Python provides to signify a Python extension module.
 */
BOOST_PYTHON_MODULE(pyrgbdcalib) {
    // An established convention for using boost.python.
    using namespace boost::python;

    class_<RGBDRIClient>("RGBDRIClient",
       init<std::string const&, std::string const&>());

    class_<Record>("Record",
        init<RGBDRIClient&, std::string const&, std::string const&>())
      .def("start", &Record::start)
      .def("stop", &Record::stop)
      .def_readwrite("filename", &Record::filename)
      .def_readwrite("stream_endpoint", &Record::stream_endpoint)
      .def_readwrite("backchannel_endpoint", &Record::backchannel_endpoint);

    class_<Play>("Play",init<RGBDRIClient&, std::string const&, std::string const&>())
      .def(init<RGBDRIClient&, std::string const&, std::string const&, std::string const&>())
      .def("start", &Play::start)
      .def("loop", &Play::play_as_loop)
      .def("pause", &Play::pause)
      .def("resume", &Play::resume)
      .def("stop", &Play::stop)
      .def("is_playing", &Play::is_playing)
      .def_readwrite("filename", &Play::filename)
      .def_readwrite("stream_endpoint", &Play::stream_endpoint)
      .def_readwrite("backchannel_endpoint", &Play::backchannel_endpoint);


}
