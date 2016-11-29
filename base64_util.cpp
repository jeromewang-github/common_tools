/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file base64_util.cpp
 * @author wangyunfei01(com@baidu.com)
 * @date 2016/02/24 15:34:49
 * @brief 
 *  
 **/

#include "base64_util.h"
#include <string.h>
#include <iostream>

namespace commontools {

const char* Base64Util::_s_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                       "abcdefghijklmnopqrstuvwxyz0123456789+/";

std::vector<int> Base64Util::_s_to_int_vec = Base64Util::init_inner_data();

Base64Util::~Base64Util() {

}

/**
 * @brief Translate the bytes into Base64 String
 *
 * @author wangyunfei01
 * @date 2016/02/24 15:46:35
**/

std::string Base64Util::encode(const char* buf) {
    return encode(buf, strlen(buf));
}

std::string Base64Util::encode(const char* buf, unsigned int len) {
    std::string base64str;
    
    int mask = 0x3F;
    unsigned int pos = 0;
    while (pos < len) {
        char b0 = buf[pos++];
        char b1 = (pos < len)? buf[pos++] : 0;
        char b2 = (pos < len)? buf[pos++] : 0;
        base64str += _s_alphabet[(b0 >> 2) & mask];
        base64str += _s_alphabet[((b0 << 4) | ((b1 & 0xFF) >> 4)) & mask];
        base64str += _s_alphabet[((b1 << 2) | ((b2 & 0xFF) >> 6)) & mask];
        base64str += _s_alphabet[b2 & mask];
    }
    switch (len % 3) {
        case 1:
            base64str.at(base64str.size() - 1) = '=';
        case 2:
            base64str.at(base64str.size() - 2) = '=';
    }

    return base64str;
}

/**
 * @brief decode the Base64 string
 *
 * @author wangyunfei01
 * @date 2016/02/24 15:47:26
**/
std::string Base64Util::decode(const char* buf) {
    return decode(buf, strlen(buf));
}

std::string Base64Util::decode(const char* buf, unsigned int len) {
    std::string raw_str;
    if (buf == NULL || len < 4) {
        return raw_str;
    }

    int delta = 0;
    if (buf[len - 1] == '=') {
        delta = (buf[len -2] == '=')? 2 : 1;
    }
    unsigned int max_raw_str_len = len * 3 / 4 - delta;

    int mask = 0xFF;
    for (unsigned int i = 0; i < len; i += 4) {
        int c0 = _s_to_int_vec[(int)buf[i]];
        int c1 = _s_to_int_vec[(int)buf[i + 1]];
        raw_str += (char) (((c0 << 2) | (c1 >> 4)) & mask);
        if (raw_str.size() >= max_raw_str_len) {
            return raw_str;
        }
        int c2 = _s_to_int_vec[(int)buf[i + 2]];
        raw_str += (char) (((c1 << 4) | (c2 >> 2)) & mask);
        if (raw_str.size() >= max_raw_str_len) {
            return raw_str;
        }
        int c3 = _s_to_int_vec[(int)buf[i + 3]];
        raw_str += (char) (((c2 << 6) | c3) & mask);
    }

    return raw_str;
}

std::vector<int> Base64Util::init_inner_data() {
    std::vector<int> vec(128);

    for (size_t i = 0; i < strlen(_s_alphabet); ++i) {
        vec.at(_s_alphabet[i]) = i;
    }

    return vec;
}

} //commontools

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
