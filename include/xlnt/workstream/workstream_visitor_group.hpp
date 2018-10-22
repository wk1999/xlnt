
/*
    wk 2018/10/18
*/

#pragma once

#include <string>
#include <map>

namespace xlnt {

class workstream_visitor;

class workstream_visitor_group {
    std::string name_;
    std::map<int, workstream_visitor*> visitors_;
    workstream_visitor * default_visitor_;

public:
    const static int default_type = 0;
    const static int workbook = 1;
    const static int worksheet = 2;
    const static int styles = 3;
    const static int shared_string = 4;
    const static int relationship = 5;
    //... and more, now only support worksheet
public:
    workstream_visitor_group(const std::string & name):
        name_(name), default_visitor_(nullptr){}
    std::string getname() const {return name_;}
    void add_visitor(int visit_type, workstream_visitor & visitor)
    {
        if (default_type == visit_type) {
            return;
        }
        visitors_[visit_type] = &visitor;
    }
    void add_default_visitor(workstream_visitor & visitor)
    {
        default_visitor_ = &visitor;
    }
    workstream_visitor * get_visitor(int visit_type) const
    {
        std::map<int, workstream_visitor*>::const_iterator it = visitors_.find(visit_type);
        if (it == visitors_.end()) {
            return (default_visitor_);
        } else {
            return (it->second);
        }
    }
};

}

