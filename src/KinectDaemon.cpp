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

KinectDaemon::KinectDaemon(std::string const& _server_port, std::string const& _client_port)
{
	this->recv_timeo = 5000;
	this->ctx = std::make_shared<zmq::context_t>(1);
	this->pub_skt = std::make_shared<zmq::socket_t>(*this->ctx.get(), ZMQ_PUB);
	this->sub_skt = std::make_shared<zmq::socket_t>(*this->ctx.get(), ZMQ_SUB);
	
	this->pub_skt->connect("tcp://" + _server_port + ":8000");
	this->sub_skt->bind("tcp://*:8000");
    this->sub_skt->setsockopt(ZMQ_SUBSCRIBE, "", 0);
	this->sub_skt->setsockopt(ZMQ_RCVTIMEO, &this->recv_timeo, sizeof(this->recv_timeo));

    sleep(1);

	/*
	 Send handshake:
		- Client IP
    */

	KinectDaemonHandshake _handshake{};
    _handshake.client_ip(_client_port);

    std::stringstream _handshake_ostream;
    {
        boost::archive::text_oarchive _handshake_archive(_handshake_ostream);
        _handshake_archive & _handshake;
    }

    std::string _handshake_msg_str{_handshake_ostream.str()};
    zmq::message_t _send_handshake{_handshake_msg_str.size()};
    memcpy((void *)_send_handshake.data(), _handshake_msg_str.data(), _handshake_msg_str.size());

    auto _handshake_string = std::string(static_cast<char *>(_send_handshake.data()), _send_handshake.size());
    std::stringstream _handshake_stream{_handshake_string};
    boost::archive::text_iarchive _handshake_archive{_handshake_stream};
    KinectDaemonHandshake _recv_handshake{};
    _handshake_archive >> _recv_handshake;
    std::cout << "Client_IP:" << _recv_handshake.client_ip() << std::endl;
    this->pub_skt->send(_send_handshake);

	/*
	 Receive handshake OK
	 Timeout: 2s (this->recv_timeo)
	 */
	zmq::message_t _recv_ohandshake;
	if(this->sub_skt->recv(&_recv_ohandshake))
	{
        std::cout << "Received handshake answer" << std::endl;
        std::shared_ptr<KinectDaemonHandshake> _recv_handshake = std::make_shared<KinectDaemonHandshake>();
        auto _handshake_string = std::string(static_cast<char *>(_recv_ohandshake.data()), _recv_ohandshake.size());
        std::stringstream _handshake_stream(_handshake_string);
        boost::archive::text_iarchive _handshake_archive(_handshake_stream);
        _handshake_archive & *_recv_handshake.get();
        this->kinect_daemon_com_port = _recv_handshake->client_ip();
        std::cout << "ComPort:" << _recv_handshake->client_ip() << std::endl;
	}
	else
	{
        std::cout << "Did not receive handshake answer" << std::endl;
	}
}

std::shared_ptr<PlayCommand> KinectDaemon::play(const std::string &_filename)
{
	std::shared_ptr<PlayCommand> _play = std::make_shared<PlayCommand>();
    _play->filename("test.stream");
	this->execute(ZMQMessageType::PLAY, _play);
	return _play;
}
/*
void KinectDaemon::open_cmd_backchannel(std::shared_ptr<Event> _event, unsigned _unique_thread_id)
{

}
*/
void KinectDaemon::execute(ZMQMessageType _type, std::shared_ptr<AbstractCommand> _cmd)
{
	//std::shared_ptr<PlayCommand> _exe(std::dynamic_pointer_cast<PlayCommand>(_cmd));
	PlayCommand _exe;
	_exe.filename("test");

	zmq::context_t _ctx(1);
	zmq::socket_t _skt(_ctx, ZMQ_PUB);
	uint32_t hwm = 10000;
  	_skt.setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
	std::cout << this->kinect_daemon_com_port.substr(this->kinect_daemon_com_port.find(":")+1,this->kinect_daemon_com_port.length()) << std::endl;
	_skt.bind("tcp://0.0.0.0:"+this->kinect_daemon_com_port.substr(this->kinect_daemon_com_port.find(":")+1,this->kinect_daemon_com_port.length()));

	sleep(1);
	GenericMessage msg;

	msg.set_payload(_cmd);
	_skt.send(msg.build_zmq_message());
	//this->start_thread(std::bind(&KinectDaemon::open_cmd_backchannel,this,this->unique_thread_id), <#std::shared_ptr<Event> _event#>)
}
