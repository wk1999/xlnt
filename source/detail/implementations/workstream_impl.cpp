
#include <xlnt/utils/path.hpp>
#include <detail/implementations/workstream_impl.hpp>
#include <xlnt/workstream/workstream_visitor.hpp>
#include <xlnt/utils/exceptions.hpp>
#include <detail/serialization/open_stream.hpp>

namespace xlnt {
namespace detail {

int workstream_impl::load(const std::string & filename)
{
    if (izs_) {
        workstream_impl other;
        other.load(filename);
        swap(other);
    } else {
        izs_.reset(load_istream(filename));
    }

    return (0);
}

int workstream_impl::visit(workstream_visitor & visitor)
{
    std::unique_ptr<ozstream> ozs;

    // load ostream
    ozs.reset(load_ostream(visitor.getname()));

    // do visit
    visitor.dosome();
    return (0);
}

void workstream_impl::swap(workstream_impl & rhs)
{
    std::swap(izs_, rhs.izs_);
}

workstream_impl::~workstream_impl()
{
}

izstream * workstream_impl::load_istream(const std::string & filename)
{
    std::ifstream * file_stream = new std::ifstream;
    ifs_.reset(file_stream);
    std::string  pathname = path(filename).string();
    open_stream(*file_stream, pathname);

    if (!file_stream->good())
    {
        throw xlnt::exception("file not found " + pathname);
    }

    return (new izstream(*file_stream));
}

ozstream * workstream_impl::load_ostream(const std::string & filename)
{
    std::ofstream * file_stream = new std::ofstream;
    ofs_.reset(file_stream);
    std::string  pathname = path(filename).string();
    open_stream(*file_stream, pathname);

    return (new ozstream(*file_stream));
}

}
}   //namespace xlnt
