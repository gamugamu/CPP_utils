//
//  Singleton.h
//  OneMind
//
//  Created by Abadie, Loïc on 20/06/13.
//  Copyright (c) 2013 Abadie, Loïc. All rights reserved.
//

#ifndef SINGLETON_DEFINED_HPP
#define SINGLETON_DEFINED_HPP

#include <thread>
#include <memory>
#include <mutex>

#include <type_traits>

/*
 Pour l'utiliser, c'est simple:
 Vous prenez une classe, vous la faites dériver de Singleton, le paramètre template
 est la classe elle-même, ensuite, si vous avez un constructeur par défaut sans 
 comportement "spécial", utilisez la macro SINGLETON_DECLARE_DEFAULT_CONSTRUCTOR(LeNomDeLaClasse),
 si vous avez un constructeur par défaut avec comportement, utilisez la macro SINGLETON_DECLARE,
 si vous n'avez pas de constructeur par défaut, utilisez simplement SINGLETON_DECLARE_NO_DEFAULT_CONSTRUCTOR.
 Enfin, utilisez la macro SINGLETON_POSSESS_DEFAULT_CONSTRUCTOR si votre classe 
 possède un constructeur par défaut, sinon utilisez SINGLETON_UNPOSSESS_DEFAULT_CONSTRUCTOR,
 hors de la classe. Un petit exemple:
 
 class Unique : public Singleton<Unique>
 {
 SINGLETON_DECLARE_DEFAULT_CONSTRUCTOR(Unique)
 public:
 void helloWorld() {
    // throw error
    }
 };
 
 SINGLETON_POSSESS_DEFAULT_CONSTRUCTOR(Unique)
 
 Unique::GetInstance()->helloWorld();
 */

template<class T>
class Singleton{
public:
    virtual ~Singleton() { }
    
    static T* getInstance()
    {
        if (!m_instance)
        {
            instancier<T, std::is_default_constructible<T>::value>::instanciate(m_instance, m_onceFlag);
            if (!m_instance) // K is not default constructible, crash detected.
                throw std::runtime_error("Singleton<T> fatal error: K is not default constructible and we ask for construct him with none args... Crash detected.");
        }
        return m_instance.get();
        
    }
    
    template<typename... Args>
    static T* getInstance(Args... args)
    {
        auto f = &Singleton<T>::template _DoInit<Args...>;
        std::call_once(m_onceFlag, f, args...);
        return m_instance.get();
    }
protected:
    Singleton() { }
    
private:
    template<typename K, bool opt>
    struct instancier
    {
        static void instanciate(std::unique_ptr<K>& instance, std::once_flag& onceFlag)
        {
            auto f = [&instance]()
            {
                instance.reset(new K);
            };
            std::call_once(onceFlag, f);
        }
    };
    template<typename K>
    struct instancier<K, false>
    {
        static void instanciate(std::unique_ptr<K>& instance, std::once_flag& onceFlag)
        {
            
        }
    };
    
    template<typename... Args>
    static void _DoInit(Args... args)
    {
        m_instance.reset(new T(std::forward<Args>(args)...));
    }
private:
    static std::unique_ptr<T> m_instance;
    static std::once_flag m_onceFlag;
    
    Singleton(const Singleton& src) = delete;
    Singleton& operator=(const Singleton& rhs) = delete;
};

#define SINGLETON_DECLARE_NO_DEFAULT_CONSTRUCTOR(className) friend class Singleton<className>;

#define SINGLETON_POSSESS_DEFAULT_CONSTRUCTOR(className) namespace std { template<> struct is_default_constructible<className> : public std::integral_constant<bool, true> { }; };
#define SINGLETON_UNPOSSESS_DEFAULT_CONSTRUCTOR(className) namespace std { template<> struct is_default_constructible<className> : public std::integral_constant<bool, false> { }; };


template<class T>
std::unique_ptr<T> Singleton<T>::m_instance = nullptr;
template<class T>
std::once_flag Singleton<T>::m_onceFlag;

#endif
