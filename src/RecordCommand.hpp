//
//  RecordCommand.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 21.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef RecordCommand_hpp
#define RecordCommand_hpp


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <zmq.hpp>
#include <thread>
#include <memory>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/thread.hpp>
#include <AbstractCommand.hpp>
#include <ZMQMessageType.hpp>
#include <Observable.hpp>
#include <CommandStatus.hpp>
#include <ThreadEvent.hpp>
class ZMQMessagingChannel;

class RecordCommand : public AbstractCommand, public Observable
{
private:
	std::shared_ptr<zmq::context_t> zmq_context;
	std::shared_ptr<zmq::socket_t> zmq_pub_socket;
	std::shared_ptr<zmq::socket_t> zmq_sub_socket;
	std::string cmd_filename;
	std::string cmd_server_address;
    std::string cmd_backchannel_com_port;
	unsigned cmd_num_kinect_cameras;
	unsigned cmd_num_seconds_to_record;
	bool cmd_rgb_is_compressed;
	unsigned cmd_wait_frames_to_before_start;
	bool is_running;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & cmd_filename;
		ar & cmd_server_address;
		ar & cmd_num_kinect_cameras;
		ar & cmd_num_seconds_to_record;
		ar & cmd_rgb_is_compressed;
		ar & cmd_wait_frames_to_before_start;
		ar & cmd_backchannel_com_port;
	}
public:
	RecordCommand();
    void set_backchannel_com_port(std::string const& _com_port);
    std::vector<std::string> get_backchannel_port(bool _port_only);
    void execute(std::shared_ptr<Event> _event);
    void stop();
	ZMQMessageType get_type();
	void listen_on_backchannel();
	void send_on_backchannel(int const _status);
	void filename(std::string const& _filename);
	std::string filename() const;
	void server_address(std::string const& _server_address);
	std::string server_address() const;
	void num_kinect_cameras(unsigned _num_kinect_cameras);
	unsigned num_kinect_cameras() const;
	void num_seconds_to_record(unsigned _max_fps);
	unsigned num_seconds_to_record() const;
	void rgb_is_compressed(bool _rgb_is_compressed);
	bool rgb_is_compressed() const;
	void wait_frames_to_before_start(unsigned _wait_frames_to_before_start);
	unsigned wait_frames_to_before_start() const;
};

#endif /* RecordCommand_hpp */
