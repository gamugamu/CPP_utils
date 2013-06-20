//
//  Observer_N.h
//  OneMind
//
//  Created by Abadie, Loïc on 20/06/13.
//  Copyright (c) 2013 Abadie, Loïc. All rights reserved.
//

#ifndef OneMind_Observer_N_h
#define OneMind_Observer_N_h

template <class T>
class Observer_N
{
public:
    Observer_N() {}
    virtual ~Observer_N() {}
    
    void attach (Observer<T> &observer){
        m_observers.push_back(&observer);
    }
    
    void notify (){
        std::vector<Observer<T> *>::iterator it;
        for (it=m_observers.begin();it!=m_observers.end();it++)
            (*it)->update(static_cast<T *>(this));
    }
private:
    std::vector<Observer<T> *> m_observers;
};

#endif
