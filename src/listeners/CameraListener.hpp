#ifndef CAMERALISTENER_H
#define CAMERALISTENER_H

#include <vector>

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
    std::vector<Drawable *> *images;
    Direction camera_dir;
    bool given_images;

    void add_as_listener();

 public:
    CameraListener();
    explicit CameraListener(std::vector<Drawable *> *images);
    ~CameraListener();
    void handle_start_move(Event *event);
    void handle_stop_move(Event *event);
};

#endif /* CAMERALISTENER_H */
