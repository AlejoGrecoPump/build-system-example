// The order of the includes are not trivial
// Son librerias de linux (de la plataforma que corre las pruebas)
#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

// Incluyo el .c para acceder a todo (lo publico y privado del modulo)
#include "../../src/logger.c"

static void test__logger_init__anyone_enabled(void **state)
{
    int res = 0;
    // Inicializo el modulo
    logger_module_init();
    
    // Acumulo los loggers habilitados (no deberia haber ninguno)
    for(char i = 0; i < MAX_LOGGER_INSTANCES; i++)
    {
        res += loggers[i].enabled;
    }

    assert_int_equal(0, res);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test__logger_init__anyone_enabled),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}