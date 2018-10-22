
#include <detail/implementations/workbook_rel_visitor.hpp>
#include <xlnt/debug/debug.hpp>

namespace xlnt {
namespace detail {

#define WORKSHEET_TYPE \
    "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet"

workstream_visitor::visit_actions workbook_rel_visitor::start_element(
                    const std::string & element, std::string & newval)
{
    if (element == "Relationships" && !start_rels_) {
        start_rels_ = true;
    } else if (start_rels_ && element == "Relationship" && !start_rel_) {
        start_rel_ = true;
    }
    newval = "";
    return (SKIP);
}

void workbook_rel_visitor::end_element()
{
    if (start_rels_) {
        if (start_rel_) {
            if (rel_type_ == WORKSHEET_TYPE) {
                sheet_file_to_rid_[file_name_] = rid_;
            }
            start_rel_ = false;
        } else {
            start_rels_ = false;
        }
    }
}

workstream_visitor::visit_actions workbook_rel_visitor::start_attribute(
                    const std::string & attr, std::string & newval)
{
    if (start_rels_ && start_rel_) {
        if (attr == "Target") {
            attr_pointer_ = &file_name_;
        } else if (attr == "Id") {
            attr_pointer_ = &rid_;
        } else if (attr == "Type") {
            attr_pointer_ = &rel_type_;
        } else {
            attr_pointer_ = nullptr;
        }
    }
    newval = "";
    return (SKIP);
}

void workbook_rel_visitor::end_attribute() {
    if (start_rels_ && start_rel_) {
        attr_pointer_ = nullptr;
    }
}

workstream_visitor::visit_actions workbook_rel_visitor::character(
                    const std::string & value, std::string & newval)
{
    if (start_rels_ && start_rel_ && attr_pointer_) {
        *attr_pointer_ = value;
    }
    newval = "";
    return (SKIP);
}

const workbook_rel_visitor::SHEETS & workbook_rel_visitor::sheet_file_rid_map() const
{
    return (sheet_file_to_rid_);
}

workstream_visitor::visit_actions workbook_rel_visitor::start_ns(const std::string & ns, std::string & newval)
{
    return (SKIP);
}

}
}

