#ifndef RemoteRecorder_hpp
#define RemoteRecorder_hpp

#include <string>

namespace zmq{
	class context_t;
	class socket_t;
}

namespace pyrgbdcalib{

	class RemoteRecorder{

	public:

		RemoteRecorder(const std::string& socket, const std::string& filename);
		~RemoteRecorder();

		std::string get_filename() const;

		void set_filename(std::string const & in_filename);

		bool play(std::string const& stream_path);

		bool record(const unsigned num_seconds);

		bool stop();

		bool is_paused();

	private:

		std::string m_socket;
		std::string m_filename;
		zmq::context_t* m_ctx;
		zmq::socket_t*  m_skt;
		void re_init();

	};
}

#endif
