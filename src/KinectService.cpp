#include <unistd.h>
#include <iostream>
#include "KinectService.hpp"

namespace pykinecting{

	KinectService::KinectService(const std::string socket)
		: ks_socket(socket),
		ks_pub_ctx(0),
		ks_pub_skt(0),
		ks_sub_ctx(0),
		ks_sub_skt(0),
        ks_message_count(0)
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

	void KinectService::play(std::string user_id, std::string filename) {
		std::string message_id = std::to_string(ks_message_count);
        std::cout << message_id << std::endl;
        std::cout << ks_message_count << std::endl;

		std::vector<zmq::message_t> i = pykinecting::play(Message_Type::PLAY, message_id, filename, user_id);
		ks_pub_skt->send(i[0], ZMQ_SNDMORE);
		ks_pub_skt->send(i[1], 0);

        // zmq::message_t response(10);
		// ks_sub_skt->recv(&response);
		// std::vector<std::string> responseResolved = pykinecting::resolveResponse(Message_Type::RESPONSE, &response);

		// for (auto i : responseResolved) {
		// 	std::cout << i << std::endl;
		// }
		++ks_message_count;
	}

	void KinectService::play_frames(std::string& user_id, std::string& filename, std::string& first, std::string& last, bool loop){
		std::string message_id = std::to_string(ks_message_count);
		ks_pub_skt->send(pykinecting::play_frames(Message_Type::PLAY_FRAMES, message_id, filename, first, last, loop, user_id));
		++ks_message_count;
	}

    void KinectService::record(std::string& user_id, std::string& filepath, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed){
    	std::string message_id = std::to_string(ks_message_count);
		ks_pub_skt->send(pykinecting::record(Message_Type::RECORD, message_id, filepath, serverport, num_cameras, duration_in_secs, is_compressed, user_id));    	
		++ks_message_count;    
    }
	void KinectService::record_play(std::string& user_id, std::string& filepath_src, std::string& startframe, std::string& endframe, std::string& filepath_dest, std::string& num_cameras){
		std::string message_id = std::to_string(ks_message_count);
		ks_pub_skt->send(pykinecting::record_play(Message_Type::RECORD_PLAY, message_id, filepath_src, startframe, endframe, filepath_dest, num_cameras, user_id));
		++ks_message_count;
	}
}