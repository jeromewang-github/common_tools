/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file base64_util.h
 * @author wangyunfei01(com@baidu.com)
 * @date 2016/02/24 15:08:33
 * @brief Base64编解码
 *  
 **/

#ifndef  COMMON_TOOLS_BASE64_UTIL_H
#define  COMMON_TOOLS_BASE64_UTIL_H

#include <string>
#include <vector>

namespace commontools {

class Base64Util {
    public:
        explicit Base64Util() {};
        ~Base64Util();

        /**
         * @brief 将字符串用Base64进行编码
         *
         * @param [in] buf   : const char*
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author wangyunfei01
         * @date 2016/02/24 20:15:06
        **/
        static std::string encode(const char* buf);

        /**
         * @brief 对指定长度的字符数组进行Base64编码
         *
         * @param [in] buf   : const char*
         * @param [in] len   : unsigned int
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author wangyunfei01
         * @date 2016/06/07 11:09:26
        **/
        static std::string encode(const char* buf, unsigned int len);

        /**
         * @brief 将Base64编码的字符串进行解码
         *
         * @param [in] buf   : const char*
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author wangyunfei01
         * @date 2016/02/24 20:15:34
        **/
        static std::string decode(const char* buf);

        /**
         * @brief 对指定长度的字符数组进行Base64解码
         *
         * @param [in] buf   : const char*
         * @param [in] len   : unsigned int
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author wangyunfei01
         * @date 2016/06/07 11:10:32
        **/
        static std::string decode(const char* buf, unsigned int len);
    
    private:
        Base64Util(const Base64Util&);
        Base64Util& operator = (const Base64Util&);

        /**
         * @brief 初始化Base64编解码所需的内部辅助数据
         *
         * @return  std::vector<int>
         * @retval   
         * @see 
         * @note 
         * @author wangyunfei01
         * @date 2016/02/24 20:16:07
        **/
        static std::vector<int> init_inner_data();

    private:
        static const char* _s_alphabet;//Base64编解码的码表
        static std::vector<int> _s_to_int_vec;
};

} //commontools

#endif  //COMMON_TOOLS_BASE64_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
