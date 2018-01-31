//
//  KinectDaemon.hpp
//  kinectdaemon
//
//  Created by Arne Osterthun on 18.09.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef KinectDaemon_hpp
#define KinectDaemon_hpp

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
#include <NotImplementedException.hpp>
#include <PlayCommand.hpp>
#include <RecordCommand.hpp>
#include <GenericMessage.hpp>
#include <AbstractObserver.hpp>

class KinectDaemon : public AbstractObserver, public std::enable_shared_from_this<KinectDaemon>
{
private:
	std::shared_ptr<zmq::context_t> ctx;
	std::shared_ptr<zmq::socket_t> pub_skt;
	std::shared_ptr<zmq::socket_t> sub_skt;
	int recv_timeo;
	std::string kinect_daemon_com_port;
	std::map<unsigned, std::shared_ptr<std::thread>> running_threads;
    std::vector<unsigned> finished_threads;
    unsigned unique_thread_id;
    std::shared_ptr<std::mutex> thread_mutex;

public:
	KinectDaemon(std::string const& _server_port, std::string const& _client_port);
//	std::shared_ptr<PlayCommand> play();
	std::shared_ptr<PlayCommand> play(std::string const& _filename);
	std::shared_ptr<PlayCommand> play(std::string const& _filename, std::string const& _socket);
//	std::shared_ptr<PlayCommand> play(std::string const& _filename,unsigned _num_kinect_cameras = 4);
	std::shared_ptr<RecordCommand> record();
	std::shared_ptr<RecordCommand> record(std::string const& _filename, std::string const& _socket, unsigned _num_rgbd_sensors = 4);
	void execute(ZMQMessageType _type, std::shared_ptr<AbstractCommand> _cmd);
//	void open_cmd_backchannel(std::shared_ptr<Event> _event);
	void update(std::shared_ptr<Observable> _observable);
    void update(Observable* _observable);
    void update(std::shared_ptr<Observable> _observable, std::shared_ptr<Event> _event);
    void update(Observable* _observable, std::shared_ptr<Event> _event);
};

#endif /* KinectDaemon_hpp */
