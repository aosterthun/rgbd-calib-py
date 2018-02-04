//
//  KinectDaemon.cpp
//  kinectdaemon
//
//  Created by Arne Osterthun on 18.09.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

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

	this->client_ip = _client_port;
	this->server_ip = _server_port;

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

void KinectDaemon::update(Observable *_observable) {
    throw NotImplemented();
}

void KinectDaemon::update(Observable *_observable, std::shared_ptr<Event> _event) {
    throw NotImplemented();
}

void KinectDaemon::update(std::shared_ptr<Observable> _observable, std::shared_ptr<Event> _event) {
    std::cout << "[START] void KinectDaemon::update(std::shared_ptr<Observable> _observable, std::shared_ptr<Event> _event)" << std::endl;
    /*std::lock_guard<std::mutex> _lock{*this->thread_mutex.get()};
    for(auto id : finished_threads){
        auto thread = this->running_threads.find(id);
        thread->second->join();
        this->finished_threads.erase(std::remove(this->finished_threads.begin(), this->finished_threads.end(), id), this->finished_threads.end());
    }*/
    std::cout << "[END] void KinectDaemon::update(std::shared_ptr<Observable> _observable, std::shared_ptr<Event> _event)" << std::endl;
}

void KinectDaemon::update(std::shared_ptr<Observable> _observable) {
    throw NotImplemented();
}

std::shared_ptr<PlayCommand> KinectDaemon::play(const std::string &_filename)
{
	std::shared_ptr<PlayCommand> _play = std::make_shared<PlayCommand>();
  _play->filename(_filename);
  _play->server_address("127.0.0.1");
	_play->set_backchannel_com_port("tcp://" + this->client_ip + ":8001");
	this->execute(ZMQMessageType::PLAY, _play);
	_play->set_backchannel_com_port("tcp://" + this->server_ip + ":8001");
	return _play;
}

std::shared_ptr<PlayCommand> KinectDaemon::play(const std::string &_filename, std::string const& _socket,unsigned _num_kinect_cameras)
{
	std::shared_ptr<PlayCommand> _play = std::make_shared<PlayCommand>();
  _play->filename(_filename);
  _play->server_address(_socket);
	_play->num_kinect_cameras(_num_kinect_cameras);
	_play->set_backchannel_com_port("tcp://" + this->client_ip + ":8001");
	this->execute(ZMQMessageType::PLAY, _play);
	_play->set_backchannel_com_port("tcp://" + this->server_ip + ":8001");
	return _play;
}

std::shared_ptr<RecordCommand> KinectDaemon::record()
{
	std::shared_ptr<RecordCommand> _record = std::make_shared<RecordCommand>();
  _record->filename("/home/mejo6715/Hiwi/kinect_recordings/rgbdri_rec_2.stream");
  _record->server_address("141.54.147.106:7000");
  _record->num_kinect_cameras(4);
	_record->set_backchannel_com_port("tcp://" + this->client_ip + ":8001");
	this->execute(ZMQMessageType::RECORD, _record);
	_record->set_backchannel_com_port("tcp://" + this->server_ip + ":8001");
	return _record;
}

std::shared_ptr<RecordCommand> KinectDaemon::record(std::string const& _filename, std::string const& _socket, unsigned _num_rgbd_sensors){
	std::shared_ptr<RecordCommand> _record = std::make_shared<RecordCommand>();
  _record->filename(_filename);
  _record->server_address(_socket);
	_record->set_backchannel_com_port("tcp://" + this->client_ip + ":8001");
  _record->num_kinect_cameras(_num_rgbd_sensors);

	this->execute(ZMQMessageType::RECORD, _record);
	_record->set_backchannel_com_port("tcp://" + this->server_ip + ":8001");
	return _record;
}

/*
void KinectDaemon::open_cmd_backchannel(std::shared_ptr<Event> _event, unsigned _unique_thread_id)
{

}
*/
void KinectDaemon::execute(ZMQMessageType _type, std::shared_ptr<AbstractCommand> _cmd)
{
	zmq::context_t _ctx(1);
	zmq::socket_t _skt(_ctx, ZMQ_PUB);
	uint32_t hwm = 10000;
  	_skt.setsockopt(ZMQ_SNDHWM,&hwm, sizeof(hwm));
	std::cout << this->kinect_daemon_com_port.substr(this->kinect_daemon_com_port.find(":")+1,this->kinect_daemon_com_port.length()) << std::endl;
	_skt.bind("tcp://0.0.0.0:"+this->kinect_daemon_com_port.substr(this->kinect_daemon_com_port.find(":")+1,this->kinect_daemon_com_port.length()));
	sleep(1);
    GenericMessage msg;
	msg.set_type(_type);
	msg.set_payload(_cmd);
	_skt.send(msg.build_zmq_message());

}
