
#pragma once

#include <detail/external/include_libstudxml.hpp>
#include <detail/serialization/zstream.hpp>
#include <fstream>

namespace xlnt {

class workstream_visitor;

namespace detail {

class workstream_impl {
    std::unique_ptr<izstream> izs_;
    std::unique_ptr<std::ifstream> ifs_;
    std::unique_ptr<std::ofstream> ofs_;

public:
    workstream_impl(){}
    ~workstream_impl();
    int load(const std::string & filename);
    int visit(workstream_visitor & visitor);

//Disabled API
private:
    workstream_impl(const workstream_impl &);
    workstream_impl & operator = (const workstream_impl &);
    workstream_impl & operator = (workstream_impl);

private:
    void swap(workstream_impl & rhs);
    izstream * load_istream(const std::string & filename);
    ozstream * load_ostream(const std::string & filename);

    ////
    #if 0
        xml::parser *   parser;
    std::unique_ptr<xml::serializer> serializer_;
    #endif
};

} //namespace detail
}   //namespace xlnt 
