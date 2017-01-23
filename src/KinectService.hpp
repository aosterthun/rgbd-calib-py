#include <string>

namespace zmq{
    class context_t;
    class socket_t;
}

namespace pykinecting{

    class KinectService
    {
    public:
        KinectService(const std::string socket);

        void play(const std::string filename);

        void play_frames(const std::string filename, const int first_frame, const int last_frame);

        void record(const std::string output_file, /*const std::string socket, */const int num_cameras,
            const float duration, const bool rgb_is_compressed = false);

        void play_record_in_sync(const std::string filename, const int first_frame, const int last_frame,
            const std::string output_file, const int num_cameras);

        void pause();

        bool is_paused() const;
        bool set_paused(bool val); //THIS IS ONLY FOR EXPOSING TO PYTHON (WHICH DOES NOT HAVE CONSTANTS)

        std::string get_socket() const;
        std::string set_socket(const std::string socket);

    private:
        bool m_paused;
        std::string m_socket;
        zmq::context_t* m_ctx;
        zmq::socket_t* m_skt;
    };
}
