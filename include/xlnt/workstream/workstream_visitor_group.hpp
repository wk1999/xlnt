
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
    std::map<relationship_type, workstream_visitor*> visitors_for_type_;
    std::map<std::string, workstream_visitor*> visitors_for_file_;
    workstream_visitor * default_visitor_;

public:
    workstream_visitor_group(const std::string & name);

    std::string getname() const;

    void add_visitor(relationship_type visit_type, workstream_visitor & visitor);

    void add_visitor(std::string visit_file, workstream_visitor & visitor);

    void add_default_visitor(workstream_visitor & visitor);

    workstream_visitor * get_visitor(relationship_type visit_type) const;

    workstream_visitor * get_visitor(const std::string visit_file) const;

    workstream_visitor * get_visitor() const;

    workstream_visitor * get_visitor(const std::string visit_file, relationship_type visit_type) const;
};

}
