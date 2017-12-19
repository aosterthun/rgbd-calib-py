#ifndef GenericMessage_hpp
#define GenericMessage_hpp

#include <PlayCommand.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <zmq.hpp>
#include <Threadable.hpp>
#include <ZMQMessageType.hpp>
#include <KinectDaemonHandshake.hpp>

class GenericMessage
{
public:
	GenericMessage();
	void set_type(ZMQMessageType _type);
	void set_payload_size(unsigned _size_payload_byte);
	void set_payload(std::shared_ptr<AbstractCommand> _cmd);
	unsigned get_message_size();
	zmq::message_t build_zmq_message();
	~GenericMessage();
	
private:
	int type;
	unsigned size_payload_byte;
	std::string payload;
};

#endif