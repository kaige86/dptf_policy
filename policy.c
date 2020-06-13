#include <string.h>
#include "policy.h"

static struct thermal_def int340x_def[MAXIMUM_UUID] = {
    { "42A441D6-AE6A-462b-A84B-4A8CE79027D3", "passive1", "" },
    { "3A95C389-E4B8-4629-A526-C52C88626BAE", "active", "" },
    { "97C68AE7-15FA-499c-B8C9-5DA81D606E0A", "critical", "" },
    { "63BE270F-1C11-48FD-A6F7-3AF253FF3E2D", "adp_perf", "" },
    { "5349962F-71E6-431D-9AE8-0A635B710AEE", "emg_call", "" },
    { "9E04115A-AE87-4D1C-9500-0F3E340BFE75", "passive2", "" },
    { "F5A35014-C209-46A4-993A-EB56DE7530A1", "power_boss", "" },
    { "6ED722A7-9240-48A5-B479-31EEF723D7CF", "virt_sensor", "" },
    { "16CAF1B7-DD38-40ED-B1C1-1B8A1913D531", "cool", "" },
    { "BE84BABF-C4D4-403D-B495-3128FD44dAC1", "duty_clc", "" }
};

char *get_policy_name(char *uuid)
{
    int i;
    for (i = 0; i < MAXIMUM_UUID; i++) {
        if (!strncmp(int340x_def[i].uuid, uuid, strlen(int340x_def[i].uuid))) {
            return int340x_def[i].cmd;
        }
    }
    return NULL;
}

char *get_policy_uuid(char *name)
{
    int i;
    for (i = 0; i < MAXIMUM_UUID; i++) {
        if (!strncmp(int340x_def[i].cmd, name, strlen(int340x_def[i].cmd))) {
            return int340x_def[i].uuid;
        }
    }
    return NULL;
}
