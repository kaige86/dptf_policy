#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "file_utils.h"
#include "policy.h"

int sys_file_write(char *file_name, char *value)
{
    int fd;
    size_t l;
    ssize_t r;
    fd = open(file_name, O_WRONLY);
    if (fd < 0) {
        printf("open file %s error %d!\n", file_name, fd);
        return fd;
    }
    l = strnlen(value, MAX_LEN);
    r = write(fd, value, l);
    (void)close(fd);
    if ((size_t)r != l) {
        printf("write ret %ld != %ld\n", r, l);
        return -1L;
    }
    return 0;
}

int sys_file_cat(char *file_name, char *buf, int len)
{
    int fd;
    ssize_t r;

    fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        printf("open file %s error %d!\n", file_name, fd);
        return fd;
    }
    r = read(fd, buf, len);
    (void)close(fd);
    if ((size_t)r <= 0) {
        printf("read ret %ld\n", r);
        return -1L;
    }
    buf[r] = 0;
 
    return r;
}

