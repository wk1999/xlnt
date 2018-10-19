
/*
    wk 2018/10/18
*/

#pragma once

#include <string>
#include <memory>

namespace xlnt {

class workstream_visitor;

namespace detail {
class workstream_impl;
}

class workstream {
public:
    workstream();
    ~workstream();

private:
    workstream(const workstream & rhs);
    workstream operator=(workstream rhs);

public:
    int load(const std::string & xlsx_file);
    int visit(workstream_visitor & xlsx_visitor);

private:
    void swap(workstream rhs);

private:
    std::unique_ptr<detail::workstream_impl> d_;
};  //class xlsxstream

}   //namespace xlnt
