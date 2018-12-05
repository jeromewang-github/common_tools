#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include "pthread.h"
#include "pcre.h"

#ifndef  REGEX_DICT_H
#define  REGEX_DICT_H

class RegexDict {
public:
    RegexDict();
    ~RegexDict();
    /**
     * @brief 从正则表达式文件列表中加载词典
     *
     * @param [in] dict_file   : const std::string&
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2018/07/17 18:32:11
    **/
    bool load_dict(const std::string& dict_file);

    /**
     * @brief 在正则表达式词典中搜索url是否命中某条pattern
     *
     * @param [in] url   : const char*
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2018/07/17 18:32:34
    **/
    bool seek_dict(const char* url);

private:
    bool create_dict();
    void destroy_dict();

private:
    static pthread_rwlock_t _s_dict_lock;
    std::string _dict_file;
    pcre* _pcre_dict;
};

#endif

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
