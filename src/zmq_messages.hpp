#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cctype>
#define BOOL_STR(b) ((b)?"true":"false")

namespace pykinecting{
	
	enum Message_Type {PLAY, RECORD, SUCCESS, ERROR};
	
	std::string toString(const Message_Type& type){
		switch (type) {
			case PLAY:
				return "0";
				break;
			case RECORD:
				return "1";
				break;
			case SUCCESS:
				return "2";
				break;
			case ERROR:
				return "3"; //Error can't be 'E' because default is already 'E'. DUH.
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

    std::string record(Message_Type type,std::string& message_id, std::string& filepath_dest, std::string serverport, std::string num_cameras, std::string duration_in_secs, bool is_compressed){
        std::string msg;
        filepath_dest.append(255 - filepath_dest.length(), '_');
        message_id.append(3 - message_id.length(), '_');
        std::string exType = pykinecting::toString(type);
        exType.append(2 - exType.length(), '_');
        serverport.append(17 - serverport.length, '_')
        duration_in_secs.append(3 - duration_in_secs.length(), '_')
        msg.append(exType);
        msg.append(message_id);
        msg.append(filepath_dest);
        msg.append(serverport);
        msg.append(duration_in_secs);
        msg.append(BOOL_STR(is_compressed));
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
	
	std::string expandToLength(size_t toExpand, int length){
		std::string tmp_str = std::to_string(toExpand);
		tmp_str.append(length - tmp_str.length(), '\t');
		return tmp_str;
	}

}

