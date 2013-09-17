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


// supprime un pointer si il est non null, l'assigne ensuite à nul.
template <typename type>
void deleteIfNoNull(type pointer){
    if(pointer){
        delete pointer;
        pointer = nullptr;
    }
}

// smartpointer permettant de supprimer un pointer lors de sa suppression.
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
