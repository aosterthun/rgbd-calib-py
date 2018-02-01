//
//  ThreadEvent.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 30.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef ThreadEvent_hpp
#define ThreadEvent_hpp

#include <stdio.h>
#include <memory>
#include <string>
#include <Event.hpp>
#include <EventData.hpp>

class ThreadEvent : public Event{
private:
	std::string data;
public:
	ThreadEvent(std::string const& _data);
	std::string get_data();
};

#endif /* ThreadEvent_hpp */
