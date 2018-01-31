/*
 * This inclusion should be put at the beginning.  It will include <Python.h>.
 */

#include <RemoteRecorder.hpp>

#include <KinectDaemon.hpp>
#include <AbstractCommand.hpp>
#include <PlayCommand.hpp>
#include <RecordCommand.hpp>

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

    // expose the class RemoteRecorder
    class_<HelloWorld>("HelloWorld",
        init<>());

    class_<AbstractCommand, boost::noncopyable>("AbstractCommand",
        no_init)
    	.def("get_type", pure_virtual(&AbstractCommand::get_type))
    	.def("execute", pure_virtual(&AbstractCommand::execute));

    class_<PlayCommand, bases<AbstractCommand>>("PlayCommand",
        init<>())
      .def("stop", &PlayCommand::stop);

    class_<RecordCommand, bases<AbstractCommand>>("RecordCommand",
        init<>())
      .def("stop", &RecordCommand::stop)
      .def("filename", static_cast<std::string (RecordCommand::*)() const>(&RecordCommand::filename))
      .def("filename", static_cast<void (RecordCommand::*)(std::string const&)>(&RecordCommand::filename))
      .def("server_address", static_cast<std::string (RecordCommand::*)() const>(&RecordCommand::server_address))
      .def("server_address", static_cast<void (RecordCommand::*)(std::string const&)>(&RecordCommand::server_address));

    class_<KinectDaemon>("KinectDaemon",
        init<std::string const&, std::string const&>())
      .def("play", static_cast<std::shared_ptr<PlayCommand> (KinectDaemon::*)(std::string const&)>(&KinectDaemon::play))
      .def("play", static_cast<std::shared_ptr<PlayCommand> (KinectDaemon::*)(std::string const&,std::string const&)>(&KinectDaemon::play))
      .def("record", static_cast<std::shared_ptr<RecordCommand> (KinectDaemon::*)()>(&KinectDaemon::record))
      .def("record", static_cast<std::shared_ptr<RecordCommand> (KinectDaemon::*)(std::string const&, std::string const&, unsigned)>(&KinectDaemon::record));
}
