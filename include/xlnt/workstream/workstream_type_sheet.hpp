
/*
    wk 2018/10/25
*/

#pragma once

#include <string>

namespace xlnt {

class workstream_type_sheet {
    std::string name_;
    std::string sheet_id_;
    std::string state_;
    std::string r_id_;

public:
    void clear() {
        name_ = "";
        sheet_id_ = "";
        state_ = "";
        r_id_ = "";
    }

    const std::string & get_name() const {
        return (name_);
    }

    const std::string & get_sheet_id() const {
        return (sheet_id_);
    }

    const std::string & get_state() const {
        return (state_);
    }

    const std::string & get_r_id() const {
        return (r_id_);
    }

    void set_name(const std::string & name) {
        name_ = name;
    }

    void set_sheet_id(const std::string & sheet_id) {
        sheet_id_ = sheet_id;
    }

    void set_state(const std::string & state) {
        state_ = state;
    }

    void set_r_id(const std::string & id) {
        r_id_ = id;
    }
};

}
