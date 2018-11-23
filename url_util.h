/**
 * @file include/url_util.h
 * @author jerome
 * @date 2017/07/27 16:14:43
 * @brief 
 *  
 **/

#ifndef  INCLUDE_URL_UTIL_H
#define  INCLUDE_URL_UTIL_H

#include <vector>
#include <string>

class UrlUtil {
public:
    UrlUtil() {}
    ~UrlUtil() {}

    /**
     * @brief get site from vurl
     *
     * @param [in] url   : const std::string&
     * @param [out] site   : std::string*
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/07/27 19:14:39
    **/
    static bool get_site_from_url(const std::string& url, std::string* site);

    /**
     * @brief whether the parameter is a ipv4 address [0-9]{1,4}\.[0-9]{1,4}\.[0-9]{1,4}\.[0-9]{1,4}
     *
     * @param [out] input   : const std::string&
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/07/27 19:15:03
    **/
    static bool is_ipv4_addr(const std::string& input);

    /**
     * @brief get main-domain from site
     *
     * @param [in] site   : const std::string&
     * @param [out] domain   : std::string*
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/07/27 19:16:12
    **/
    static bool get_maindomain_from_site(const std::string& site, std::string* domain);

    /**
     * @brief get main-domain from url
     *
     * @param [in] url   : const std::string&
     * @param [out] domain   : std::string*
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/07/27 19:16:32
    **/
    static bool get_maindomain_from_url(const std::string& url, std::string* domain);

private:
    struct IgnoreItem {
        char name[8];
        int length;
    };

private:

    /**
     * @brief initialize the data structure used to find main-domain
     *
     * @return  std::vector<IgnoreItem> 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/07/27 19:16:51
    **/
    static std::vector<IgnoreItem> initialize_ignore_items();

    /**
     * @brief whether the slip should be skipped when searching for main-domain
     *
     * @param [in] slip   : const char*
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/07/27 19:17:34
    **/
    static bool ignore_url_substring(const char* slip);

private:
    static std::vector<IgnoreItem> _s_ignore_list;
    static const int _S_IGNORE_COUNT = 47;
};

#endif  //INCLUDE_URL_UTIL_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
