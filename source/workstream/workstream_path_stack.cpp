
#include <xlnt/workstream/workstream_path_stack.hpp>

namespace xlnt {

workstream_path_stack & workstream_path_stack::push(const std::string & val) {
    _stack.push_back(val);
    return (*this);
}

workstream_path_stack & workstream_path_stack::pop() {
    _stack.pop_back();
    return (*this);
}

bool workstream_path_stack::empty() const {
    return (_stack.empty());
}

void workstream_path_stack::clear() {
    _stack.clear();
}

std::size_t workstream_path_stack::size() const {
    return (_stack.size());
}

bool workstream_path_stack::operator!=(const std::string & path) const {
    return !(operator==(path));
}

bool workstream_path_stack::operator==(const std::string & path) const {
    std::size_t size = _stack.size();
    if (0 == size) {
        return (false);
    }

    // first time
    std::string back(_stack.back());
    if (back == path) {
        return (true);
    }
    if (back.size() >= path.size()) {
        return (false);
    }

    // middle time
    for (std::size_t i = size-1; i > 0; i--) {
        back = _stack[i-1] + "/" + back;
        if (back == path) {
            return (true);
        }
        if (back.size() >= path.size()) {
            return (false);
        }
    }

    // last time
    back = std::string("/") + back;
    if (back == path) {
        return (true);
    }

    return (false);
}

std::string workstream_path_stack::string() const {
    std::string a;
    for (std::size_t i = 0; i < _stack.size(); i++) {
        a += "/" + _stack[i];
    }

    return (a);
}

}
