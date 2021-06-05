#include "oneshot.h"

#ifdef ENABLE_ONESHOT


#ifdef ENABLE_ONESHOT_HOLD
bool is_oneshot_hold(oneshot_state state)
{
    return (state & os_mode_mask) == os_mode_hold;
}

void toggle_oneshot_hold(oneshot_state* state)
{
    *state = (*state ^ os_mode_hold);
}
#endif

void update_oneshot(oneshot_state* state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t* record)
{
    // @TODO: Can still extract MOD_BIT(mod) out to the caller site
    uint16_t modbit = MOD_BIT(mod);
    
    if (keycode == trigger)
    {
        if (record->event.pressed)
        {
            // Trigger keydown
            if ((*state & os_state_mask) == os_up_unqueued)
            {
                add_mods(modbit);
            }
            *state = *state | os_down_unused;
        }
        else
        {
            // Trigger keyup
            switch (*state & os_state_mask)
            {
                case os_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = (*state & ~os_state_mask) | os_up_queued;
                    del_mods(modbit);
                    add_oneshot_mods(modbit);
                    break;
                case os_down_unused | os_up_queued:
                    *state = (*state ^ os_down_unused);
#ifdef ENABLE_ONESHOT_HOLD
                    toggle_oneshot_hold(state);
                    if (is_oneshot_hold(*state))
                    {
                        del_oneshot_mods(modbit);
                        add_mods(modbit);
                    }
                    else
                    {
                        del_mods(modbit);
                        add_oneshot_mods(modbit);
                    }
#endif
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = os_up_unqueued;
                    del_mods(modbit);
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
                    // Turn off mod
                    del_mods(modbit);
                    del_oneshot_mods(modbit);
                } 
                *state = os_up_unqueued;
            } 
        } else {
            if (!is_oneshot_ignored_key(keycode))
            {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state & os_state_mask)
                {
                    case os_down_unused: 
                    case os_down_unused | os_up_queued: 
                        *state = os_down_used;
                        break;
                    case os_up_queued:
#ifdef ENABLE_ONESHOT_HOLD
                        if (!is_oneshot_hold(*state))
                        {
                            *state = os_up_unqueued;
                        }
#else
                        *state = os_up_unqueued;
#endif
                        break;
                    default: break;
                }
            }            
        }
    }
}

#endif
