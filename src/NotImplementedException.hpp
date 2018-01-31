//
// Created by arne on 07.11.17.
//

#ifndef RGBD_CALIB_NOTIMPLEMENTEDEXCEPTION_HPP
#define RGBD_CALIB_NOTIMPLEMENTEDEXCEPTION_HPP

#include <stdexcept>

class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error("Function not yet implemented") { };
};

#endif //RGBD_CALIB_NOTIMPLEMENTEDEXCEPTION_HPP
