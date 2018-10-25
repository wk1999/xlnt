
#pragma once

#include <vector>
#include <string>

namespace xlnt {

class workstream_path_stack {
    std::vector<std::string> _stack;

public:
    workstream_path_stack & push(const std::string & val);

    workstream_path_stack & pop();

    bool empty() const;

    void clear();

    std::size_t size() const;

    bool operator==(const std::string & path) const;

    bool operator!=(const std::string & path) const;

    std::string string() const;
};

} //namespace
