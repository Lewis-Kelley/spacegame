#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <functional>
#include <map>
#include <stdexcept>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "Event.hpp"

class EventHandler {
 public:
    typedef uint16_t listener_key_t;
    typedef std::function<void(Event *)> listener_t;
    typedef std::pair<listener_key_t,
                      std::function<void(Event *)>> listener_pair_t;
    typedef std::map<std::type_index,
                     std::vector<listener_pair_t> *> listener_map_t;

 private:
    static EventHandler *self;
    static listener_key_t next_listener_key;

    listener_map_t *listeners;
    bool given_map;

    EventHandler() : listeners()
    {
        listeners = new listener_map_t(); given_map = false;
    }

 protected:
    EventHandler(listener_map_t *map) : listeners(map) { given_map = true; }

 public:
    class InvalidListenerException : public std::exception {
     private:
        std::string msg;
     public:
        InvalidListenerException(std::string msg) : msg(msg) { }
        ~InvalidListenerException() throw() { }
        const char *what() const throw() { return msg.c_str(); }
    };

    class InvalidEventException : public std::exception {
     private:
        std::string msg;
     public:
        InvalidEventException(std::string msg) : msg(msg) { }
        ~InvalidEventException() throw() { }
        const char *what() const throw() { return msg.c_str(); }
    };

    static EventHandler *get_instance();
    static void reset();

    virtual ~EventHandler();

    virtual void handle_event(Event *event) const;
    virtual listener_key_t add_listener(Event *sample_event, listener_t obs);
    virtual void remove_listener(listener_key_t obs);
};

#endif
