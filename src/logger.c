#include <stdio.h>
#include "logger.h"

// Defines
#define MAX_LOG_MSG_LENGTH 42

// Internal data declaration
const char *log_types_str[] = {"INFO", "WARNING", "ERROR", "SUCCESS"}; 

// External funtion definition
char logger_write(log_t *log)
{
    printf("[%s]: %s", log_types_str[log->type], log->msg);
    return 1;
}
//------------------------------------
