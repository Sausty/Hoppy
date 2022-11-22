/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** event.cpp
*/

#include "event.h"
#include "log.h"

#include <vector>
#include <map>

namespace hoppy {
    struct registered_event {
        void *listener;
        pfn_on_event callback;
    };

    struct event_type_entry {
        std::vector<registered_event> events;
    };

    struct event_system {
        std::map<event_type, event_type_entry> registered;
    };

    static event_system _e_system;

    void event_system_init()
    {
        _e_system = {};
    }

    void event_system_exit()
    {
        _e_system.registered.clear();
    }

    void event_system_register(event_type type, void *listener, pfn_on_event on_event)
    {
        uint64_t registered_count = _e_system.registered[type].events.size();
        for (uint64_t i = 0; i < registered_count; i++) {
            if (_e_system.registered[type].events[i].listener == listener) {
                log_warn("[WARN] Trying to register an event listener that is already registered!");
                return;
            }
        }

        registered_event event;
        event.listener = listener;
        event.callback = on_event;
        _e_system.registered[type].events.push_back(event);
    }

    void event_system_unregister(event_type type, void *listener, pfn_on_event on_event)
    {
        if (_e_system.registered[type].events.empty()) {
            log_warn("[WARN] Trying to unregister an event listener that isn't registered!");
            return;
        }

        uint64_t registered_count = _e_system.registered[type].events.size();
        for (uint64_t i = 0; i < registered_count; i++) {
            if (_e_system.registered[type].events[i].listener == listener) {
                registered_event popped_event = _e_system.registered[type].events[i];
                _e_system.registered[type].events.erase(_e_system.registered[type].events.begin() + i);
            }
        }
    }

    bool event_system_fire(event_type type, void *sender, event data)
    {
        if (_e_system.registered[type].events.empty()) {
            return false;
        }

        uint64_t registered_count = _e_system.registered[type].events.size();
        for (uint64_t i = 0; i < registered_count; i++) {
            registered_event e = _e_system.registered[type].events[i];
            if (e.callback(type, sender, e.listener, data)) {
                return true;
            }
        }
        return false;
    }
}
