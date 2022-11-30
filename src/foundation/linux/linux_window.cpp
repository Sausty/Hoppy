/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** macos_window
*/

#include "foundation/window.h"
#include "foundation/log.h"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <string.h>

namespace hoppy {
    struct x11_state {
        Display* display;
        xcb_connection_t* connection;
        xcb_window_t window;
        xcb_screen_t* screen;
        xcb_atom_t protocols;
        xcb_atom_t delete_win;
        bool is_open;
    };

    x11_state x_state;
    
    void window_init(window *w, uint32_t width, uint32_t height, const char *title)
    {
        x_state.is_open = true;

        x_state.display = XOpenDisplay(nullptr);
        if (!x_state.display) {
            log_crit("[ERROR] Failed to open linux display!");
        }
        x_state.connection = XGetXCBConnection(x_state.display);
        if (xcb_connection_has_error(x_state.connection)) {
            log_crit("[ERROR] Failed to connect to X server via XCB!");
        }

        const struct xcb_setup_t* setup = xcb_get_setup(x_state.connection);
        xcb_screen_iterator_t iterator = xcb_setup_roots_iterator(setup);
        int screen = 0;
        for (int screen_number = screen; screen_number > 0; screen_number--) {
            xcb_screen_next(&iterator);
        }
        x_state.screen = iterator.data;

        x_state.window = xcb_generate_id(x_state.connection);

        uint32_t event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t event_listeners = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                           XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
                           XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                           XCB_EVENT_MASK_STRUCTURE_NOTIFY;
        uint32_t value_list[] = { x_state.screen->black_pixel, event_listeners };
        xcb_create_window(x_state.connection, XCB_COPY_FROM_PARENT, x_state.window, x_state.screen->root,
                          0, 0, width, height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, x_state.screen->root_visual,
                          event_mask, value_list);

        xcb_change_property(x_state.connection, XCB_PROP_MODE_REPLACE, x_state.window, XCB_ATOM_WM_NAME,
                            XCB_ATOM_STRING, 8, strlen(title), title);

        xcb_intern_atom_cookie_t delete_cookie = xcb_intern_atom(x_state.connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
        xcb_intern_atom_cookie_t protocols_cookie = xcb_intern_atom(x_state.connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
        xcb_intern_atom_reply_t* delete_reply = xcb_intern_atom_reply(x_state.connection, delete_cookie, NULL);
        xcb_intern_atom_reply_t* protocols_reply = xcb_intern_atom_reply(x_state.connection, protocols_cookie, NULL);
        x_state.protocols = protocols_reply->atom;
        x_state.delete_win = delete_reply->atom;

        xcb_change_property(x_state.connection, XCB_PROP_MODE_REPLACE, x_state.window, protocols_reply->atom, 4, 32, 1, &delete_reply->atom);
        
        xcb_map_window(x_state.connection, x_state.window);
        
        int stream_result = xcb_flush(x_state.connection);
        if (stream_result <= 0) {
            log_crit("[ERROR] Error %d when flushing the XCB stream", stream_result);
        }
    }
    
    void window_free(window *w)
    {
        xcb_destroy_window(x_state.connection, x_state.window);
        XCloseDisplay(x_state.display);
    }
    
    void window_poll_events(window *w)
    {
        xcb_generic_event_t* event;
        xcb_client_message_event_t* custom_client_message;
        while ((event = xcb_poll_for_event(x_state.connection))) {
            switch (event->response_type & ~0x80) {
                case XCB_CLIENT_MESSAGE: {
                    custom_client_message = (xcb_client_message_event_t*)event;
                    if (custom_client_message->data.data32[0] == x_state.delete_win) {
                        x_state.is_open = false;
                    }
                } break;
                default: {
                    break;
                }
            }
        }
    }

    bool window_is_open(window *w)
    {
        return x_state.is_open;
    }
}
