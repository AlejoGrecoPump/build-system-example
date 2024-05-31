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

typedef char (*logger_writer_func_t)(char *data, int length);

typedef struct {
    char id;
    char enabled;
    logger_writer_func_t writer;
}logger_t;
//------------------------------------

// External function declaration
void logger_module_init();
char logger_ctor(logger_writer_func_t writer);
char logger_write(char logger_id, log_t *log);
//------------------------------------

#endif /* LOGGER__H */