#include "CameraListener.hpp"

void CameraListener::add_as_listener()
{
    auto handler = EventHandler::get_instance();

    CameraMoveEvent camera_event;
    StopCameraMoveEvent stop_event;

    handler->add_listener(&camera_event, [this](Event *event)
                          { handle_start_move(event); });
    handler->add_listener(&stop_event, [this](Event *event)
                          { handle_stop_move(event); });
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
void CameraListener::handle_start_move(Event *event)
{
    auto start_event = dynamic_cast<CameraMoveEvent *>(event);

    Direction event_dir = start_event->get_dir();

    // Check if either the camera isn't moving OR that it wasn't
    // moving in the opposite direction to this new move
    if (camera_dir == NO_DIRECTION
        || (is_cardinal_dir(camera_dir)
            && event_dir != opp_dir(camera_dir))) {
        camera_dir = merge_directions(camera_dir, event_dir);
        // FIXME Maybe move the pertinant logic out of the Event so we
        // don't make a new one?
        CameraMoveEvent *move_event = new CameraMoveEvent(camera_dir);

        for (Drawable *image : *images) {
            image->start_move(move_event->get_dx(), move_event->get_dy(),
                              CAMERA);
        }
    }
}

/**
 * Handle a StopCameraMoveEvent by halting the underlying Drawable
 * motion.
 *
 * @param event The StopCameraMoveEvent to handle.
 */
void CameraListener::handle_stop_move(Event *event)
{
    auto stop_event = dynamic_cast<StopCameraMoveEvent *>(event);

    if (!has_direction(camera_dir, stop_event->get_dir())) {
        return;
    }

    for (Drawable *image : *images) {
        image->end_move(CAMERA);
    }

    camera_dir
        = remove_direction(camera_dir, stop_event->get_dir());

    handle_start_move(new CameraMoveEvent(camera_dir));
}
