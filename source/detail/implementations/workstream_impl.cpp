
#include <xlnt/utils/path.hpp>
#include <detail/implementations/workstream_impl.hpp>
#include <xlnt/workstream/workstream_visitor.hpp>
#include <xlnt/workstream/workstream_visitor_group.hpp>
#include <detail/implementations/workbook_visitor.hpp>
#include <detail/implementations/workbook_rel_visitor.hpp>
#include <xlnt/utils/exceptions.hpp>
#include <detail/serialization/open_stream.hpp>
#include "xlnt/debug/debug.hpp"

#include <sstream>

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

int workstream_impl::visit(workstream_visitor_group & visitors)
{
    std::unique_ptr<ozstream> ozs;
    std::stringbuf tmp;
    std::ostream os(&tmp);

    // load tmp ostream
    ozs.reset(new ozstream(os));

    // do visit
    workbook_visitor    wb_visitor;
    visit_part("xl/workbook.xml", ozs, wb_visitor);
    const workbook_visitor::SHEETS & sheets = wb_visitor.sheet_rid_name_map();

    // do visit
    workbook_rel_visitor    wb_rel_visitor;
    visit_part("xl/_rels/workbook.xml.rels", ozs, wb_rel_visitor);
    const workbook_rel_visitor::SHEETS & rels = wb_rel_visitor.sheet_file_rid_map();

    // setup sheet table
    std::string sheet_name;
    for (auto it : rels) {
        auto sheet = sheets.find(it.second);
        if (sheet != sheets.end()) {
            sheet_name = sheet->second;
        } else {
            sheet_name = "";
        }
        partname_to_sheetname_[std::string("xl/") + it.first] = sheet_name;
    }

    ozs.reset(load_ostream(visitors.getname()));
    // visit all part
    std::vector<path> files = izs_->files();
    int visit_type = workstream_visitor_group::default_type;
    for (auto part : files) {
        auto part_string = part.string();
        auto visit_name = part_string;
        auto type = get_part_type(part_string);
        if (part_type_sheet == type) {
            visit_type = workstream_visitor_group::worksheet;
            visit_name = partname_to_sheetname_[part_string];
        }
        workstream_visitor * visitor = visitors.get_visitor(visit_type);
        if (visitor) {
            visitor->before_visit(visit_name);
            visit_part(part_string, ozs, *visitor);
            visitor->after_visit(visit_name);
        }
    }
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

void workstream_impl::visit_part(const std::string & partname, std::unique_ptr<ozstream> & ozs,
                                workstream_visitor & visitor)
{
    path filepath(partname);
    auto content_types_streambuf = izs_->open(filepath);
    std::istream content_types_stream(content_types_streambuf.get());
    xml::parser p(content_types_stream, filepath.string(),
                        xml::parser::receive_default
                        |xml::parser::receive_attributes_event
                        |xml::parser::receive_namespace_decls);

    auto current_part_streambuf_ = ozs->open(filepath);
    std::ostream current_part_stream(current_part_streambuf_.get());
    xml::serializer s(current_part_stream, filepath.string(), 0);

    s.xml_decl("1.0", "UTF-8", "yes");

    std::string newval;
    for (xml::parser::event_type e: p) {
        switch  (e) {
            case xml::parser::start_element:
            {
                workstream_visitor::visit_actions act = visitor.start_element(p.qname().name(), newval);
                if (workstream_visitor::WRITE == act) {
                    s.start_element(p.qname());
                } else if (workstream_visitor::REPLACE == act) {
                    s.start_element(p.qname().namespace_(), newval);
                } else if (workstream_visitor::SKIP == act) {
                    skip_element_++;
                } else {
                    throw xlnt::exception("invalid visitor actions");
                }
                break;
            }
            case xml::parser::end_element:
            {
                if (skip_element_) {
                    skip_element_--;
                } else {
                    s.end_element();
                }
                visitor.end_element();
                break;
            }
            case xml::parser::start_attribute:
            {
                workstream_visitor::visit_actions act = visitor.start_attribute(p.qname().name(), newval);
                if (skip_element_) {
                    break;
                }
                if (workstream_visitor::WRITE == act) {
                    s.start_attribute(p.qname());
                } else if (workstream_visitor::REPLACE == act) {
                    s.start_attribute(p.qname().namespace_(), newval);
                } else if (workstream_visitor::SKIP == act) {
                    skip_attribute_++;
                } else {
                    throw xlnt::exception("invalid visitor actions");
                }
                break;
            }
            case xml::parser::end_attribute:
            {
                if (skip_element_) {
                } else if (skip_attribute_) {
                    skip_attribute_--;
                } else {
                    s.end_attribute();
                }
                visitor.end_attribute();
                break;
            }
            case xml::parser::characters:
            {
                workstream_visitor::visit_actions act = visitor.character(p.value (), newval);
                if (skip_attribute_ || skip_element_) {
                    break;
                }
                if (workstream_visitor::WRITE == act) {
                    s.characters (p.value ());
                } else if (workstream_visitor::REPLACE == act) {
                    s.characters (newval);
                } else {
                    throw xlnt::exception("invalid visitor actions");
                }
                break;
            }
            case xml::parser::start_namespace_decl:
            {
                workstream_visitor::visit_actions act = visitor.start_ns(p.namespace_ (), newval);
                if (workstream_visitor::WRITE == act) {
                    s.namespace_decl (p.namespace_ (), p.prefix ());
                } else if (workstream_visitor::REPLACE == act) {
                    s.namespace_decl (newval, p.prefix ());
                } else if (workstream_visitor::SKIP == act) {
                } else {
                    throw xlnt::exception("invalid visitor actions");
                }
                
                break;
            }
            case xml::parser::end_namespace_decl:
            {
                break;
            }
            default:
            {
                throw xlnt::exception("invalid parser event");
            }
        }
    }
}

int workstream_impl::get_part_type(const std::string & partname) const
{
    auto it = partname_to_sheetname_.find(partname);

    if (it == partname_to_sheetname_.end()) {
        return (part_type_other);
    } else {
        return (part_type_sheet);
    }
}

}
}   //namespace xlnt
