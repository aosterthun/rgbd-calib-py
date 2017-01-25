#ifndef kinect_service_hpp
#define kinect_service_hpp

#include <string>
#include <zmq_messages.cpp>

namespace zmq{
	class context_t;
	class socket_t;
}

namespace pykinecting{

	class KinectService
	{
	public:
		KinectService(const std::string socket);

		void play(std::string user_id, std::string filename);
		void play_frames(std::string user_id, std::string filename, std::string first, std::string last, bool loop);
		void record(std::string user_id, std::string filepath, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed);
		void record_play(std::string user_id, std::string filepath_src, std::string startframe, std::string endframe, std::string filepath_dest, std::string num_cameras);
	private:
		int ks_message_count;
		std::string ks_socket;
		zmq::context_t* ks_pub_ctx;
		zmq::socket_t* ks_pub_skt;
		zmq::context_t* ks_sub_ctx;
		zmq::socket_t* ks_sub_skt;
		//bool ks_is_playing;
		//bool ks_is_recording;
	};
}
#endif
