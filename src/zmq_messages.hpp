#ifndef zmq_messages_hpp
#define zmq_messages_hpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cctype>

#define BOOL_STR(b) ((b)?"true":"false")

namespace pykinecting{
	
	enum Message_Type {PLAY, RECORD, SUCCESS, ERROR, RECORD_PLAY};
	
	inline std::string toString(const Message_Type& type){
	}
	
	inline std::ostream& operator<<  (std::ostream& os, const Message_Type& obj){
	}
	
	inline std::string play(Message_Type type,std::string& message_id, std::string& filepath_src){
	}

	inline std::string play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe){
	}
	
	inline std::string play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, bool loop){
	}


	inline std::string record(Message_Type type,std::string& message_id, std::string& filepath_dest, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed){
	}
	
	inline std::string record_play(Message_Type type,std::string& message_id, std::string& filepath_src, std::string& startframe, std::string& endframe, std::string& filepath_dest, std::string& num_cameras){
	}

	inline std::string response(Message_Type type,std::string& message_id){
	}
	
	inline std::string expandToLength(size_t toExpand, int length){
	}
}

#endif