#include <stdlib.h>
#include <string>
#include <iostream>
#include "regex_dict.h"

static std::vector<std::string> split(const std::string& input_str, char delimiter) {
    std::vector<std::string> ret;
    size_t pre = 0;
    size_t cur = 0;
    size_t len = input_str.length();
    while (cur < len) {
        if (input_str[cur] == delimiter) {
            if (pre < cur) {
                ret.push_back(input_str.substr(pre, cur - pre));
            }
            cur += 1;
            pre = cur;
        } else {
            cur += 1;
        }
    }

    if (pre < cur) {
        ret.push_back(input_str.substr(pre));
    }

    return ret;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
            << " filter.dict parsed_column(started from 0) used_as(0-blacklist/1-whitelist)" << std::endl;
        return 1;
    }
    
    const char* dict_path = argv[1];
    int column = atoi(argv[2]);
    bool is_whitelist = (atoi(argv[3]) != 0);

    baidu::spider::videomimoadaptor::RegexDict reg_dict;
    if (!reg_dict.load_dict(dict_path)) {
        std::cerr << "failed to load dict " << dict_path << std::endl;
        return 1;
    }

    std::string record;
    while (getline(std::cin, record)) {
        std::vector<std::string> fields = split(record, '\t');
        if (fields.size() <= column) {
            std::cerr << "skip invalid record " << record << std::endl;
            continue;
        }

        std::string field_val = fields[column];
        if (is_whitelist) {
            if (reg_dict.seek_dict(field_val.c_str())) {
                std::cout << record << std::endl;
            }
        } else {
            if (!reg_dict.seek_dict(field_val.c_str())) {
                std::cout << record << std::endl;
            }
        }
    }

    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
