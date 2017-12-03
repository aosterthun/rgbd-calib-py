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
#include <PlayCommand.hpp>

class KinectDaemon
{
private:
	std::shared_ptr<zmq::context_t> ctx;
	std::shared_ptr<zmq::socket_t> pub_skt;
	std::shared_ptr<zmq::socket_t> sub_skt;
	int recv_timeo;
	std::string kinect_daemon_com_port;
	
public:
	KinectDaemon(std::string const& _server_adress);
//	std::shared_ptr<PlayCommand> play();
	void play(std::string const& _filename);
//	std::shared_ptr<PlayCommand> play(std::string const& _filename,unsigned _num_kinect_cameras = 4);
	void execute(ZMQMessageType _type, std::shared_ptr<AbstractCommand> _cmd);
//	void open_cmd_backchannel(std::shared_ptr<Event> _event);
};

#endif /* KinectDaemon_hpp */
