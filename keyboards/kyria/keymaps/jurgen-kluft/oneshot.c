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
    if (keycode == trigger)
    {
        if (record->event.pressed)
        {
            // Trigger keydown
            if ((*state & os_state_mask) == os_up_unqueued)
            {
                add_mods(MOD_BIT(mod));
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
                    del_mods(MOD_BIT(mod));
                    add_oneshot_mods(MOD_BIT(mod));
                    break;
                case os_down_unused | os_up_queued:
                    *state = (*state ^ os_down_unused);
#ifdef ENABLE_ONESHOT_HOLD
                    toggle_oneshot_hold(state);
                    if (is_oneshot_hold(*state))
                    {
                        del_oneshot_mods(MOD_BIT(mod));
                        add_mods(MOD_BIT(mod));
                    }
                    else
                    {
                        del_mods(MOD_BIT(mod));
                        add_oneshot_mods(MOD_BIT(mod));
                    }
#endif
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = os_up_unqueued;
                    del_mods(MOD_BIT(mod));
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
                    del_mods(MOD_BIT(mod));
                    del_oneshot_mods(MOD_BIT(mod));
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
