#ifndef LOGGER__H
#define LOGGER__H

// External data definition
typedef enum {
    LOG_INFO = 0,
    LOG_WARNING,
    LOG_ERROR,
    LOG_SUCCESS
}log_gravity_t;

typedef struct {
    log_gravity_t type;
    char *msg;
}log_t;
//------------------------------------

// External function declaration
char logger_write(log_t *log);
//------------------------------------

#endif /* LOGGER__H */