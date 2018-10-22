
#pragma once

#include <string>
#include <map>
#include <xlnt/workstream/workstream_visitor.hpp>

namespace xlnt {
namespace detail {

class workbook_rel_visitor : public workstream_visitor {
    std::map<std::string, std::string>  sheet_file_to_rid_;
    bool start_rels_;
    bool start_rel_;
    std::string rel_type_;
    std::string file_name_;
    std::string rid_;
    std::string * attr_pointer_;

public:
    typedef std::map<std::string, std::string> SHEETS;

public:
    workbook_rel_visitor():
            start_rels_(false), start_rel_(false), attr_pointer_(nullptr){}
    virtual visit_actions start_element(const std::string & element, std::string & newval);
    virtual void end_element();
    virtual visit_actions start_attribute(const std::string & attr, std::string & newval);
    virtual void end_attribute();
    virtual visit_actions character(const std::string & value, std::string & newval);
    virtual visit_actions start_ns(const std::string & ns, std::string & newval);
    const SHEETS & sheet_file_rid_map() const;
};

}
}

