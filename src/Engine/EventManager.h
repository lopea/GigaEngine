//
// Created by javier on 6/2/2020.
//

#ifndef GIGAENGINE_EVENTMANAGER_H
#define GIGAENGINE_EVENTMANAGER_H

#include <functional>
#include <deque>
#include <rttr/type>


class GenericEvent
{
public:
    virtual ~GenericEvent()= default;
    virtual void Unsubscribe(const std::string& id) = 0;
};

template<typename... Args>
class Event : public GenericEvent
{

public:

    void operator()(Args... args);


    void Subscribe(const std::string& id, std::function<void(Args...)> func);

    void Unsubscribe(const std::string& id) override;


    void clear() {functions_.clear();};

    ~Event() override = default;

private:

    void Invoke(Args... args);

    std::unordered_map<std::string, std::function<void(Args...)> > functions_;
};

template<typename... Args>
void Event<Args...>::Subscribe(const std::string& id, std::function<void(Args...)> func)
{
    functions_[id] = func;
}

template<typename... Args>
void Event<Args...>::Unsubscribe(const std::string& id)
{
    functions_.erase(id);
}

template<typename... Args>
void Event<Args...>::Invoke(Args... args)
{
    for(auto it = functions_.begin(); it != functions_.end(); ++it)
    {
       it->second(args...);
    }
}

template<typename... Args>
void Event<Args...>::operator()(Args... args)
{
    Invoke(args...);
}


class EventManager
{
public:
    EventManager() = default;

    template<typename... Args>
    void AddEvent(unsigned int EventID);

    template<typename... Args>
    void InvokeEvent(unsigned int EventID, Args... args);

    template<typename... Args>
    void SubscribeEvent(unsigned int EventID, const std::string& FunctionID, std::function<void(Args...)> function);

    template<typename... Args>
    void SubscribeEvent(unsigned int EventID, const std::string& FunctionID, void(*function)(Args...));

    template<typename... Args, typename Func>
    void SubscribeEvent(unsigned int EventID,
                                      const std::string &FunctionID, Func function);

    void UnsubscribeEvent(unsigned int EventID, const std::string& FunctionID);
    
    template<typename... Args>
    static void AddGlobalEvent(unsigned int EventID);

    template<typename... Args>
    static void SubscribeGlobalEvent(unsigned int EventID, const std::string& FunctionID, std::function<void(Args...)> function);

    static void UnsubscribeGlobalEvent(unsigned int EventID, const std::string& FunctionID);

    ~EventManager();
    
private:
    std::unordered_map<unsigned int, GenericEvent*> events_;

    EventManager(const EventManager& manager) = default;
    EventManager& operator=(const EventManager& manager) = default;

    void clear();
    static EventManager global_;
    static bool Init_;
};

inline EventManager EventManager::global_;
inline bool EventManager::Init_;

template<typename... Args>
void EventManager::AddEvent(unsigned int EventID)
{
    auto it = events_.find(EventID);

    if(it == events_.end())
    {
        events_[EventID] = new Event<Args...>();
    }

}

template<typename... Args>
void EventManager::InvokeEvent(unsigned int EventID, Args... args)
{
    auto it = events_.find(EventID);

    if (it != events_.end())
    {
        static_cast< Event<Args...>* >(it->second)->operator()(args...);
    }
}

void EventManager::UnsubscribeEvent(unsigned int EventID, const std::string &FunctionID)
{
    auto it = events_.find(EventID);

    if (it != events_.end())
    {
        it->second->Unsubscribe(FunctionID);
    }
}

template<typename... Args>
void EventManager::SubscribeEvent(unsigned int EventID,
        const std::string &FunctionID, std::function<void(Args...)> function)
{
    auto it = events_.find(EventID);

    if (it != events_.end())
    {
        static_cast< Event<Args...>* >(it->second)->Subscribe(FunctionID, function);
    }
}

template<typename... Args, typename Func>
void EventManager::SubscribeEvent(unsigned int EventID,
                                  const std::string &FunctionID, Func function)
{
    auto it = events_.find(EventID);
    std::function<void(Args...)> f = function;
    if (it != events_.end())
    {
        static_cast< Event<Args...>* >(it->second)->Subscribe(FunctionID, f);
    }
}


template<typename... Args>
void EventManager::AddGlobalEvent(unsigned int EventID)
{
    global_.AddEvent<Args...>(EventID);
}

EventManager::~EventManager()
{
    clear();
}

template<typename... Args>
void EventManager::SubscribeGlobalEvent(unsigned int EventID, const std::string &FunctionID,
                                        std::function<void(Args...)> function)
{
   global_.SubscribeEvent(EventID, FunctionID, function);
}

void EventManager::UnsubscribeGlobalEvent(unsigned int EventID, const std::string &FunctionID)
{
    global_.UnsubscribeEvent(EventID, FunctionID);
}

void EventManager::clear()
{
    for(auto it : events_)
    {
        delete it.second;
    }
    events_.clear();
}

template<typename... Args>
void EventManager::SubscribeEvent(unsigned int EventID, const std::string &FunctionID, void (*function)(Args...))
{
    auto it = events_.find(EventID);

    if (it != events_.end())
    {
        static_cast< Event<Args...>* >(it->second)->Subscribe(FunctionID, function);
    }
}


#endif //GIGAENGINE_EVENTMANAGER_H
