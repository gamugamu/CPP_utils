//
//  Observer_S.h
//  OneMind
//
//  Created by Abadie, Loïc on 20/06/13.
//  Copyright (c) 2013 Abadie, Loïc. All rights reserved.
//

#ifndef OneMind_Observer_S_h
#define OneMind_Observer_S_h

template <class T>

class Observer_O{
public:
    Observer_O() {}
    virtual ~Observer_O() {}
    virtual void update(T *subject)= 0;
};

#endif
