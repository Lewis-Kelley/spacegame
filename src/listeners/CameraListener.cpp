#include "CameraListener.hpp"

void CameraListener::add_as_listener()
{
    auto handler = EventHandler::get_instance();

    CameraMoveEvent camera_event;
    StopCameraMoveEvent stop_event;

    handler->add_listener(&camera_event, &start_move_listener);
    handler->add_listener(&stop_event, &end_move_listener);
}

/**
 * Create a new CameraListener with an empty vector of Drawable's to
 * update.
 */
CameraListener::CameraListener()
    : start_move_listener(this), end_move_listener(this),
      images(new std::vector<Drawable *>), camera_dir(NO_DIRECTION)
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
    : start_move_listener(this), end_move_listener(this),
      images(images), camera_dir(NO_DIRECTION)
{
    add_as_listener();
    given_images = true;
}

CameraListener::~CameraListener()
{
    if (!given_images && images != NULL) {
        delete images;
    }
}

/**
 * Handle a CameraMoveEvent by passing it through to the underlying
 * Drawable image.
 *
 * @param event The CameraMoveEvent to handle.
 */
void CameraListener::StartMoveListener::catch_event(Event *event)
{
    auto start_event = dynamic_cast<CameraMoveEvent *>(event);

    Direction event_dir = start_event->get_dir();
    MovementType type = is_horiz_dir(event_dir) ? CAMERA_X : CAMERA_Y;

    // Check if either the camera isn't moving OR that it wasn't
    // moving in the opposite direction to this new move
    if (outer->camera_dir == NO_DIRECTION
        || (is_cardinal_dir(outer->camera_dir)
            && event_dir != opp_dir(outer->camera_dir))) {
        outer->camera_dir = merge_directions(outer->camera_dir, event_dir);

        for (Drawable *image : *outer->images) {
            image->start_move(start_event->get_dx(), start_event->get_dy(),
                              type);
        }
    }
}

/**
 * Handle a StopCameraMoveEvent by halting the underlying Drawable
 * motion.
 *
 * @param event The StopCameraMoveEvent to handle.
 */
void CameraListener::EndMoveListener::catch_event(Event *event)
{
    auto stop_event = dynamic_cast<StopCameraMoveEvent *>(event);

    if (!has_direction(stop_event->get_dir(), outer->camera_dir)) {
        return;
    }

    MovementType type;

    if (has_direction(stop_event->get_dir(), EAST)
        || has_direction(stop_event->get_dir(), WEST)) {
        type = CAMERA_X;
    } else {
        type = CAMERA_Y;
    }

    for (Drawable *image : *outer->images) {
        image->end_move(type);
    }

    outer->camera_dir
        = remove_direction(outer->camera_dir, stop_event->get_dir());
}
