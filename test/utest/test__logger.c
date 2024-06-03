// The order of the includes are not trivial
// Son librerias de linux (de la plataforma que corre las pruebas)
#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

// Incluyo el .c para acceder a todo (lo publico y privado del modulo)
#include "../../src/logger.c"

// Internal auxiliary functions definitions
char mock_injection_writter(char *buff, int length)
{
    function_called();
    return 1;
}
// ------------------------------------------------------------

// Test cases
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

static void test__logger_init__get_logger_id(void **state)
{
    char logger_id;
    // Inicializo el modulo
    logger_module_init();
    
    // Acumulo los loggers habilitados (no deberia haber ninguno)
    logger_id = logger_ctor(mock_injection_writter);

    assert_int_equal(1, logger_id);
}

static void test__logger_init__make_one_log(void **state)
{
    log_t log;
    char logger_id, ret;

    // Test pre init
    expect_function_call(mock_injection_writter);

    // Inicializo el modulo
    logger_module_init();
    
    // Acumulo los loggers habilitados (no deberia haber ninguno)
    logger_id = logger_ctor(mock_injection_writter);

    // Preparo mensaje a loggear
    log.type = LOG_INFO;
    log.msg = "Si ya se";

    ret = logger_write(logger_id, &log);

    // Reviso log fue correcto
    assert_int_equal(1, ret);
}
// ------------------------------------------------------------

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test__logger_init__anyone_enabled),
        cmocka_unit_test(test__logger_init__get_logger_id),
        cmocka_unit_test(test__logger_init__make_one_log),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}