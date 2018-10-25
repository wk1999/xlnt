
#include <detail/implementations/workbook_rel_visitor.hpp>
#include <xlnt/workstream/workstream_path_stack.hpp>
#include <xlnt/debug/debug.hpp>

namespace xlnt {
namespace detail {

#define WORKSHEET_TYPE \
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet"

workstream_visitor::visit_actions workbook_rel_visitor::start_element(
                    const std::string & element UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

void workbook_rel_visitor::end_element()
{
    const workstream_path_stack & stack = get_path_stack();
    if (stack == "Relationships/Relationship" &&
        rel_type_ == WORKSHEET_TYPE) {
        sheet_file_to_rid_[file_name_] = rid_;
    }
}

workstream_visitor::visit_actions workbook_rel_visitor::start_attribute(
                    const std::string & attr UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

workstream_visitor::visit_actions workbook_rel_visitor::character(
                    const std::string & value, std::string & newval)
{
    const workstream_path_stack & stack = get_path_stack();
    if (stack == "Relationships/Relationship/Target") {
        file_name_ = value;
    } else if (stack == "Relationships/Relationship/Id") {
        rid_ = value;
    } else if (stack == "Relationships/Relationship/Type") {
        rel_type_ = value;
    }
    newval = "";
    return (SKIP);
}

const workbook_rel_visitor::SHEETS & workbook_rel_visitor::sheet_file_rid_map() const
{
    return (sheet_file_to_rid_);
}

workstream_visitor::visit_actions workbook_rel_visitor::start_ns(
                    const std::string & ns UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

}
}

