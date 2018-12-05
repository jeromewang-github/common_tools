#include "regex_dict.h"
#include <fstream>

pthread_rwlock_t RegexDict::_s_dict_lock = PTHREAD_RWLOCK_INITIALIZER;

RegexDict::RegexDict() : _pcre_dict(NULL) {
    _pcre_dict = NULL;
}

RegexDict::~RegexDict() {
    destroy_dict();
}

bool RegexDict::load_dict(const std::string& dict_file) {
    _dict_file = dict_file;
    if (_pcre_dict != NULL) {
        destroy_dict();
    }

    std::ifstream in(_dict_file.c_str());
    if (!in) {
        fprintf(stderr, "Open regex-dict file [%s] failed.\n", _dict_file.c_str());
        return false;
    }
    
    int patt_cnt = 0;
    bool first = true;
    std::string pcre_pattern = "";
    std::string line;
    while (in >> line) {
        if (line.empty() || line[0] == '#') { // 注释行
            continue;
        }

        ++patt_cnt;
        if (first) {
            first = false;
            pcre_pattern = "(" + line;
        } else {
            pcre_pattern += "|" + line;
        }
    }
    if (!first) {
        pcre_pattern += ")";
    }
    in.close();

    if (!pcre_pattern.empty()) {
        pthread_rwlock_wrlock(&_s_dict_lock);
        const char *error = NULL;
        int erroffset = -1;
        _pcre_dict = pcre_compile(pcre_pattern.c_str(), 0, &error, &erroffset, NULL);
        pthread_rwlock_unlock(&_s_dict_lock);   
        if (!_pcre_dict) {
            fprintf(stderr, "Complile pcre pattern [%s] failed.\n", pcre_pattern.c_str());
            return false;
        }
    }
    
    return true;
}

void RegexDict::destroy_dict() {
    pthread_rwlock_wrlock(&_s_dict_lock);
    if (_pcre_dict) {
        pcre_free(_pcre_dict);
        _pcre_dict = NULL; 
    } 
    pthread_rwlock_unlock(&_s_dict_lock);
}

bool RegexDict::seek_dict(const char* url) {
    if (!url) {
        return false;
    }
    int url_len = strlen(url);
    bool hit_dict = false;
    pthread_rwlock_rdlock(&_s_dict_lock);
    if (_pcre_dict != NULL) {
        if (pcre_exec(_pcre_dict, NULL, url, url_len, 0, 0, NULL, 0) >= 0) {
            hit_dict = true;
        }
    }
    pthread_rwlock_unlock(&_s_dict_lock);
    return hit_dict;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
