//
//  KinectDaemon.cpp
//  kinectdaemon
//
//  Created by Arne Osterthun on 18.09.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

//  CommandStatus _cmd_status = CommandStatus::PAUSE;
//	std::stringstream _cmd_status_stream;
//	boost::archive::text_oarchive _cmd_status_archive(_cmd_status_stream);
//	_cmd_status_archive << _cmd_status;
//	std::string _cmd_status_msg_str = _cmd_status_stream.str();
//	zmq::message_t _cmd_status_msg(_cmd_status_msg_str.length());
//	memcpy(_cmd_status_msg.data(), _cmd_status_msg_str.data(), _cmd_status_msg_str.length());
//	_skt1.send(_cmd_status_msg);
#include "KinectDaemon.hpp"

KinectDaemon::KinectDaemon(const std::string &_serverport)
{
	this->recv_timeo = 2000;
	zmq::context_t _ctx(1);
	zmq::socket_t _pub_skt(_ctx, ZMQ_PUB);
	_pub_skt.bind("tcp://127.0.0.1:8001");
	//this->ctx = std::make_shared<zmq::context_t>(1);
	//this->pub_skt = std::make_shared<zmq::socket_t>(*this->ctx.get(), ZMQ_PUB);
	//this->sub_skt = std::make_shared<zmq::socket_t>(*this->ctx.get(), ZMQ_SUB);
	
	//this->pub_skt->connect("tcp://127.0.0.1:8001");
	//this->sub_skt->bind("tcp://127.0.0.1:8002");
	//this->sub_skt->setsockopt(ZMQ_RCVTIMEO, &this->recv_timeo, sizeof(this->recv_timeo));
	
	
	/*
	 Send handshake:
		- Client IP
	 */
//	std::shared_ptr<KinectDaemonHandshake> _handshake = std::make_shared<KinectDaemonHandshake>();
//	_handshake->client_ip("127.0.0.1");
//	
//	std::stringstream _handshake_stream;
//	boost::archive::text_oarchive _handshake_archive(_handshake_stream);
//	_handshake_archive << _handshake.get();
//	std::string _handshake_msg_str = _handshake_stream.str();
//	
//	std::shared_ptr<zmq::message_t> _send_handshake = std::make_shared<zmq::message_t>(_handshake_msg_str.length());
//	memcpy(_send_handshake->data(), _handshake_msg_str.data(), _handshake_msg_str.length());
	
	
	int _j = 0;

	
	while(true){
		zmq::message_t _msg(sizeof(int));
		memcpy((char*) _msg.data(), (const char*)&_j, sizeof(int));
		std::cout << "Sending: " << _j << std::endl;
		_pub_skt.send(_msg);
		++_j;
		
	}
	/*
	 Receive handshake OK
	 Timeout: 2s (this->recv_timeo)
	 */
//	std::shared_ptr<zmq::message_t> _recv_handshake = std::make_shared<zmq::message_t>();
//	if(this->sub_skt->recv(_recv_handshake.get()))
//	{
//		std::cout << "Received handshake answer" << std::endl;
//	}
//	else
//	{
//		//throw some error
//	}
}
//
//std::shared_ptr<PlayCommand> KinectDaemon::play(const std::string &_filename)
//{
//	std::shared_ptr<PlayCommand> _play = std::make_shared<PlayCommand>(_filename);
//	this->execute(ZMQMessageType::PLAY, _play);
//	return _play;
//}
//
////void KinectDaemon::open_cmd_backchannel(std::shared_ptr<Event> _event, unsigned _unique_thread_id)
////{
////	
////}
//
//void KinectDaemon::execute(ZMQMessageType _type, std::shared_ptr<AbstractCommand> _cmd)
//{
////	std::shared_ptr<AbstractCommand> _exe;
////	switch (_type) {
////		case PLAY: {
//			std::shared_ptr<PlayCommand> _exe(dynamic_cast<PlayCommand*>(_cmd.get()));
////			break;
////		}
////		case PLAY_RECORD_IN_SYNC:{
////			//std::shared_ptr<PlayCommand> _exe(dynamic_cast<PlayCommand*>(_cmd.get()));
////			break;
////		}
////		case RECORD:{
////			//std::shared_ptr<RecordCommand> _exe(dynamic_cast<RecordCommand*>(_cmd.get()));
////			break;
////		}
////	}
//	
//	zmq::context_t _ctx(1);
//	zmq::socket_t _skt(_ctx, ZMQ_PUB);
//	_skt.connect("tcp://127.0.0.1:8000");
//	
//	std::stringstream _type_stream;
//	std::stringstream _exe_stream;
//	boost::archive::text_oarchive _type_archive(_type_stream);
//	boost::archive::text_oarchive _exe_archive(_exe_stream);
//	_type_archive << _type;
//	_exe_archive << _exe;
//	
//	
//	std::string _type_msg_str = _type_stream.str();
//	std::string _exe_msg_str = _exe_stream.str();
//	zmq::message_t _type_msg(_type_msg_str.length());
//	zmq::message_t _exe_msg(_exe_msg_str.length());
//	
//	
//	memcpy(_type_msg.data(), _type_msg_str.data(), _type_msg_str.length());
//	memcpy(_exe_msg.data(), _exe_msg_str.data(), _exe_msg_str.length());
//	
//	_skt.send(_type_msg, ZMQ_SNDMORE);
//	_skt.send(_exe_msg, 0);
//	
//	//this->start_thread(std::bind(&KinectDaemon::open_cmd_backchannel,this,this->unique_thread_id), <#std::shared_ptr<Event> _event#>)
//}
