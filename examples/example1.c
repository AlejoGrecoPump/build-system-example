#include "logger.h"
#include <stdio.h>

char app_writter(char *buff, int length);

int main(int argc, char **argv)
{
    log_t log;
    char logger_id;
    char greeting[] = "Hola mundo!\n";

    log.type = LOG_INFO;
    log.msg = greeting;
    
    // Inicializo el modulo
    logger_module_init();
    // Creo instancia para uso de la app
    logger_id = logger_ctor(app_writter);
    // Escribo un log
    logger_write(logger_id, &log);
    return 0;
}

char app_writter(char *buff, int length)
{
    printf("%s", "APP FUNTION WRITER \n");
    return (char)printf("%s", buff);
}