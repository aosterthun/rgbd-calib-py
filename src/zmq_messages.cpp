//
//  main.cpp
//  kinectServiceProtocolMessage
//
//  Created by Arne Osterthun on 21.01.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef zmq_messages_hpp
#define zmq_messages_hpp

#include <iostream>
#include <zmq.hpp>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <cctype>
#define BOOL_STR(b) ((b)?"true":"false")

namespace pykinecting{
    
	enum Message_Type {PLAY, PLAY_FRAMES, RECORD, RECORD_PLAY, RESPONSE};
	
	inline std::string toString(const Message_Type& type){
		switch (type) {
			case PLAY:
				return "0";
				break;
			case PLAY_FRAMES:
				return "1";
				break;
			case RECORD:
				return "2";
				break;
			case RECORD_PLAY:
				return "3";
				break;
			case RESPONSE:
				return "4";
				break;
			default:
				return "E";
				break;
		}
	}
	
	inline std::ostream& operator<<  (std::ostream& os, const Message_Type& obj){
		switch (obj) {
			case PLAY:
				os << "0";
				break;
				
			default:
				break;
		}
		return os;
	}
	
	
	inline std::vector<zmq::message_t> play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& user_id){
		zmq::message_t zmq_msg(529);
		zmq::message_t zmq_msg2(1);
		std::string msg;
		std::string msg2;
		std::vector<zmq::message_t> messages;
		
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		//exType.append(2 - exType.length(), '_');
		user_id.append(4 - user_id.length(), '_');
		
		msg2.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		msg.append(user_id);
		msg.append(529 - 264, '_');
		msg.append("\0");
		msg2.append("\0");
		//std::cout << msg.c_str() << std::endl;
		memcpy(zmq_msg.data(),msg.c_str(),529);
		memcpy(zmq_msg2.data(),msg.c_str(),1);

		messages.push_back(std::move(zmq_msg2));
		messages.push_back(std::move(zmq_msg));

		//std::cout << zmq_msg.size() << std::endl;
		return messages;
	}
	
	inline std::vector<zmq::message_t> play_frames(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, bool loop, std::string& user_id){
		zmq::message_t zmq_msg(529);
		zmq::message_t zmq_msg2(3);
		std::string msg;
		std::string msg2;
		std::vector<zmq::message_t> messages;
	
		std::string exType = pykinecting::toString(type);		
		exType.append(2 - exType.length(), '_');
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		startframe.append(5 - startframe.length(), '_');
		endframe.append(5 - endframe.length(), '_');
		user_id.append(4 - user_id.length(), '_');
		
		msg2.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		msg.append(startframe);
		msg.append(endframe);
		msg.append(BOOL_STR(loop));
		msg.append(user_id);
		msg.append(529 - 275, '_');
		msg.append("\0");
		msg2.append("\0");

		memcpy(zmq_msg.data(),msg.c_str(),529);
		memcpy(zmq_msg2.data(),msg.c_str(),3);

		messages.push_back(std::move(zmq_msg2));
		messages.push_back(std::move(zmq_msg));

		return messages;
	}
	
	
	inline std::vector<zmq::message_t> record(Message_Type type,std::string& message_id, std::string& filepath_dest, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed, std::string& user_id){
		zmq::message_t zmq_msg(529);
		zmq::message_t zmq_msg2(3);
		std::string msg;
		std::string msg2;
		std::vector<zmq::message_t> messages;

		filepath_dest.append(255 - filepath_dest.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		serverport.append(17 - serverport.length(), '_');
		duration_in_secs.append(3 - duration_in_secs.length(), '_');
		user_id.append(4 - user_id.length(), '_');

		msg2.append(exType);
		msg.append(message_id);
		msg.append(filepath_dest);
		msg.append(serverport);
		msg.append(num_cameras);
		msg.append(duration_in_secs);
		msg.append(BOOL_STR(is_compressed));
		msg.append(user_id);
		msg.append(529 - 286, '_');
		msg.append("\0");
		msg2.append("\0");

		memcpy(zmq_msg.data(),msg.c_str(),529);
		memcpy(zmq_msg2.data(),msg.c_str(),3);

		messages.push_back(std::move(zmq_msg2));
		messages.push_back(std::move(zmq_msg));

		return messages;
	}
	
	inline std::vector<zmq::message_t> record_play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, std::string& filepath_dest, std::string& num_cameras, std::string& user_id){
		zmq::message_t zmq_msg(529);
		zmq::message_t zmq_msg2(3);
		std::string msg;
		std::string msg2;
		std::vector<zmq::message_t> messages;

		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		filepath_src.append(255 - filepath_src.length(), '_');
		filepath_dest.append(255 - filepath_dest.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		startframe.append(5 - startframe.length(), '_');
		endframe.append(5 - endframe.length(), '_');
		user_id.append(4 - user_id.length(), '_');

		msg2.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		msg.append(startframe);
		msg.append(endframe);
		msg.append(filepath_dest);
		msg.append(num_cameras);
		msg.append(user_id);
		msg.append(2, '_');
		msg.append("\0");
		msg2.append("\0");
		
		memcpy(zmq_msg.data(),msg.c_str(),529);
		memcpy(zmq_msg2.data(),msg.c_str(),3);

		messages.push_back(std::move(zmq_msg2));
		messages.push_back(std::move(zmq_msg));

		return messages;
	}
	
	inline zmq::message_t response(Message_Type type,std::string& message_id, std::string& user_id, bool success){
		zmq::message_t zmq_msg(10);
		std::string msg;
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		user_id.append(4 - user_id.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(user_id);
		msg.append(BOOL_STR(success));
		msg.append(520, '_');
		memcpy(zmq_msg.data(),&msg,10);
		return zmq_msg;
	}
	
	inline std::vector<std::string> resolveResponse(Message_Type type, zmq::message_t* response){
		
		std::string responseString;
		char responseArray[response->size()-4];
		std::vector<std::string> resolvedResponse;
		
		switch (type) {
			case PLAY:
				memcpy(&responseArray, response->data(), 530);
				responseString = responseArray;	
				resolvedResponse.push_back(responseString.substr(0,3));
				resolvedResponse.push_back(responseString.substr(3,255));
				resolvedResponse.push_back(responseString.substr(258,4));
				resolvedResponse.push_back(responseString.substr(262,530-262));
				break;
			case PLAY_FRAMES:
				memcpy(&responseArray, response->data(), 530);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,3));
				resolvedResponse.push_back(responseString.substr(3,255));
				resolvedResponse.push_back(responseString.substr(258,5));
				resolvedResponse.push_back(responseString.substr(263,5));
				resolvedResponse.push_back(responseString.substr(268,1));
				resolvedResponse.push_back(responseString.substr(269,4));
				resolvedResponse.push_back(responseString.substr(273,530-273));
				break;
			case RECORD:
				memcpy(&responseArray, response->data(), 530);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,3));
				resolvedResponse.push_back(responseString.substr(3,255));
				resolvedResponse.push_back(responseString.substr(258,17));
				resolvedResponse.push_back(responseString.substr(275,1));
				resolvedResponse.push_back(responseString.substr(276,3));
				resolvedResponse.push_back(responseString.substr(279,1));
				resolvedResponse.push_back(responseString.substr(280,4));
				resolvedResponse.push_back(responseString.substr(284,530-284));
				break;
			case RECORD_PLAY:
				memcpy(&responseArray, response->data(), 530);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,3));
				resolvedResponse.push_back(responseString.substr(3,255));
				resolvedResponse.push_back(responseString.substr(258,5));
				resolvedResponse.push_back(responseString.substr(263,5));
				resolvedResponse.push_back(responseString.substr(268,255));
				resolvedResponse.push_back(responseString.substr(523,1));
				resolvedResponse.push_back(responseString.substr(524,4));
				resolvedResponse.push_back(responseString.substr(528,2));

				break;
			case RESPONSE:
				memcpy(&responseArray, response->data(), 530);
				responseString = responseArray;
				resolvedResponse.push_back(responseString.substr(0,2));
				resolvedResponse.push_back(responseString.substr(2,3));
				resolvedResponse.push_back(responseString.substr(5,4));
				resolvedResponse.push_back(responseString.substr(9,1));
				resolvedResponse.push_back(responseString.substr(10,520));
				break;
			default:
				break;
		}
		
		std::vector<std::string> dickbutt;

		for (auto i : resolvedResponse) {
			//std::cout << i << std::endl;
			i.erase(std::remove(i.begin(),i.end(),'_'), i.end());
			dickbutt.push_back(i);
			//std::cout << i << std::endl;
		}
		return dickbutt;
	}
}

#endif

