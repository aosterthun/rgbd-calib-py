//
//  AbstractCommand.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 21.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef AbstractCommand_hpp
#define AbstractCommand_hpp

#include <stdio.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "Event.hpp"
#include <ZMQMessageType.hpp>

class AbstractCommand
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){

	}
public:
	virtual ZMQMessageType get_type() = 0;
	virtual void execute(std::shared_ptr<Event> _event) = 0;
};

#endif /* AbstractCommand_hpp */
