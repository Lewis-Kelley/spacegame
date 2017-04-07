#ifndef MOVEMENTLISTENER_H
#define MOVEMENTLISTENER_H

#include "../events/EventHandler.hpp"
#include "../entities/Unit.hpp"
#include "Listener.hpp"
#include "../events/MoveEvent.hpp"
#include "../events/StopMoveEvent.hpp"
#include "../events/MoveFinishedEvent.hpp"
#include "../events/SelectUnitEvent.hpp"
#include "../events/DeselectUnitEvent.hpp"

/**
 * Listenes for movement Event's, keeps track of the selected Unit,
 * and moves the Unit as necessary.
 */
class MovementListener {
 private:
    class StartMoveListener : public Listener {
     private:
        MovementListener *outer;

     public:
        StartMoveListener(MovementListener *outer) : outer(outer) { }
        virtual ~StartMoveListener() { }
        void catch_event(Event *event);
    } start_listener;

    class StopMoveListener : public Listener {
     private:
        MovementListener *outer;

     public:
        StopMoveListener(MovementListener *outer) : outer(outer) { }
        virtual ~StopMoveListener() { }
        void catch_event(Event *event);
    } stop_listener;

    class MoveFinishedListener : public Listener {
     private:
        MovementListener *outer;

     public:
        MoveFinishedListener(MovementListener *outer) : outer(outer) { }
        virtual ~MoveFinishedListener() { }
        void catch_event(Event *event);
    } finished_listener;

    class SelectUnitListener : public Listener {
     private:
        MovementListener *outer;

     public:
        SelectUnitListener(MovementListener *outer) : outer(outer) { }
        virtual ~SelectUnitListener() { }
        void catch_event(Event *event);
    } select_unit_listener;

    class DeselectUnitListener : public Listener {
     private:
        MovementListener *outer;

     public:
        DeselectUnitListener(MovementListener *outer) : outer(outer) { }
        virtual ~DeselectUnitListener() { }
        void catch_event(Event *event);
    } deselect_unit_listener;

    Unit *controlled;
    Direction move_dir;
    Direction queue_dir;

 public:
    MovementListener();
    void catch_event(Event *event);
};

#endif /* MOVEMENTLISTENER_H */
