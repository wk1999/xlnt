
/*
    wk 2018/10/18
*/

#pragma once

#include <string>

namespace xlnt {

class workstream_visitor {
    std::string name_;
public:
    workstream_visitor(const std::string & name):name_(name){}
    std::string getname() const {return name_;}
    virtual void dosome() {}
};

}

