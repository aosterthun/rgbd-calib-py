//
//  CommandStatus.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 28.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef CommandStatus_hpp
#define CommandStatus_hpp

#include <stdio.h>

enum CommandStatus : int {NOT_A_FILE = 501, STARTED = 201, FINISHED = 202, STOP = 101, PAUSE = 102, PAUSED = 203, STOPED = 204};

namespace boost {
	namespace serialisation {
		template<class Archive>
		void save(Archive & ar, const CommandStatus & t, const unsigned int version){
			int c = (int) t;
			ar & c;
		}
		
		template<class Archive>
		void load(Archive & ar, CommandStatus & t, unsigned int version)
		{
			int c;
			ar & c;
			t = (CommandStatus) c;
		}
	}
}
#endif /* CommandStatus_hpp */
