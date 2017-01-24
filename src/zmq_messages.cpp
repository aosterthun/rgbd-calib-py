#ifndef zmq_messages_hpp
#define zmq_messages_hpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cctype>
#include <zmq_messages.hpp>

#define BOOL_STR(b) ((b)?"true":"false")

//
//  main.cpp
//  kinectServiceProtocolMessage
//
//  Created by Arne Osterthun on 21.01.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#include <zmq.hpp>
#include <vector>
#include <iostream>
#include <cstring>
#include "message.cpp"
#include <algorithm>
#include <string>
#include <cctype>
#define BOOL_STR(b) ((b)?"1":"0")

namespace pykinecting{
    
	enum Message_Type {PLAY, PLAY_FRAMES, PLAY_FRAMES_LOOP, RECORD, SUCCESS, ERROR, RECORD_PLAY};
	
	std::string toString(const Message_Type& type){
		switch (type) {
			case PLAY:
				return "0";
				break;
			case PLAY_FRAMES:
				return "1";
				break;
			case PLAY_FRAMES_LOOP:
				return "2";
				break;
			case RECORD:
				return "3";
				break;
			case RECORD_PLAY:
				return "4";
				break;
			case SUCCESS:
				return "5";
				break;
			case ERROR:
				return "6"; //Error can't be 'E' because default is already 'E'. DUH.
				break;
			default:
				return "E";
				break;
		}
	}
	
	std::ostream& operator<<  (std::ostream& os, const Message_Type& obj){
		switch (obj) {
			case PLAY:
				os << "0";
				break;
				
			default:
				break;
		}
		return os;
	}
	
	
	zmq::message_t play(Message_Type type,std::string& message_id, std::string& filepath_src){
		zmq::message_t zmq_msg(260);
		std::string msg;
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		//std::cout << msg.c_str() << std::endl;
		memcpy(zmq_msg.data(),msg.c_str(),260);
		//std::cout << zmq_msg.size() << std::endl;
		return zmq_msg;
	}
	
	zmq::message_t play_frames(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe){
		zmq::message_t zmq_msg(270);
		std::string msg;
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		startframe.append(5 - startframe.length(), '_');
		endframe.append(5 - endframe.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		msg.append(startframe);
		msg.append(endframe);
		memcpy(zmq_msg.data(),&msg,270);
		return zmq_msg;
	}
	
	zmq::message_t play_frames_loop(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, bool loop){
		zmq::message_t zmq_msg(271);
		std::string msg;
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		startframe.append(5 - startframe.length(), '_');
		endframe.append(5 - endframe.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		msg.append(startframe);
		msg.append(endframe);
		msg.append(BOOL_STR(loop));
		
		memcpy(zmq_msg.data(),&msg,271);
		return zmq_msg;
	}
	
	
	zmq::message_t record(Message_Type type,std::string& message_id, std::string& filepath_dest, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed){
		zmq::message_t zmq_msg(282);
		std::string msg;
		filepath_dest.append(255 - filepath_dest.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		serverport.append(17 - serverport.length(), '_');
		duration_in_secs.append(3 - duration_in_secs.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_dest);
		msg.append(serverport);
		msg.append(num_cameras);
		msg.append(duration_in_secs);
		msg.append(BOOL_STR(is_compressed));
		
		memcpy(zmq_msg.data(),&msg,282);
		return zmq_msg;
	}
	
	zmq::message_t record_play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, std::string& filepath_dest, std::string& num_cameras){
		zmq::message_t zmq_msg(521);
		std::string msg;
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		filepath_src.append(255 - filepath_src.length(), '_');
		filepath_dest.append(255 - filepath_dest.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		startframe.append(5 - startframe.length(), '_');
		endframe.append(5 - endframe.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		msg.append(startframe);
		msg.append(endframe);
		msg.append(filepath_dest);
		msg.append(num_cameras);
		
		memcpy(zmq_msg.data(),&msg,521);
		return zmq_msg;
	}
	
	zmq::message_t response(Message_Type type,std::string& message_id){
		zmq::message_t zmq_msg(6);
		std::string msg;
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		memcpy(zmq_msg.data(),&msg,6);
		return zmq_msg;
	}
	
	std::vector<std::string> resolveResponse(Message_Type type, zmq::message_t response){
		
		std::string responseString;
		char responseArray[response.size()-4];
		std::vector<std::string> resolvedResponse;
		
		switch (type) {
			case PLAY:
				memcpy(&responseArray, response.data(), 260);
				responseString = responseArray;
				
				resolvedResponse.push_back(responseString.substr(0,2));
				resolvedResponse.push_back(responseString.substr(2,3));
				resolvedResponse.push_back(responseString.substr(5,255));
				break;
			case PLAY_FRAMES:
				memcpy(&responseArray, &response, 270);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,2));
				resolvedResponse.push_back(responseString.substr(2,3));
				resolvedResponse.push_back(responseString.substr(5,255));
				resolvedResponse.push_back(responseString.substr(260,5));
				resolvedResponse.push_back(responseString.substr(265,5));
				break;
			case PLAY_FRAMES_LOOP:
				memcpy(&responseArray, &response, 271);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,2));
				resolvedResponse.push_back(responseString.substr(2,3));
				resolvedResponse.push_back(responseString.substr(5,255));
				resolvedResponse.push_back(responseString.substr(260,5));
				resolvedResponse.push_back(responseString.substr(265,5));
				resolvedResponse.push_back(responseString.substr(270,1));
				break;
			case RECORD:
				memcpy(&responseArray, &response, 282);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,2));
				resolvedResponse.push_back(responseString.substr(2,3));
				resolvedResponse.push_back(responseString.substr(5,255));
				resolvedResponse.push_back(responseString.substr(260,17));
				resolvedResponse.push_back(responseString.substr(277,1));
				resolvedResponse.push_back(responseString.substr(278,3));
				resolvedResponse.push_back(responseString.substr(281,1));
				break;
			case RECORD_PLAY:
				memcpy(&responseArray, &response, 521);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,2));
				resolvedResponse.push_back(responseString.substr(2,3));
				resolvedResponse.push_back(responseString.substr(5,255));
				resolvedResponse.push_back(responseString.substr(260,5));
				resolvedResponse.push_back(responseString.substr(265,5));
				resolvedResponse.push_back(responseString.substr(270,255));
				resolvedResponse.push_back(responseString.substr(525,1));
				break;
			default:
				break;
		}
		
		std::vector<std::string> nichttest;
		for (auto i : resolvedResponse) {
			//std::cout << i << std::endl;
			i.erase(std::remove(i.begin(),i.end(),'_'), i.end());
			test.push_back(i);
			//std::cout << i << std::endl;
		}
		for (auto i : nichttest) {
		std::cout << i << std::endl;
		}
		return resolvedResponse;
	}
}

#endif