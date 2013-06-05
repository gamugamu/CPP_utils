//
//  File.h
//  TestinC++
//
//  Created by Abadie, Loïc on 05/06/13.
//  Copyright (c) 2013 Abadie, Loïc. All rights reserved.
//

#ifndef __TestinC____File__
#define __TestinC____File__

#include <iostream>

template <typename T>
class Deleter {
public:
    Deleter(T* pointer) : pointer_(pointer) { }
    Deleter(const Deleter& deleter) {
        Deleter* d = const_cast<Deleter*>(&deleter);
        pointer_ = d->pointer_;
        d->pointer_ = 0;
    }
    ~Deleter() { delete pointer_; }
    T* pointer_;
};

#endif /* defined(__TestinC____File__) */
