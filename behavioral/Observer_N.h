//
//  Observer_N.h
//  OneMind
//
//  Created by Abadie, Loïc on 20/06/13.
//  Copyright (c) 2013 Abadie, Loïc. All rights reserved.
//

#ifndef OneMind_Observer_N_h
#define OneMind_Observer_N_h
#include "Observer_O.h"
#include <vector>

template <class T>
class Observer_N{
public:
    Observer_N() {}
    virtual ~Observer_N() {}

    void subscribe(Observer_O<T> &observer){
        m_observers.push_back(&observer);
    }
    
    void unSubscribe(Observer_O<T> &observer){
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), &observer), m_observers.end());
    }
    
    void notify(){
        typename std::vector<Observer_O<T> *>::iterator it;
        
        for (it = m_observers.begin(); it != m_observers.end(); it++)
            (*it)->update(static_cast<T *>(this));
    }
private:
    std::vector<Observer_O<T> *> m_observers;
};

#endif
