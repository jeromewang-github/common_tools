/**
 * @file src/url_util.cpp
 * @author jerome
 * @date 2017/07/27 16:36:10
 * @brief 
 *  
 **/

#include "url_util.h"
#include <string.h>
#include <ctype.h>

std::vector<UrlUtil::IgnoreItem> UrlUtil::_s_ignore_list = initialize_ignore_items();

// URL format "protocol :// hostname[:port] / path / [;parameters][?query]#fragment"
bool UrlUtil::get_site_from_url(const std::string& url, std::string* site) {
    if (site == NULL) {
        return false;
    }

    size_t start = url.find("://");
    if (start == std::string::npos) {
        return false;
    }
    start += 3;

    size_t colon_pos = url.find(':', start);
    size_t slash_pos = url.find('/', start);
    if (colon_pos != std::string::npos && colon_pos > slash_pos) {
        return false;
    }

    size_t end = (colon_pos < slash_pos) ? colon_pos : slash_pos;
    *site = url.substr(start, end - start);

    return true;
}

bool UrlUtil::is_ipv4_addr(const std::string& input) {
    const static int MAX_LEN = 15;
    const static int MIN_LEN = 7;

    size_t len = input.length();
    if (len < MIN_LEN || len > MAX_LEN || !isdigit(input[0])) {
        return false;
    }

    int dot_num = 0;
    size_t cur_pos = 1;
    int digit_len = 1;

    while (cur_pos < len) {
        if (isdigit(input[cur_pos])) {
            ++digit_len;
            if (digit_len > 3) {
                return false;
            }
        } else if (input[cur_pos] == '.') {
            if (input[cur_pos - 1] == '.') { // continuous dot mark
                return false;
            }
            digit_len = 0; // reset the length of continus digits
            ++dot_num;
        } else {
            return false;
        }
        ++cur_pos;
    }

    return (dot_num == 3);
}

bool UrlUtil::get_maindomain_from_site(const std::string& site, std::string* domain) {
    if (domain == NULL) {
        return false;
    }

    if (is_ipv4_addr(site)) {
        *domain = site;
        return true;
    }

    const char* site_ptr = site.c_str();
    const char* tail = strrchr(site_ptr, '.');
    if (tail == NULL) {
        *domain = site;
        return true;
    }

    const char* first = tail - 1;
    while (first >= site_ptr - 1) {
        if (first == site_ptr - 1 || (*first == '.')) {
            if (!ignore_url_substring(first + 1)) {
                int len = tail - first - 1;
                *domain = std::string(first + 1, len);
                return true;
            } else {
                tail = first;
            }
        }
        --first;
    }

    *domain = site;

    return true;
}

bool UrlUtil::get_maindomain_from_url(const std::string& url, std::string* domain) {
    if (domain == NULL) {
        return false;
    }

    std::string site;
    if (!get_site_from_url(url, &site)) {
        return false;
    }

    if (!get_maindomain_from_site(site, domain)) {
        return false;
    }

    return true;
}

std::vector<UrlUtil::IgnoreItem> UrlUtil::initialize_ignore_items() {
    static const IgnoreItem ignore_list[_S_IGNORE_COUNT] = {
        {"ac.", 3},
        {"ah.", 3},
        {"bj.", 3},
        {"co.", 3},
        {"com.", 4},
        {"cq.", 3},
        {"ed.", 3},
        {"edu.", 4},
        {"fj.", 3},
        {"gd.", 3},
        {"go.", 3},
        {"gov.", 4},
        {"gs.", 3},
        {"gx.", 3},
        {"gz.", 3},
        {"ha.", 3},
        {"hb.", 3},
        {"he.", 3},
        {"hi.", 3},
        {"hk.", 3},
        {"hl.", 3},
        {"hn.", 3},
        {"jl.", 3},
        {"js.", 3},
        {"jx.", 3},
        {"ln.", 3},
        {"mo.", 3},
        {"ne.", 3},
        {"net.", 4},
        {"nm.", 3},
        {"nx.", 3},
        {"or.", 3},
        {"org.", 4},
        {"pe.", 3},
        {"qh.", 3},
        {"sc.", 3},
        {"sd.", 3},
        {"sh.", 3},
        {"sn.", 3},
        {"sx.", 3},
        {"tj.", 3},
        {"tw.", 3},
        {"www.", 4},
        {"xj.", 3},
        {"xz.", 3},
        {"yn.", 3},
        {"zj.", 3}};

    return std::vector<IgnoreItem>(ignore_list, ignore_list + _S_IGNORE_COUNT);
}

bool UrlUtil::ignore_url_substring(const char* slip) {
    int head = 0;
    int tail = _S_IGNORE_COUNT - 1;
    int cur = 0;
    int ret = 0;
    while (head <= tail) {
        cur = (head + tail) / 2;
        ret = strncmp(slip, _s_ignore_list[cur].name, _s_ignore_list[cur].length);
        if (ret < 0) {
            tail = cur - 1;
        } else if (ret > 0) {
            head = cur + 1;
        } else {
            return true;
        }
    }
    return false;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
