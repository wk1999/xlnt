
#pragma once

#include <string>
#include <map>
#include <xlnt/workstream/workstream_visitor.hpp>
#include <xlnt/workstream/workstream_type_sheet.hpp>

namespace xlnt {
namespace detail {

class workbook_visitor : public workstream_visitor {
public:
    // r:id is the key
    typedef std::map<std::string, workstream_type_sheet> SHEETS;

private:
    SHEETS  sheets_;
    workstream_type_sheet   sheet_;

public:
    virtual visit_actions start_element(const std::string & element, std::string & newval);
    virtual void end_element();
    virtual visit_actions start_attribute(const std::string & attr, std::string & newval);
    virtual visit_actions character(const std::string & value, std::string & newval);
    virtual visit_actions start_ns(const std::string & ns, std::string & newval);
    const SHEETS & sheets_map() const;
};

}
}
