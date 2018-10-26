
#include <detail/serialization/custom_value_traits.hpp>
#include <detail/implementations/workbook_rel_visitor.hpp>
#include <xlnt/workstream/workstream_path_stack.hpp>
#include <xlnt/debug/debug.hpp>

namespace xlnt {
namespace detail {

workstream_visitor::visit_actions workbook_rel_visitor::start_element(
                    const std::string & element UNUSED, std::string & newval UNUSED)
{
    return (SKIP);
}

void workbook_rel_visitor::end_element()
{
    const workstream_path_stack & stack = get_path_stack();
    if (stack == "Relationships/Relationship") {
        rels_[rel_.file_name] = rel_;
        rel_.file_name = "";
        rel_.r_id = "";
        rel_.r_type = relationship_type::unknown;
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
        rel_.file_name = std::string("xl/") + value;
    } else if (stack == "Relationships/Relationship/Id") {
        rel_.r_id = value;
    } else if (stack == "Relationships/Relationship/Type") {
        rel_.r_type = from_string<relationship_type>(value);
    }
    newval = "";
    return (SKIP);
}

bool  workbook_rel_visitor::get_file_relationship(const std::string filename,
                                    std::string & r_id, relationship_type & type) const
{
    FILE_RELS::const_iterator it = rels_.find(filename);
    if (it == rels_.end()) {
        return (false);
    }
    r_id = it->second.r_id;
    type = it->second.r_type;
    return (true);
}

workstream_visitor::visit_actions workbook_rel_visitor::start_ns(
                    const std::string & ns UNUSED, const std::string & prefix UNUSED)
{
    return (SKIP);
}

}
}

