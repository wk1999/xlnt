
#pragma once

#include <vector>
#include <string>
#include <memory>

namespace xlnt {

class workstream_path_stack {
    std::vector<std::string> _stack;

    mutable std::unique_ptr<workstream_path_stack> _parent;

public:
    workstream_path_stack & push(const std::string & val);

    workstream_path_stack & pop();

    bool empty() const;

    void clear();

    std::size_t size() const;

    bool operator==(const std::string & path) const;

    bool operator!=(const std::string & path) const;

    std::string string() const;

    const workstream_path_stack & parent() const;
};

} //namespace
