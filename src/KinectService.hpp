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

        void play(std::string& user_id, std::string& filename);

    private:
        int ks_message_count;
        std::string ks_socket;
        zmq::context_t* ks_pub_ctx;
        zmq::socket_t* ks_pub_skt;
        zmq::context_t* ks_sub_ctx;
        zmq::socket_t* ks_sub_skt;
    };
}
#endif
