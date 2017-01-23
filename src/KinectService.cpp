#include  <unistd.h>
#include <iostream>
#include "KinectService.hpp"

#include <zmq.hpp>

namespace pykinecting{

    KinectService::KinectService(const std::string socket)
      : m_socket(socket),
      m_ctx(0),
      m_skt(0)
      {
        std::cout << "INFO:: KinectService constructor" << std::endl;

        m_ctx = new zmq::context_t(1); // means single threaded
        m_skt = new zmq::socket_t(*m_ctx, ZMQ_PUB); // means a publisher
        uint32_t hwm = 1;
        m_skt->setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
        std::string endpoint("tcp://" + m_socket);
        m_skt->bind(endpoint.c_str());
        sleep(1);
      }

    void KinectService::play(const std::string filename) {
    }

    void KinectService::play_frames(const std::string filename, const int first_frame, const int last_frame) {
    }

    void KinectService::record(const std::string output_file, /*const std::string socket, */const int num_cameras,
        const float duration, const bool rgb_is_compressed/* = false*/) {
    }

    void KinectService::play_record_in_sync(const std::string filename, const int first_frame, const int last_frame,
                const std::string output_file, const int num_cameras) {
    }

    void KinectService::pause() {
    }

    bool KinectService::is_paused() const {
        return m_paused;
    }

    bool KinectService::set_paused(bool val) {
        m_paused = val;
    }

    std::string KinectService::get_socket() const {
        return m_socket;
    }

    std::string KinectService::set_socket(const std::string socket) {
        m_socket = socket;
    }
}
