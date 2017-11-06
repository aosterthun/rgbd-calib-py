//
//  Observable.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 21.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef Observable_hpp
#define Observable_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "AbstractObserver.hpp"
#include "Event.hpp"

class AbstractObserver;

class Observable : public std::enable_shared_from_this<Observable>
{
private:
    std::vector<std::shared_ptr<AbstractObserver>> observers;
    
public:
    Observable();
    void attach(std::shared_ptr<AbstractObserver> observer);
    void detach(std::shared_ptr<AbstractObserver> observer);
    void notify();
	void notify(std::shared_ptr<Event> _event);
};

#endif /* Observable_hpp */
