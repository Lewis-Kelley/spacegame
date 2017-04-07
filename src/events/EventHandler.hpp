#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <map>
#include <stdexcept>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "Event.hpp"
#include "../listeners/Listener.hpp"

class EventHandler {
 public:
    typedef std::map<std::type_index, std::vector<Listener *>*> listener_map;

 private:
    static EventHandler *self;
    listener_map *listeners;
    bool given_map;

    EventHandler() : listeners()
    {
        listeners = new listener_map(); given_map = false;
    }

 protected:
    EventHandler(listener_map *map) : listeners(map) { given_map = true; }

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

    ~EventHandler();

    void handle_event(Event *event) const;
    void add_listener(Event *sample_event, Listener *obs);
    void remove_listener(Event *sample_event, Listener *obs);
};

#endif
