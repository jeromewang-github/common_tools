/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file include/union_find_set.h
 * @author jerome(com@baidu.com)
 * @date 2017/10/19 11:20:48
 * @brief 
 *  
 **/

#ifndef  __INCLUDE_UNION_FIND_SET_H_
#define  __INCLUDE_UNION_FIND_SET_H_

#include <stddef.h> // size_t
class UnionFindSet {
private:
    struct InternalNode {
        size_t parent;
        size_t rank;
    };

public:
    /**
     * @brief constructor of UnionFindSet
     *
     * @param [in] num   : size_t, number of all the items
     * @return 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/10/19 13:50:27
    **/
    explicit UnionFindSet(size_t num);
    virtual ~UnionFindSet();

    /**
     * @brief 初始化并查集的相关数据结构
     *
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2018/11/23 17:08:48
    **/
    bool init();

    /**
     * @brief get the index of parent
     *
     * @param [in] index   : size_t
     * @return  size_t 
     * @retval  returns -1 if the index exceeds the maximum index
     * @see 
     * @note 
     * @author jerome
     * @date 2017/10/19 13:46:45
    **/
    size_t get_parent(size_t index) const;

    /**
     * @brief merge two items
     *
     * @param [in] index1   : size_t
     * @param [in] index2   : size_t
     * @return  void 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/10/19 13:47:59
    **/
    void merge(size_t index1, size_t index2);

    /**
     * @brief check whether two items is connected
     *
     * @param [in] index1   : size_t
     * @param [in] index2   : size_t
     * @return  bool 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/10/19 13:48:25
    **/
    bool is_connected(size_t index1, size_t index2) const;

    /**
     * @brief get the number of disjoint sets
     *
     * @return  size_t 
     * @retval   
     * @see 
     * @note 
     * @author jerome
     * @date 2017/10/19 13:49:02
    **/
    size_t get_disjoint_num() const;

private:
    UnionFindSet(const UnionFindSet&);
    UnionFindSet& operator= (const UnionFindSet&);

private:
    InternalNode* _nodes_array; // array storing the state of each item
    size_t _nodes_num; // number of items
    size_t _disjoint_num; // number of disjoint-set
}; // class UnionFindSet

#endif  //__INCLUDE_UNION_FIND_SET_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
