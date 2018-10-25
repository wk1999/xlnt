
#pragma once

#include <string>
#include <map>
#include <xlnt/workstream/workstream_visitor.hpp>

namespace xlnt {
namespace detail {

class workbook_visitor : public workstream_visitor {
    std::map<std::string, std::string>  sheet_rid_to_name_;
    std::string sheet_name_;
    std::string sheet_rid_;

public:
    typedef std::map<std::string, std::string> SHEETS;

public:
    virtual visit_actions start_element(const std::string & element, std::string & newval);
    virtual void end_element();
    virtual visit_actions start_attribute(const std::string & attr, std::string & newval);
    virtual visit_actions character(const std::string & value, std::string & newval);
    virtual visit_actions start_ns(const std::string & ns, std::string & newval);
    const SHEETS & sheet_rid_name_map() const;
};

}
}
