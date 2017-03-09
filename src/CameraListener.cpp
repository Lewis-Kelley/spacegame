#include "CameraListener.hpp"

void CameraListener::add_as_listener()
{
    event_handler::add_listener(Event::START_CAMERA_MOVE, this);
    event_handler::add_listener(Event::STOP_CAMERA_MOVE, this);
}

/**
 * Create a new CameraListener with an empty vector of Drawable's to
 * update.
 */
CameraListener::CameraListener()
    : images(new std::vector<Drawable *>), camera_dir(NO_DIRECTION)
{
    add_as_listener();
    given_images = false;
}

/**
 * Create a new CameraListener with a pointer to some vector of
 * Drawable's to update.
 *
 * @param images A vector of Drawable's this Listener will update when
 * appropriate.
 */
CameraListener::CameraListener(std::vector<Drawable *> *images)
    : images(images), camera_dir(NO_DIRECTION)
{
    add_as_listener();
    given_images = true;
}

/**
 * Handle a CameraMoveEvent by passing it through to the underlying
 * Drawable image.
 *
 * @param event The CameraMoveEvent to handle.
 */
void CameraListener::handle_camera_move_event(CameraMoveEvent *event)
{
    Direction event_dir = event->get_dir();
    MovementType type = is_horiz_dir(event_dir) ? CAMERA_X : CAMERA_Y;

    // Check if either the camera isn't moving OR that it wasn't
    // moving in the opposite direction to this new move
    if (camera_dir == NO_DIRECTION
        || (is_cardinal_dir(camera_dir) && event_dir != opp_dir(camera_dir))) {
        camera_dir = merge_directions(camera_dir, event_dir);

        for (Drawable *image : *images) {
            image->start_move(event->get_dx(), event->get_dy(), type);
        }
    }
}

/**
 * Handle a StopCameraMoveEvent by halting the underlying Drawable
 * motion.
 *
 * @param event The StopCameraMoveEvent to handle.
 */
void CameraListener::handle_camera_stop_move_event(StopCameraMoveEvent *event)
{
    if (!has_direction(event->get_dir(), camera_dir)) {
        return;
    }

    MovementType type;

    if (has_direction(event->get_dir(), EAST)
        || has_direction(event->get_dir(), WEST)) {
        type = CAMERA_X;
    } else {
        type = CAMERA_Y;
    }

    for (Drawable *image : *images) {
        image->end_move(type);
    }

    camera_dir = remove_direction(camera_dir, event->get_dir());
}
void CameraListener::catch_event(Event *event)
{
    switch (event->get_type()) {
    case Event::START_CAMERA_MOVE:
        handle_camera_move_event((CameraMoveEvent *)event);
        break;
    case Event::STOP_CAMERA_MOVE:
        handle_camera_stop_move_event((StopCameraMoveEvent *)event);
        break;
    default:
        break;
    }
}
