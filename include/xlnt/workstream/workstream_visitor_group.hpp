
/*
    wk 2018/10/18
*/

#pragma once

#include <xlnt/packaging/relationship.hpp>
#include <string>
#include <map>

namespace xlnt {

class workstream_visitor;

class workstream_visitor_group {
    std::string name_;
    std::map<relationship_type, workstream_visitor*> visitors_;
    workstream_visitor * default_visitor_;

public:
    workstream_visitor_group(const std::string & name):
        name_(name), default_visitor_(nullptr){}
    std::string getname() const {return name_;}
    void add_visitor(relationship_type visit_type, workstream_visitor & visitor)
    {
        if (relationship_type::unknown == visit_type) {
            return;
        }
        visitors_[visit_type] = &visitor;
    }
    void add_default_visitor(workstream_visitor & visitor)
    {
        default_visitor_ = &visitor;
    }
    workstream_visitor * get_visitor(relationship_type visit_type) const
    {
        std::map<relationship_type, workstream_visitor*>::const_iterator it = visitors_.find(visit_type);
        if (it == visitors_.end()) {
            return (default_visitor_);
        } else {
            return (it->second);
        }
    }
};

}

