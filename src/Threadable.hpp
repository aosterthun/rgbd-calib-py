//
//  Threadable.hpp
//  kinectdaemon
//
//  Created by Arne Osterthun on 19.09.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef Threadable_hpp
#define Threadable_hpp

#include <stdio.h>
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include <memory>
#include "Event.hpp"

class Threadable
{
private:
	std::map<unsigned, std::shared_ptr<std::thread>> running_threads;
	std::vector<unsigned> finished_threads;
	unsigned unique_thread_id;
	std::shared_ptr<std::mutex> thread_mutex;
public:
	void start_thread(std::shared_ptr<std::function<void (std::shared_ptr<Event> _event, unsigned _unique_thread_id)>> _functor, std::shared_ptr<Event> _event);
	void end_thread(std::shared_ptr<Event> _event, unsigned _unique_thread_id);
};

#endif /* Threadable_hpp */
