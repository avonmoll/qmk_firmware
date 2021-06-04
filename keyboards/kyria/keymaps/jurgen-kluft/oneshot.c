#include "oneshot.h"

#ifdef ENABLE_ONESHOT

#define CASSERT(predicate) _impl_CASSERT_LINE(predicate,__LINE__,__FILE__)

#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) \
    typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];

CASSERT(sizeof(oneshot_state) == sizeof(uint8_t));

bool is_oneshot_hold(oneshot_state state)
{
    return (state & os_mode_mask) == os_mode_hold;
}

void toggle_oneshot_hold(oneshot_state* state)
{
    if (is_oneshot_hold(*state))
    {
        *state = (*state & ~os_mode_mask);
    }
    else
    {
        *state = (*state | os_mode_hold);
    }
}


void update_oneshot(oneshot_state* state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t* record)
{
    if (keycode == trigger)
    {
        if (record->event.pressed)
        {
            // Trigger keydown
            if ((*state & os_state_mask) == os_up_unqueued)
            {
                register_code(mod);
                *state = (*state & ~os_state_mask) | os_down_unused;
            }
        }
        else
        {
            // Trigger keyup
            switch (*state & os_state_mask)
            {
                case os_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = (*state & ~os_state_mask) | os_up_queued;
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    if (!is_oneshot_hold(*state))
                    {
                        *state = os_up_unqueued;
                        unregister_code(mod);
                    }
                    break;
                case os_up_queued:
                    toggle_oneshot_hold(state); 
                    break;
                default: 
                    break;
            }
        }
    }
    else
    {
        if (record->event.pressed)
        {
            if (is_oneshot_cancel_key(keycode))
            {
                if ((*state & os_state_mask) != os_up_unqueued)
                {
                    // Cancel all on designated cancel keydown.
                    unregister_code(mod);
                } 
                *state = os_up_unqueued;
            }
        }
        else
        {
            if (!is_oneshot_ignored_key(keycode))
            {
                if (!is_oneshot_hold(*state))
                {
                    // On non-ignored keyup, consider the oneshot used.
                    switch (*state & os_state_mask)
                    {
                        case os_down_unused: 
                            *state = os_down_used;
                            break;
                        case os_up_queued:
                            *state = os_up_unqueued;
                            unregister_code(mod);
                            break;
                        default: break;
                    }
                }
            }
        }
    }
}

#endif
