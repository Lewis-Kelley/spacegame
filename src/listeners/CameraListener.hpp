#ifndef CAMERALISTENER_H
#define CAMERALISTENER_H

#include <vector>

#include "Listener.hpp"
#include "../events/Event.hpp"
#include "../drawables/Drawable.hpp"
#include "../util/Direction.hpp"
#include "../events/EventHandler.hpp"
#include "../events/CameraMoveEvent.hpp"
#include "../events/StopCameraMoveEvent.hpp"

/**
 * Listener for camera events that updates all it's held images
 * accordingly.
 */
class CameraListener {
 private:
    class StartMoveListener : public Listener {
     private:
        CameraListener *outer;

     public:
        StartMoveListener(CameraListener *outer) : outer(outer) { }
        virtual ~StartMoveListener() { }
        void catch_event(Event *event);
    } start_move_listener;

    class EndMoveListener : public Listener {
     private:
        CameraListener *outer;

     public:
        EndMoveListener(CameraListener *outer) : outer(outer) { }
        virtual ~EndMoveListener() { }
        void catch_event(Event *event);
    } end_move_listener;

    std::vector<Drawable *> *images;
    Direction camera_dir;
    bool given_images;

    void add_as_listener();

 public:
    CameraListener();
    explicit CameraListener(std::vector<Drawable *> *images);
    ~CameraListener();
};

#endif /* CAMERALISTENER_H */
