//
//  KinectDaemonHandshake.hpp
//  kinectdaemon
//
//  Created by Arne Osterthun on 19.09.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef KinectDaemonHandshake_hpp
#define KinectDaemonHandshake_hpp


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <zmq.hpp>
#include <thread>
#include <memory>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/thread.hpp>

class KinectDaemonHandshake
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & client_ip_mem;
	}
	std::string client_ip_mem;

public:
	KinectDaemonHandshake();
	void client_ip(std::string _client_ip);
	std::string client_ip();
};

#endif /* KinectDaemonHandshake_hpp */
