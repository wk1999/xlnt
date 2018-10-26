
/*
    wk 2018/10/18
*/

#include <xlnt/workstream/workstream_visitor_group.hpp>

namespace xlnt {

workstream_visitor_group::workstream_visitor_group(const std::string & name):
    name_(name), default_visitor_(nullptr){}

std::string workstream_visitor_group::getname() const {return name_;}

void workstream_visitor_group::add_visitor(relationship_type visit_type, workstream_visitor & visitor)
{
    if (relationship_type::unknown == visit_type) {
        return;
    }
    visitors_for_type_[visit_type] = &visitor;
}

void workstream_visitor_group::add_visitor(std::string visit_file, workstream_visitor & visitor)
{
    visitors_for_file_[visit_file] = &visitor;
}

void workstream_visitor_group::add_default_visitor(workstream_visitor & visitor)
{
    default_visitor_ = &visitor;
}

workstream_visitor * workstream_visitor_group::get_visitor(relationship_type visit_type) const
{
    std::map<relationship_type, workstream_visitor*>::const_iterator it =
                        visitors_for_type_.find(visit_type);
    if (it == visitors_for_type_.end()) {
        return (nullptr);
    } else {
        return (it->second);
    }
}

workstream_visitor * workstream_visitor_group::get_visitor(const std::string visit_file) const
{
    std::map<std::string, workstream_visitor*>::const_iterator it =
                        visitors_for_file_.find(visit_file);
    if (it == visitors_for_file_.end()) {
        return (nullptr);
    } else {
        return (it->second);
    }
}

workstream_visitor * workstream_visitor_group::get_visitor() const
{
    return (default_visitor_);
}

workstream_visitor * workstream_visitor_group::get_visitor(const std::string visit_file, relationship_type visit_type) const
{
    workstream_visitor * visitor = get_visitor(visit_file);
    if (visitor) {
        return (visitor);
    }
    visitor = get_visitor(visit_type);
    if (visitor) {
        return (visitor);
    }
    return (default_visitor_);
}

}
