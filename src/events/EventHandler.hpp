#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <stdexcept>

#include "Event.hpp"
#include "../listeners/Listener.hpp"

class EventHandler {
 public:
    typedef std::map<Event::Event_Type, std::vector<Listener *>*> listener_map;

 private:
    static EventHandler *self;
    listener_map *listeners;

    EventHandler() : listeners() { }

 protected:
    EventHandler(listener_map *map) : listeners(map) { }

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

    void handle_event(Event *event) const;
    void add_listener(Event::Event_Type type, Listener *obs);
    void remove_listener(Event::Event_Type type, Listener *obs);
};

#endif
