/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file base64tool.cpp
 * @author wangyunfei01(com@baidu.com)
 * @date 2016/11/29 23:25:09
 * @brief 
 *  
 **/

#include <unistd.h>
#include <iostream>
#include "base64_util.h"

void help(const char* exe_file) {
    std::cout <<"Usage:" << exe_file << " option[-d|-e] string1 string2..." << std::endl;
    std::cout <<"Example:" << exe_file << " -e 123 1234" << std::endl;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        help(argv[0]);
        return 1;
    }

    bool operation = -1;
    int opt;
    while ((opt = getopt(argc, argv, "de")) != -1) {
        switch (opt) {
            case 'd':
                operation = 0; //decode
                break;
            case 'e':
                operation = 1; //encode
                break;
            default:
                help(argv[0]);
                return 1;
        }

        if (operation == 0 || operation == 1) {
            break;
        }
    }

    if (operation == 0) {
        for (int i = 2; i < argc; ++i) {
            std::cout << argv[i] << '\t' << commontools::Base64Util::decode(argv[i]) << std::endl;
        }
    } else if (operation == 1) {
        for (int i = 2; i < argc; ++i) {
            std::cout << argv[i] << '\t' << commontools::Base64Util::encode(argv[i]) << std::endl;
        }
    }
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
