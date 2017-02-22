#include "event_handler.hpp"

event_handler::event_handler() {
    // Do nothing
}

event_handler *event_handler::get_instance() {
    if (self == NULL) {
        self = new event_handler();
    }

    return self;
}

/**
 * Calls any listeners that are waiting for the passed event.
 *
 * @param event The SDL_Event to handle.
 */
void event_handler::handle_event(SDL_Event *event) {
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_q) {
        SDL_Event *quit_event = new SDL_Event();
        quit_event->type = SDL_QUIT;
        SDL_PushEvent(quit_event);
    }
}

/**
 * Adds a new listener to the handler with the given information.
 *
 * @param event_code The event code upon which to trigger the
 * listener.
 * @param obs The listener to add to the observer list.
 */
void event_handler::add_listener(uint32_t event_code, listener *obs) {
}

/**
 * Remove the given listener from the call list with the given
 * event_code.
 *
 * @param event_code The event code from which to remove the listener.
 * @param obs The listener to remove.
 */
void event_handler::remove_listener(uint32_t event_code, listener *obs) {
}

// /**
//  * Do all actions necessary for the given event.
//  *
//  * @param [in] event The event to handle.
//  */
// void EventHandler::handle_event(SDL_Event *event) {
//   switch(event->type) {
//   case SDL_KEYDOWN:
//     if(event->key.repeat == 0) {
//       key_down(event->key.keysym.sym);
//     }
//     break;
//   case SDL_KEYUP :
//     key_up(event->key.keysym.sym);
//     break;
//   case SDL_MOUSEMOTION:
//     //EMPTY
//     break;
//   case SDL_MOUSEBUTTONDOWN:
//     switch(event->button.button) {
//     case SDL_BUTTON_LEFT:
//       //EMPTY
//       break;
//     case SDL_BUTTON_RIGHT:
//       //EMPTY
//       break;
//     case SDL_BUTTON_MIDDLE:
//       //EMPTY
//       break;
//     }
//     break;
//   case SDL_MOUSEBUTTONUP:
//     switch(event->button.button) {
//     case SDL_BUTTON_LEFT:
//       //EMPTY
//       break;
//     case SDL_BUTTON_RIGHT:
//       //EMPTY
//       break;
//     case SDL_BUTTON_MIDDLE:
//       //EMPTY
//       break;
//     }
//     break;
//   case SDL_QUIT:
//     on_quit();
//     break;
//   case SDL_WINDOWEVENT:
//     //EMPTY
//     break;
//   case SDL_TEXTINPUT:
//     //EMPTY
//     break;
//   case SDL_SYSWMEVENT:
//     //EMPTY
//     break;
//   default:
//     printf("Unhandled event: %d.\n", event->type);
//     break;
//   }
// }

// /**
//  * Handles any actions necessary for the given key_pressed event.
//  *
//  * @param [in] keycode The key that was pressed.
//  */
// void EventHandler::key_down(SDL_Keycode keycode) {
//   Control res = KeyHandler::pressed_key(keycode);

//   if (res == QUIT) {
//     Window::running = false;
//   } else if ((res & MOVE_ALL) != 0) {
//     on_move_press(res);
//   } else if ((res & CAM_ALL) != 0) {
//     on_cam_press(res);
//   }
// }

// /**
//  * Handles any actions necessary for the given key_released event.
//  *
//  * @param [in] keycode The key that was released.
//  */
// void EventHandler::key_up(SDL_Keycode keycode) {
//   Control res = KeyHandler::released_key(keycode);

//   if ((res & MOVE_ALL) != 0) {
//     on_move_rel(res);
//   } else if ((res & CAM_ALL) != 0) {
//     on_cam_rel(res);
//   }
// }

// /**
//  * Handles a movement key being pressed.
//  *
//  * @param [in] move The movement control that has been activated.
//  */
// void EventHandler::on_move_press(Control move) {
//   Direction dir;
//   switch (move) {
//   case MOVE_RIGHT:
//     dir = EAST;
//     break;
//   case MOVE_UP:
//     dir = NORTH;
//     break;
//   case MOVE_LEFT:
//     dir = WEST;
//     break;
//   case MOVE_DOWN:
//     dir = SOUTH;
//     break;
//   default:
//     printf("Unrecognized move control %d.\n", move);
//     return;
//   }

//   m_map->move_sel_unit(dir);
// }

// /**
//  * Handles a camera key being pressed.
//  *
//  * @param [in] move The camera control that has been activated.
//  */
// void EventHandler::on_cam_press(Control move) {
//   switch (move) {
//   case CAM_RIGHT:
//     m_map->m_cam_vel_x = CAM_SPEED;
//     break;
//   case CAM_UP:
//     m_map->m_cam_vel_y = -CAM_SPEED;
//     break;
//   case CAM_LEFT:
//     m_map->m_cam_vel_x = -CAM_SPEED;
//     break;
//   case CAM_DOWN:
//     m_map->m_cam_vel_y = CAM_SPEED;
//     break;
//   default:
//     printf("Unrecognized camera control %d.\n", move);
//     break;
//   }
// }

// /**
//  * Handles a movement key being released.
//  *
//  * @param [in] move The movement control that has been deactivated.
//  */
// void EventHandler::on_move_rel(Control move) {
//   // TODO Complete stubbed function.
// }

// /**
//  * Handles a camera key being released.
//  *
//  * @param [in] move The camera control that has been deactivated.
//  */
// void EventHandler::on_cam_rel(Control move) {
//   switch (move) {
//   case CAM_RIGHT:
//     if (m_map->m_cam_vel_x > 0) {
//       m_map->m_cam_vel_x = 0.0;
//     }
//     break;
//   case CAM_UP:
//     if (m_map->m_cam_vel_y < 0) {
//       m_map->m_cam_vel_y = 0.0;
//     }
//     break;
//   case CAM_LEFT:
//     if (m_map->m_cam_vel_x < 0) {
//       m_map->m_cam_vel_x = 0.0;
//     }
//     break;
//   case CAM_DOWN:
//     if (m_map->m_cam_vel_y > 0) {
//       m_map->m_cam_vel_y = 0.0;
//     }
//     break;
//   default:
//     break;
//   }
// }

// void EventHandler::on_quit() {
//   // TODO Complete stubbed function
// }
//
