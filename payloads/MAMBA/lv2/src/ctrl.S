#include <lv2/macros.h.S>
#include <lv2/symbols.h>

#ifdef sm_ring_buzzer_symbol
LV2_FUNCTION(sm_ring_buzzer_internal, sm_ring_buzzer_symbol)
#endif

#ifdef sm_get_temperature_symbol

LV2_FUNCTION(sm_get_temperature_internal, sm_get_temperature_symbol)
LV2_FUNCTION(sm_get_fan_policy_internal, sm_get_fan_policy_symbol)
LV2_FUNCTION(sm_set_fan_policy_internal, sm_set_fan_policy_symbol)

#endif
