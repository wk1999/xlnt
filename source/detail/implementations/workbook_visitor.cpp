
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
        sheets_[sheet_.get_r_id()] = sheet_;
        sheet_.clear();
    }
}

workstream_visitor::visit_actions workbook_visitor::character(
                    const std::string & value, std::string & newval)
{
    const workstream_path_stack & stack = get_path_stack();
    if (stack == "sheets/sheet/name") {
        sheet_.set_name(value);
    } else if (stack == "sheets/sheet/id") {
        sheet_.set_r_id(value);
    } else if (stack == "sheets/sheet/sheetId") {
        sheet_.set_sheet_id(value);
    } else if (stack == "sheets/sheet/state") {
        sheet_.set_state(value);
    }
    newval = "";
    return (SKIP);
}

workstream_visitor::visit_actions workbook_visitor::start_attribute(
                    const std::string & attr UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

const workbook_visitor::SHEETS & workbook_visitor::sheets_map() const
{
    return (sheets_);
}

workstream_visitor::visit_actions workbook_visitor::start_ns(
                    const std::string & ns UNUSED, const std::string & prefix UNUSED)
{
    return (SKIP);
}

}
}

