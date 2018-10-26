
#pragma once

#include <string>
#include <map>
#include <xlnt/workstream/workstream_visitor.hpp>
#include <xlnt/packaging/relationship.hpp>

namespace xlnt {
namespace detail {

class workbook_rel_visitor : public workstream_visitor {
    struct relationship {
        std::string         file_name;
        std::string         r_id;
        relationship_type   r_type;
        relationship():r_type(relationship_type::unknown){}
    };
    // fle name to relation ship
    typedef std::map<std::string, relationship> FILE_RELS;
    FILE_RELS       rels_;
    relationship    rel_;

public:
    virtual ~workbook_rel_visitor(){}

    virtual visit_actions start_element(const std::string & element, std::string & newval);

    virtual void end_element();

    virtual visit_actions start_attribute(const std::string & attr, std::string & newval);

    virtual visit_actions character(const std::string & value, std::string & newval);

    virtual visit_actions start_ns(const std::string & ns, const std::string & prefix);

    bool  get_file_relationship(const std::string filename,
                                    std::string & r_id, relationship_type & type) const;
};

}
}

