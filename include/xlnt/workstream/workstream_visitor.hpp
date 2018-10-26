
/*
    wk 2018/10/18
*/

#pragma once
#if defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#include <string>

namespace xlnt {

class workstream_path_stack;

class workstream_visitor {
    std::string name_;
    const workstream_path_stack * ps_;

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
    workstream_visitor():ps_(nullptr){}

    virtual ~workstream_visitor(){}

    void init_path_stack(const workstream_path_stack & ps) {
        ps_ = &ps;
    }

    const workstream_path_stack & get_path_stack() const {
        return (*ps_);
    }

    virtual void before_visit(const std::string & visit_name UNUSED, const void * visit_data UNUSED) {}

    virtual void after_visit(const std::string & visit_name UNUSED) {}

    virtual visit_actions start_element(const std::string & element UNUSED, std::string & newval UNUSED)
    {
        return (WRITE);
    }

    virtual void end_element() {}

    virtual visit_actions start_attribute(const std::string & attr UNUSED, std::string & newval UNUSED)
    {
        return (WRITE);
    }

    virtual void end_attribute() {}

    virtual visit_actions character(const std::string & value UNUSED, std::string & newval UNUSED)
    {
        return (WRITE);
    }

    virtual visit_actions start_ns(const std::string & ns UNUSED, const std::string & prefix UNUSED)
    {
        return (WRITE);
    }
};

}
