
#include "error.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static const char *error_log_progname;
static enum loglevel loglevel = WARN;

static void error_log(unsigned char status, int errnum, const char *message_format, va_list args) {
    fprintf(stderr, "%s: ", error_log_progname);

    vfprintf(stderr, message_format, args);

    if (errnum) {
        const char *error_string = strerror(errnum);
        fprintf(stderr, ": %s", error_string ? error_string : "Unknown system error");
    }

    putc('\n', stderr);

    if (status)
        exit(status);
}

void log_set_progname(const char *progname) {
    error_log_progname = progname;
}

const char *log_get_progname(void) {
    return error_log_progname;
}

void log_increase_level() {
    if (loglevel != SILENT)
        ++loglevel;
}

void log_silence() {
    loglevel = SILENT;
}

enum loglevel log_get_loglevel() {
    return loglevel;
}

void log_info(const char *message_format, ...) {
    if (loglevel >= INFO) {
        va_list args;

        va_start(args, message_format);
        error_log(0, 0, message_format, args);
        va_end(args);
    }
}

void log_warn(const char *message_format, ...) {
    if (loglevel >= WARN) {
        va_list args;

        va_start(args, message_format);
        error_log(0, 0, message_format, args);
        va_end(args);
    }
}

void log_error(const char *message_format, ...) {
    if (loglevel >= ERROR) {
        va_list args;

        va_start(args, message_format);
        error_log(0, 0, message_format, args);
        va_end(args);
    }
}

void log_debug(const char *message_format, ...) {
    if (loglevel >= DEBUG) {
        va_list args;

        va_start(args, message_format);
        error_log(0, 0, message_format, args);
        va_end(args);
    }
}

void die(unsigned char status, int errnum, const char *message_format, ...) {
    va_list args;

    va_start(args, message_format);
    error_log(status, errnum, message_format, args);
    va_end(args);
}
