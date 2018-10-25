
#include <detail/implementations/workbook_visitor.hpp>
#include <xlnt/workstream/workstream_path_stack.hpp>
#include <xlnt/debug/debug.hpp>

namespace xlnt {
namespace detail {

workstream_visitor::visit_actions workbook_visitor::start_element(
                    const std::string & element UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

void workbook_visitor::end_element()
{
    const workstream_path_stack & stack = get_path_stack();
    if (stack == "sheets/sheet") {
        sheet_rid_to_name_[sheet_rid_] = sheet_name_;
    }
}

workstream_visitor::visit_actions workbook_visitor::character(
                    const std::string & value, std::string & newval)
{
    const workstream_path_stack & stack = get_path_stack();
    if (stack == "sheets/sheet/name") {
        sheet_name_ = value;
    } else if (stack == "sheets/sheet/id") {
        sheet_rid_ = value;
    }
    newval = "";
    return (SKIP);
}

workstream_visitor::visit_actions workbook_visitor::start_attribute(
                    const std::string & attr UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

const workbook_visitor::SHEETS & workbook_visitor::sheet_rid_name_map() const
{
    return (sheet_rid_to_name_);
}

workstream_visitor::visit_actions workbook_visitor::start_ns(
                    const std::string & ns UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

}
}

