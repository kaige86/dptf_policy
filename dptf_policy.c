#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "file_utils.h"
#include "policy.h"

#define INT3400_THERMAL "INT3400 Thermal"
#define THERMAL_ZONE_PREFIX "/sys/class/thermal/thermal_zone"
#define INT3400_AVA_UUIDS "/sys/bus/platform/devices/INT3400:00/uuids/available_uuids"
#define INT3400_CUR_UUID "/sys/bus/platform/devices/INT3400:00/uuids/current_uuid"

struct dptf_dev {
    char mode[MAX_LEN + 1];
    char *ava_policy;
    char *cur_policy;
    char *valid_policy[MAXIMUM_UUID];
} dev;

void dptf_help(void)
{
    printf("usage:\n");
    printf("  dptf_policy on/off                enable/disable dptf policy\n");
    printf("  dptf_policy <policy>              set current dptf policy\n\n");
}

void value_show(char *path)
{
    char buf[MAX_LEN + 1];
    int len;
    
    len = sys_file_cat(path, buf, MAX_LEN);
    if (len <= 0) {
        printf("read %s failed %d\n", path, len);
        return;
    }
    buf[len] = 0;
    printf("%s\n", buf);
}

char *curr_policy(void)
{
    char buf[MAX_LEN + 1];
    char *name;
    int len;
    
    len = sys_file_cat(dev.cur_policy, buf, MAX_LEN);
    if (len <= 0) {
        printf("read %s failed %d\n", dev.cur_policy, len);
        return "unkown";
    }
    buf[len] = 0;
    name = get_policy_name(buf);	
    if (!name) {
        printf("uuid: %s\n", buf);
        return "unknow";
    }
    return name;
}

void dptf_info(void)
{
    int i;
    char *uuid;

    printf("int3400 status:\n");
    value_show(dev.mode);

    printf("Current policy:\n");
    printf("%s\n\n", curr_policy());

    printf("int3400 available policys\n");
    printf("%-10s %-16s\n", "Policy", "UUID");
    for (i = 0; i < MAXIMUM_UUID; i++) {
        if (!dev.valid_policy[i])
            break;
        uuid = get_policy_uuid(dev.valid_policy[i]);
        if (uuid) {
            printf("%-10s %-16s\n", dev.valid_policy[i], uuid);
        }
    }
}

void dptf_on(void)
{
    (void)sys_file_write(dev.mode, "enabled");
}

void dptf_off(void)
{
    (void)sys_file_write(dev.mode, "disabled");
}

void dptf_ctrl(char *policy)
{
    (void)sys_file_write(dev.cur_policy, policy);
}

void dptf_show(void)
{
    dptf_info();
}

void dptf_mode(char *mode)
{
    char buf[MAX_LEN + 1];
    char path[MAX_LEN + 1];
    int len, i;

    for (i = 0; i < 32; i++) {
        (void)sprintf(path, "%s%d/type", THERMAL_ZONE_PREFIX, i);
        len = sys_file_cat(path, buf, MAX_LEN);
        if (len <= 0) {
            break;
        }
        buf[len] = 0;
        if (!strncmp(INT3400_THERMAL, buf, strlen(INT3400_THERMAL))) {
             (void)sprintf(path, "%s%d/mode", THERMAL_ZONE_PREFIX, i);
             (void)strncpy(mode, path, MAX_LEN);
             //printf("mode : %s\n", path);
             break;
        }
    }
}

void policy_ava(char *policy[])
{
    char buf[MAX_LEN + 1];
    char *name, *cur;
    int len, p;
    
    len = sys_file_cat(INT3400_AVA_UUIDS, buf, MAX_LEN);
    if (len <= 0) {
        printf("read %s failed %d\n", INT3400_AVA_UUIDS, len);
        return;
    }
    buf[len] = 0;
    cur = buf;
    p = 0;
    do {
        name = get_policy_name(cur);
        if (NULL != name)
            policy[p++] = name;
    } while ((cur = strstr(cur, "\n")) && cur++ && p < MAXIMUM_UUID);
}

void dptf_init(void)
{
    dptf_mode(dev.mode);
    policy_ava(dev.valid_policy);
    dev.ava_policy = INT3400_AVA_UUIDS;
    dev.cur_policy = INT3400_CUR_UUID;
    //printf("mode path: %s\n", dev.mode);
}

int main (int argc, char *argv[])
{
    char *uuid;
    int i;

    dptf_init();
    if (argc < 2) {
        dptf_help();
        dptf_show();
        return 0;
    }

    if (!strncmp(argv[1], "on", 2)) {
        dptf_on();
        dptf_show();
        return 0;
    }

    if (!strncmp(argv[1], "off", 3)) {
        dptf_off();
        dptf_show();
        return 0;
    }

    uuid = get_policy_uuid(argv[1]);

    if (NULL != uuid) {
        printf("Policy %s uuid %s\n", argv[1], uuid);
        dptf_off();
        dptf_ctrl(uuid);
        dptf_on();
        dptf_show();
    }
    else {
        printf("error, current available policy: \n");
        for (i = 0; i < MAXIMUM_UUID; i++) {
            if (!dev.valid_policy[i])
                break;
            printf("%s\n", dev.valid_policy[i]);
        }
    }
    return 0;
}
