//
//  AbstractObserver.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 21.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef AbstractObserver_hpp
#define AbstractObserver_hpp

#include <stdio.h>
#include <memory>
#include "Observable.hpp"
#include "Event.hpp"

class Observable;

class AbstractObserver
{
public:
    virtual void update(std::shared_ptr<Observable> _observable) = 0;
	virtual void update(Observable* _observable) = 0;
	virtual void update(std::shared_ptr<Observable> _observable, std::shared_ptr<Event> _event) = 0;
	virtual void update(Observable* _observable, std::shared_ptr<Event> _event) = 0;
};

#endif /* AbstractObserver_hpp */
