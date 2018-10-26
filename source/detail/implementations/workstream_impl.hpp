
#pragma once

#include <detail/external/include_libstudxml.hpp>
#include <detail/serialization/zstream.hpp>
#include <xlnt/workstream/workstream_path_stack.hpp>
#include <fstream>
#include <map>
#include <string>
#include <memory>

namespace xlnt {

class workstream_visitor;
class workstream_visitor_group;

namespace detail {

class workstream_impl {
    std::unique_ptr<izstream> izs_;
    std::unique_ptr<std::ifstream> ifs_;
    std::unique_ptr<std::ofstream> ofs_;
    workstream_path_stack   stack_;

    std::map<std::string, std::string> partname_to_sheetname_;

    const int part_type_sheet = 1;
    const int part_type_other = 2;

    int skip_element_;
    int skip_attribute_;

public:
    workstream_impl():skip_element_(0),skip_attribute_(0){}
    ~workstream_impl();
    int load(const std::string & filename);
    int visit(workstream_visitor_group & visitors);

//Disabled API
private:
    workstream_impl(const workstream_impl &);
    workstream_impl & operator = (const workstream_impl &);
    workstream_impl & operator = (workstream_impl);

private:
    void swap(workstream_impl & rhs);
    izstream * load_istream(const std::string & filename);
    ozstream * load_ostream(const std::string & filename);
    void visit_part(const std::string & partname, std::unique_ptr<ozstream> & ozs, workstream_visitor & visitor);
};

} //namespace detail
}   //namespace xlnt 
