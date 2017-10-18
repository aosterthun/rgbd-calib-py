#include <KinectDaemon.hpp>


int main(int argc, char** argv){
	zmq::context_t _ctx(1);
	zmq::socket_t _pub_skt(_ctx, ZMQ_PUB);
	_pub_skt.connect("tcp://141.54.147.27:8001");	
	
	int _j = 0;

	
	while(true){
		zmq::message_t _msg(sizeof(int));
		memcpy((char*) _msg.data(), (const char*)&_j, sizeof(int));
		std::cout << "Sending: " << _j << std::endl;
		_pub_skt.send(_msg);
		++_j;
		
	}
	return 0;
}
