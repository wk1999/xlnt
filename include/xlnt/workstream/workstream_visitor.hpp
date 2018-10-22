
/*
    wk 2018/10/18
*/

#pragma once

#include <string>

namespace xlnt {

class workstream_visitor {
    std::string name_;
public:
    enum visit_actions {
        // write the original value to ostream
        WRITE = 0,
        // replace the original value with the new value then write to ostream
        REPLACE,
        // do not write this whole element/attribute to ostream
        // only valid at start_element/start_attribute
        SKIP,
    };
public:
    virtual void before_visit(const std::string & visit_name) {}
    virtual void after_visit(const std::string & visit_name) {}
    virtual visit_actions start_element(const std::string & element, std::string & newval)
    {
        return (WRITE);
    }
    virtual void end_element() {}
    virtual visit_actions start_attribute(const std::string & attr, std::string & newval)
    {
        return (WRITE);
    }
    virtual void end_attribute() {}
    virtual visit_actions character(const std::string & value, std::string & newval)
    {
        return (WRITE);
    }
    virtual visit_actions start_ns(const std::string & ns, std::string & newval)
    {
        return (WRITE);
    }
};

}

