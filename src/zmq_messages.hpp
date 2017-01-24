#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cctype>

namespace pykinecting{
    
    enum Message_Type {PLAY, RECORD};
    
    std::string toString(const Message_Type& type){
        switch (type) {
            case PLAY:
                return "0";
                break;
            case RECORD:
                return "1";
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
    
    std::string expandToLength(size_t toExpand, int length){
        std::string tmp_str = std::to_string(toExpand);
        tmp_str.append(length - tmp_str.length(), '\t');
        return tmp_str;
    }

}

