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
class CameraListener : public Listener {
private:
    std::vector<Drawable *> *images;
    Direction camera_dir;
    bool given_images;

    void handle_camera_move_event(CameraMoveEvent *event);
    void handle_camera_stop_move_event(StopCameraMoveEvent *event);
    void add_as_listener();
public:
    CameraListener();
    CameraListener(std::vector<Drawable *> *images);
    ~CameraListener() { if (!given_images) delete images; }
    void catch_event(Event *event);
};

#endif /* CAMERALISTENER_H */
