#include "GenericMessage.hpp"

GenericMessage::GenericMessage(){}
GenericMessage::~GenericMessage(){}

void GenericMessage::set_type(ZMQMessageType _type){
	this->type = _type;
}

void GenericMessage::set_payload_size(unsigned _size_payload_byte){
	this->size_payload_byte = _size_payload_byte;
}

unsigned GenericMessage::get_message_size(){
	return sizeof(int) + sizeof(unsigned) + this->size_payload_byte;
}

void GenericMessage::set_payload(std::shared_ptr<AbstractCommand> _cmd){
	std::shared_ptr<PlayCommand> _exe(std::dynamic_pointer_cast<PlayCommand>(_cmd));

	std::stringstream _exe_stream;

    boost::archive::text_oarchive _exe_archive{_exe_stream};
    _exe_archive << *_exe;
	this->payload = _exe_stream.str();
	std::cout << this->payload << std::endl;
}

zmq::message_t GenericMessage::build_zmq_message(){\
	this->set_type(ZMQMessageType::PLAY);

	this->set_payload_size(this->payload.size() + 1);

	zmq::message_t _exe_msg{this->get_message_size()};

	memcpy(((unsigned char*) _exe_msg.data()), (const unsigned char*) &this->type, sizeof(int));
	memcpy(((unsigned char*) _exe_msg.data() + sizeof(int)), (const unsigned char*) &this->size_payload_byte, sizeof(unsigned));
	memcpy(((unsigned char*) _exe_msg.data() + sizeof(int) + sizeof(unsigned)), (const unsigned char*) this->payload.c_str(), this->size_payload_byte);

	return _exe_msg;
}