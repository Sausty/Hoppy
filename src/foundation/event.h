/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** event.h
*/

#ifndef EVENT_H_
#define EVENT_H_

#include <cstdint>

namespace hoppy {
    /// @brief An enum representing the various event types
    enum class event_type {
        /// @brief Window has been resized
        resize,
        /// @brief The mouse wheel has been scrolled
        mouse_wheel,
        /// @brief A gamepad has been connected
        gamepad_connect,
        /// @brief A gamepad has been disconnected
        gamepad_disconnect
    };

    /// @brief A struct representing an event
    struct event {
        /// @brief The data the event holds (max 128 bytes)
        union {
            /// @brief An array of 2 64-bit signed integers
            int64_t i64[2];
            /// @brief An array of 2 64-bit unsigned integers
            uint64_t u64[2];
            /// @brief An array of 2 64-bit floating-point numbers
            double f64[2];
            /// @brief An array of 4 32-bit signed integers
            int32_t i32[4];
            /// @brief An array of 4 32-bit unsigned integers
            uint32_t u32[4];
            /// @brief An array of 4 32-bit floating-point numbers
            float f32[4];
            /// @brief An array of 8 16-bit signed integers
            int16_t i16[8];
            /// @brief An array of 8 16-bit unsigned integers
            uint16_t u16[8];
            /// @brief An array of 16 8-bit signed integers
            int8_t i8[16];
            /// @brief An array of 16 8-bit unsigned integers
            uint8_t u8[16];
            /// @brief An array of 16 characters
            char c[16];
        } payload;
    };

    /// @brief A function pointer which is used for event subscriptions by the subscriber
    /// @param type The type of event to send
    /// @param sender A pointer to the sender of the event. Can be NULL
    /// @param listener A pointer to the listener of the event. Can be NULL
    /// @param data The event context to be passed with the fired event
    /// @return True if the message should be considered handled, which mean that it will not be sent to any other consumers; otherwise false.
    typedef bool (*pfn_on_event)(event_type type, void *sender, void *listener_inst, event data);
    
    /// @brief Initialises the event system
    void event_system_init();

    /// @brief Shuts the event system down
    void event_system_exit();

    /// @brief Register to listen for when events are sent with the provided type.
    /// @param type The event type to listen for
    /// @param listener A pointer to a listener instance. Can be NULL
    /// @param on_event The callback function pointer to be invoked when the event code is fired
    void event_system_register(event_type type, void *listener, pfn_on_event on_event);

    /// @brief Unregister to listen for when events are sent with the provided type.
    /// @param type The event type to listen for
    /// @param listener A pointer to a listener instance. Can be NULL
    /// @param on_event The callback function pointer to be unregistered
    void event_system_unregister(event_type type, void *listener, pfn_on_event on_event);

    /// @brief Fires an event to listeners of the given type.
    /// @param type The event type to fire. 
    /// @param sender A pointer to the sender. Can be NULL
    /// @param data The event data.
    /// @return Whether or not the event is handled
    bool event_system_fire(event_type type, void *sender, event data);
}

#endif /* !EVENT_H_ */
