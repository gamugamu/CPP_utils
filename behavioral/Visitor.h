//
//  Visitor.h
//  OneMind
//
//  Created by Abadie, Loïc on 19/06/13.
//  Copyright (c) 2013 Abadie, Loïc. All rights reserved.
//

#ifndef OneMind_Visitor_h
#define OneMind_Visitor_h

class Visitor {

public:
    virtual void willVisit(void* node) = 0;
    virtual void didVisit(void* node) = 0;
};

#endif
