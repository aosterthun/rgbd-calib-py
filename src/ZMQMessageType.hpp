//
//  ZMQMessageType.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 22.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef ZMQMessageType_hpp
#define ZMQMessageType_hpp

#include <stdio.h>

enum ZMQMessageType : int {PLAY = 0, RECORD = 1, PLAY_RECORD_IN_SYNC = 2};

namespace boost {
	namespace serialisation {
		template<class Archive>
		void save(Archive & ar, const ZMQMessageType & t, const unsigned int version){
			int c = (int) t;
			ar & c;
		}
		
		template<class Archive>
		void load(Archive & ar, ZMQMessageType & t, unsigned int version)
		{
			int c;
			ar & c;
			t = (ZMQMessageType) c;
		}
	}
}
#endif /* ZMQMessageType_hpp */
