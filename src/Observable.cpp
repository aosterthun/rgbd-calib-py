//
//  Observable.cpp
//  ZMQ
//
//  Created by Arne Osterthun on 21.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#include "Observable.hpp"

Observable::Observable()
{
    //std::cout << "Init Observable" << std::endl;
}

void Observable::attach(std::shared_ptr<AbstractObserver> observer)
{
    observers.push_back(observer);
}
void Observable::detach(std::shared_ptr<AbstractObserver> observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
void Observable::notify()
{
    for(std::shared_ptr<AbstractObserver> observer : observers)
    {
		try
		{
			observer->update(shared_from_this());
		}
		catch (const std::bad_weak_ptr& e)
		{
			observer->update(this);
		}

    }
}

void Observable::notify(std::shared_ptr<Event> _event)
{
	for(std::shared_ptr<AbstractObserver> observer : observers)
	{
		observer->update(shared_from_this(), _event);
	}
}
