#include "logger.h"
#include <stdio.h>
#include <string.h>

// Defines
#define MAX_LOGGER_INSTANCES 1
#define MAX_LOG_MSG_LENGTH 256


// Internal data declaration
logger_t loggers[MAX_LOGGER_INSTANCES] = {};
const char *log_types_str[] = {"INFO", "WARNING", "ERROR", "SUCCESS"}; 

// Internal function definition


// External funtion definition
void logger_module_init()
{
    for(char i = 0; i < MAX_LOGGER_INSTANCES; i++)
    {
        loggers[i].enabled = 0;
        loggers[i].id = 0;
        loggers[i].writer = NULL;    
    }
}

char logger_ctor(logger_writer_func_t writer)
{
    for(char i = 0; i < MAX_LOGGER_INSTANCES; i++)
    {
        if(!loggers[i].enabled)
        {
            loggers[i].enabled = 1;
            loggers[i].id = i + 1;
            loggers[i].writer = writer;

            return loggers[i].id;
        }
    }

    return 0;
}

char logger_write(char logger_id, log_t *log)
{
    int length = 0;
    char buffer[MAX_LOG_MSG_LENGTH];

    if(loggers[logger_id - 1].enabled)
    {
        length = strlen(log->msg) + strlen("[WARNING]: ");

        if(length < MAX_LOG_MSG_LENGTH)
        {
            sprintf(buffer, "[%s]: %s", log_types_str[log->type], log->msg);
            loggers[logger_id - 1].writer(buffer, length);
            return 1;
        }

        return 0;
    }
    
    return -1;
}
//------------------------------------
