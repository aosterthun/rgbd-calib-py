//
//  Threadable.cpp
//  kinectdaemon
//
//  Created by Arne Osterthun on 19.09.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#include "Threadable.hpp"

void Threadable::start_thread(std::shared_ptr<std::function<void (std::shared_ptr<Event> _event, unsigned _unique_thread_id)>> _functor, std::shared_ptr<Event> _event)
{
//	std::shared_ptr<std::thread> _thr = std::make_shared<std::thread>(_functor, this , _event, unique_thread_id);
//	this->running_threads.insert(std::make_pair(unique_thread_id,_thr));
//	++unique_thread_id;
//	std::lock_guard<std::mutex> _lock{*this->thread_mutex.get()};
//	for(auto id : finished_threads){
//		auto thread = this->running_threads.find(id);
//		thread->second->join();
//		this->finished_threads.erase(std::remove(this->finished_threads.begin(), this->finished_threads.end(), id), this->finished_threads.end());
//	}
}

void Threadable::end_thread(std::shared_ptr<Event> _event, unsigned _unique_thread_id)
{
	std::lock_guard<std::mutex> _lock{*this->thread_mutex};
	this->finished_threads.push_back(_unique_thread_id);
}
