
/*
    wk 2018/10/18
*/

#include <xlnt/workstream/workstream.hpp>
#include <detail/implementations/workstream_impl.hpp>

namespace xlnt {

workstream::workstream():d_(new detail::workstream_impl)
{
}

workstream::~workstream() = default;

int workstream::load(const std::string & xlsx_file)
{
    return (d_->load(xlsx_file));
}

int workstream::visit(workstream_visitor & xlsx_visitor)
{
    return (d_->visit(xlsx_visitor));
}

}

