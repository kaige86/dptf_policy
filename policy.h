
struct thermal_def {
    char *uuid;
    char *cmd;
    char *help;
};

enum int3400_th_uuid {
    PASSIVE_1,
    ACTIVE,
    CRITICAL, /* yes */
    ADAPTIVE_PERFORMANCE, /* yes */
    EMERGENCY_CALL_MODE,
    PASSIVE_2, /* yes */
    POWER_BOSS,
    VIRTUAL_SENSOR,
    COOLING_MODE,
    HARDWARE_DUTY_CYCLING,
    MAXIMUM_UUID,
};


char *get_policy_name(char *uuid);
char *get_policy_uuid(char *name);
