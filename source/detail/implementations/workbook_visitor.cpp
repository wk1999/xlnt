
#include <detail/implementations/workbook_visitor.hpp>
#include <xlnt/debug/debug.hpp>

namespace xlnt {
namespace detail {

workstream_visitor::visit_actions workbook_visitor::start_element(
                    const std::string & element, std::string & newval)
{
    if (element == "sheets" && !start_sheets_) {
        start_sheets_ = true;
    } else if (start_sheets_ && element == "sheet" && !start_sheet_) {
        start_sheet_ = true;
    }
    newval = "";
    return (SKIP);
}

void workbook_visitor::end_element()
{
    if (start_sheets_) {
        if (start_sheet_) {
            sheet_rid_to_name_[sheet_rid_] = sheet_name_;
            start_sheet_ = false;
        } else {
            start_sheets_ = false;
        }
    }
}

workstream_visitor::visit_actions workbook_visitor::start_attribute(
                    const std::string & attr, std::string & newval)
{
    if (start_sheets_ && start_sheet_) {
        if (attr == "name") {
            attr_pointer_ = &sheet_name_;
        } else if (attr == "id") {
            attr_pointer_ = &sheet_rid_;
        } else {
            attr_pointer_ = nullptr;
        }
    }
    newval = "";
    return (SKIP);
}

void workbook_visitor::end_attribute() {
    if (start_sheets_ && start_sheet_) {
        attr_pointer_ = nullptr;
    }
}

workstream_visitor::visit_actions workbook_visitor::character(
                    const std::string & value, std::string & newval)
{
    if (start_sheets_ && start_sheet_ && attr_pointer_) {
        *attr_pointer_ = value;
    }
    newval = "";
    return (SKIP);
}

const workbook_visitor::SHEETS & workbook_visitor::sheet_rid_name_map() const
{
    return (sheet_rid_to_name_);
}

workstream_visitor::visit_actions workbook_visitor::start_ns(const std::string & ns, std::string & newval)
{
    return (SKIP);
}

}
}

