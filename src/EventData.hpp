//
//  EventData.hpp
//  ZMQ
//
//  Created by Arne Osterthun on 31.08.17.
//  Copyright © 2017 Arne Osterthun. All rights reserved.
//

#ifndef EventData_hpp
#define EventData_hpp

#include <stdio.h>

template<class T>
class EventData
{
private:
	T data;
public:
	void set_data(T _data)
	{
		this->data = _data;
	}
	
	T get_data()
	{
		return this->data;
	}
};

#endif /* EventData_hpp */
