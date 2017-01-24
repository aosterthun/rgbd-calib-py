#include "RemoteRecorder.hpp"
#include <zmq.hpp>
#include <iostream>
#include <unistd.h>

namespace pyrgbdcalib{


RemoteRecorder::RemoteRecorder(const std::string& socket, const std::string& filename)
: m_socket(socket),
m_filename(filename),
m_ctx(0),
m_skt(0)
{
	re_init();
}

RemoteRecorder::~RemoteRecorder(){
	std::cout << "INFO: begin ~RemoteRecorder()" << std::endl;
	delete m_ctx;
	delete m_skt;
	std::cout << "INFO: end ~RemoteRecorder()" << std::endl;
}

void
RemoteRecorder::re_init(){

	std::string type = "0";
	std::string id = "1B";
	std::string path = "opt/test";
	std::string path_dest = "opt/test/rec";
	std::string startframe = "132";
	std::string endframe = "982";
	std::string num_cameras = "4";
	std::string serverport = "127.0.0.1:7000";
	std::string duration_in_secs = "420";
	std::cout << pykinecting::play(pykinecting::Message_Type::PLAY, id, path) << std::endl;
	std::cout << pykinecting::play(pykinecting::Message_Type::PLAY, id, path,startframe,endframe) << std::endl;
	std::cout << pykinecting::play(pykinecting::Message_Type::PLAY, id, path,startframe,endframe,true) << std::endl;
	std::cout << pykinecting::record(pykinecting::Message_Type::RECORD, id, path_dest, serverport, num_cameras, duration_in_secs,true) << std::endl;
	std::cout << pykinecting::record_play(pykinecting::Message_Type::RECORD_PLAY, id, path,startframe,endframe,path_dest,num_cameras) << std::endl;

	std::cout << "INFO: RemoteRecorder::re_init()" << std::endl;

	m_ctx = new zmq::context_t(1); // means single threaded
	m_skt = new zmq::socket_t(*m_ctx, ZMQ_PUB); // means a publisher
	uint32_t hwm = 1;
	m_skt->setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
	std::string endpoint("tcp://" + m_socket);
	m_skt->bind(endpoint.c_str());
	sleep(1);
}


bool
RemoteRecorder::play(std::string const& stream_path){
	std::cout << "INFO: RemoteRecorder::play(std::string const& stream_path)" << std::endl;
}

std::string
RemoteRecorder::get_filename() const {
return m_filename;
}

void
RemoteRecorder::set_filename(std::string const & in_filename) {
if(is_paused()){
// 1. use zmq socket to tell recorddaemon new filename
m_filename = in_filename;
}
}

bool
RemoteRecorder::record(const unsigned num_seconds){
std::cout << "INFO: RemoteRecorder::record: starting recording for num seconds: " << num_seconds << std::endl;

// 1. use zmq socket to tell recorddaemon to record for num_seconds....
float mat = 5.0f;
zmq::message_t zmqm(sizeof(float));
memcpy( (float* ) zmqm.data(), &mat, sizeof(float));
std::cout << "sending" << std::endl;
m_skt->send(zmqm);


return true;
}


bool
RemoteRecorder::stop(){
// 1. use zmq socket to tell recorddaemon to stop and save....
return true;
}


bool
RemoteRecorder::is_paused(){
// 1. use zmq socket to ask recorddaemon if saving of filename is finished....
return true;
}


}
