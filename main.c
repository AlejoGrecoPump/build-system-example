#include "logger.h"

int main(int argc, char **argv)
{
    log_t log;
    char greeting[] = "Hola mundo!\n";

    log.type = LOG_INFO;
    log.msg = greeting;
    
    logger_write(&log);
    return 0;
}