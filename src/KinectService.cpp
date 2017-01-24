#include <unistd.h>
#include <iostream>
#include "KinectService.hpp"

namespace pykinecting{

	KinectService::KinectService(const std::string socket)
		: ks_socket(socket),
		ks_pub_ctx(0),
		ks_pub_skt(0),
		ks_sub_ctx(0),
		ks_sub_skt(0)
      {
		  std::cout << "INFO:: KinectService constructor" << std::endl;
		  ks_pub_ctx = new zmq::context_t(1); // means single threaded
		  ks_pub_skt = new zmq::socket_t(*ks_pub_ctx, ZMQ_PUB); // means a publisher
		  ks_sub_ctx = new zmq::context_t(1); // means single threaded
		  ks_sub_skt = new zmq::socket_t(*ks_pub_ctx, ZMQ_SUB); // means a sublisher
		  uint32_t hwm = 1;
		  ks_pub_skt->setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
		  ks_sub_skt->setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
		  std::string endpoint("tcp://" + ks_socket);
		  ks_pub_skt->bind(endpoint.c_str());
		  ks_sub_skt->connect(endpoint.c_str());
		  sleep(1);
      }

    void KinectService::play(std::string& user_id, std::string& filename) {
		std::string message_id = std::to_string(ks_message_count);
		ks_pub_skt->send(pykinecting::play(Message_Type::PLAY, message_id, filename, user_id));
		zmq::message_t response(10);
		ks_sub_skt->recv(&response);
		pykinecting::resolveResponse(Message_Type::RESPONSE, &response);
    }
}