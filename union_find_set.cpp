/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file src/union_find_set.cpp
 * @author jerome(com@baidu.com)
 * @date 2017/10/19 12:15:06
 * @brief 
 *  
 **/

#include "union_find_set.h"

UnionFindSet::UnionFindSet(size_t num) : 
        _nodes_array(NULL),
        _nodes_num(num),
        _disjoint_num(num) {
    init();
}

UnionFindSet::~UnionFindSet() {
    delete[] _nodes_array;
}

bool UnionFindSet::init() {
    _nodes_array = new(std::nothrow) InternalNode[_nodes_num];
    if (_nodes_array == NULL) {
        return false;
    }
    for (size_t sz = 0; sz < _nodes_num; ++sz) {
        _nodes_array[sz].parent = sz;
        _nodes_array[sz].rank = 0;
    }

    return true;
}

size_t UnionFindSet::get_parent(size_t index) const {
    if (index >= _nodes_num) {
        return -1;
    }
    size_t ret = index;
    while (_nodes_array[ret].parent != ret) {
        ret = _nodes_array[ret].parent;
    }

    // path compression
    size_t p_val = 0;
    while (_nodes_array[index].parent != ret) {
        p_val = _nodes_array[index].parent; // stores its parent
        _nodes_array[index].parent = ret; // change its parent to root directly
        index = p_val; // move to its previous parent
    }

    return ret;
}

void UnionFindSet::merge(size_t index1, size_t index2) {
    size_t ret1 = get_parent(index1);
    size_t ret2 = get_parent(index2);
    if (ret1 == ret2 || ret1 == size_t(-1) || ret2 == size_t(-1)) {
        return;
    }
    if (_nodes_array[ret1].rank < _nodes_array[ret2].rank) {
        _nodes_array[ret1].parent = ret2;
    } else if (_nodes_array[ret1].rank > _nodes_array[ret2].rank) {
        _nodes_array[ret2].parent = ret1;
    } else {
        _nodes_array[ret1].parent = ret2;
        ++_nodes_array[ret1].rank;
    }
    --_disjoint_num;
}

bool UnionFindSet::is_connected(size_t index1, size_t index2) const {
    size_t ret1 = get_parent(index1);
    size_t ret2 = get_parent(index2);
    return (ret1 == ret2 && ret1 != size_t(-1));
}

size_t UnionFindSet::get_disjoint_num() const {
    return _disjoint_num;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
