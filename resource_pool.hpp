/**
 * @file resource_pool.hpp
 * @author jerome
 * @date 2017/04/21 11:15:01
 * @brief 
 *  
 **/

#ifndef  INCLUDE_RESOURCE_POOL_H
#define  INCLUDE_RESOURCE_POOL_H

#include <deque>
#include <vector>

template <typename T>
class ResourcePool {
public:
    ResourcePool();
    ResourcePool(int block_sz);
    ~ResourcePool();
    T* acquire_resource();
    void release_resource(T* resource);
    void reset();

private:
    bool allocate_resource_block();
    ResourcePool(const ResourcePool<T>& copy);
    ResourcePool<T>& operator=(const ResourcePool<T>& copy);

private:
    std::vector<T*> _block_resource;
    std::deque<T*> _free_resource;
    int _block_size;
    static const int DEFAULT_BLOCK_SIZE = 15;
}; //class ResourcePool

template <typename T>
ResourcePool<T>::ResourcePool() : _block_size(DEFAULT_BLOCK_SIZE) {
}

template <typename T>
ResourcePool<T>::ResourcePool(int block_sz) : _block_size(block_sz) {
}

template <typename T>
ResourcePool<T>::~ResourcePool() {
    typename std::vector<T*>::iterator it;

    for (it = _block_resource.begin(); it != _block_resource.end(); ++it) {
        delete [](*it);
    }
}

template <typename T>
T* ResourcePool<T>::acquire_resource() {
    if (_free_resource.empty()) {
        if (!allocate_resource_block()) {
            return NULL;
        }
    }

    T* resource = _free_resource.front();
    _free_resource.pop_front();

    return resource;
}

template <typename T>
void ResourcePool<T>::release_resource(T* resource) {
    _free_resource.push_back(resource);
}

template <typename T>
void ResourcePool<T>::reset() {
    _free_resource.clear();

    typename std::vector<T*>::iterator it;
    for (it = _block_resource.begin(); it != _block_resource.end(); ++it) {
        T* block = *it;
        for (int i = 0; i < _block_size; ++i) {
            _free_resource.push_back(block + i);
        }
    }
}

template <typename T>
bool ResourcePool<T>::allocate_resource_block() {
    T* block = new(std::nothrow) T[_block_size];
    if (block == NULL) {
        return false;
    }

    _block_resource.push_back(block);
    for (int i = 0; i < _block_size; ++i) {
        _free_resource.push_back(block + i);
    }

    return true;
}

#endif  //INCLUDE_RESOURCE_POOL_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
