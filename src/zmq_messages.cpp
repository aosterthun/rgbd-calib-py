#ifndef zmq_messages_hpp
#define zmq_messages_hpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cctype>
#include <zmq_messages.hpp>

#define BOOL_STR(b) ((b)?"true":"false")

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
	
	std::string play(Message_Type type,std::string& message_id, std::string& filepath_src){
		std::string msg;
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		return msg;
	}
	
	zmq_message_t play(Message_Type type,std::string& message_id, std::string& filepath_src){
		std::string msg;
		filepath_src.append(255 - filepath_src.length(), '_');
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		msg.append(filepath_src);
		return msg;
	}

	std::string play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe){
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
		return msg;
	}
	
	std::string play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, bool loop){
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
		
		return msg;
	}
	
	
	std::string record(Message_Type type,std::string& message_id, std::string& filepath_dest, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed){
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
		return msg;
	}
	
	std::string record_play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, std::string& filepath_dest, std::string& num_cameras){
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
		
		return msg;
	}
	
	std::string response(Message_Type type,std::string& message_id){
		std::string msg;
		message_id.append(3 - message_id.length(), '_');
		std::string exType = pykinecting::toString(type);
		exType.append(2 - exType.length(), '_');
		msg.append(exType);
		msg.append(message_id);
		return msg;
	}
	
	std::vector<std::string> resolveResponse(Message_Type type, std::string& response){
		std::vector<std::string> resolvedResponse;
		
		switch (type) {
			case PLAY:
				resolvedResponse.push_back(response.substr(0,2));
				resolvedResponse.push_back(response.substr(2,3));
				resolvedResponse.push_back(response.substr(4,255));
				break;
			case PLAY_FRAMES:
				resolvedResponse.push_back(response.substr(0,2));
				resolvedResponse.push_back(response.substr(2,3));
				resolvedResponse.push_back(response.substr(5,255));
				resolvedResponse.push_back(response.substr(260,5));
				resolvedResponse.push_back(response.substr(265,5));
				break;
			case PLAY_FRAMES_LOOP:
				resolvedResponse.push_back(response.substr(0,2));
				resolvedResponse.push_back(response.substr(2,3));
				resolvedResponse.push_back(response.substr(5,255));
				resolvedResponse.push_back(response.substr(260,5));
				resolvedResponse.push_back(response.substr(265,5));
				resolvedResponse.push_back(response.substr(270,1));
				break;
			case RECORD:
				resolvedResponse.push_back(response.substr(0,2));
				resolvedResponse.push_back(response.substr(2,3));
				resolvedResponse.push_back(response.substr(5,255));
				resolvedResponse.push_back(response.substr(260,17));
				resolvedResponse.push_back(response.substr(277,1));
				resolvedResponse.push_back(response.substr(278,3));
				resolvedResponse.push_back(response.substr(281,1));
				break;
			case RECORD_PLAY:
				resolvedResponse.push_back(response.substr(0,2));
				resolvedResponse.push_back(response.substr(2,3));
				resolvedResponse.push_back(response.substr(5,255));
				resolvedResponse.push_back(response.substr(260,5));
				resolvedResponse.push_back(response.substr(265,5));
				resolvedResponse.push_back(response.substr(270,255));
				resolvedResponse.push_back(response.substr(525,1));
				break;
			default:
				break;
		}
		
		for (auto i : resolvedResponse) {
			std::cout << i << std::endl;
			i.erase(std::remove(i.begin(),i.end(),'_'), i.end());
			//std::cout << i << std::endl;
		}
		
		return resolvedResponse;
	}
}

#endif