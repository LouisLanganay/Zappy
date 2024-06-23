#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(eject, check_no_eject)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {0, 5}, .orientation = SOUTH};
    ai_t ai2 = {.fd = 2, .pos = {5, 5}, .orientation = SOUTH};
    egg_t *egg = calloc(1, sizeof(egg_t));

    egg->pos.x = 5;
    egg->pos.y = 4;
    egg->id = 1;

    TAILQ_INIT(&server.ais);
    TAILQ_INIT(&server.eggs);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.eggs, egg, entries);

    cr_redirect_stdout();
    eject(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: ko\n");
}

Test(eject, check_eggs_destruction)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {0, 5}, .orientation = SOUTH};
    egg_t *egg = calloc(1, sizeof(egg_t));

    egg->pos.x = 0;
    egg->pos.y = 5;
    egg->id = 1;

    TAILQ_INIT(&server.ais);
    TAILQ_INIT(&server.eggs);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.eggs, egg, entries);

    cr_redirect_stdout();
    eject(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: ok\n");
}

Test(eject, check_basic_eject)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH};
    ai_t ai2 = {.fd = 2, .pos = {5, 5}, .orientation = SOUTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);

    cr_redirect_stdout();
    eject(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 2: eject: 5\n"
                            "To client 1: ok\n");
}

Test(eject, check_basic_eject_2)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = NORTH};
    ai_t ai2 = {.fd = 2, .pos = {5, 5}, .orientation = EAST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);

    cr_redirect_stdout();
    eject(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 2: eject: 7\n"
                            "To client 1: ok\n");
}

Test(eject, check_basic_eject_3)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = WEST};
    ai_t ai2 = {.fd = 2, .pos = {5, 5}, .orientation = SOUTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);

    cr_redirect_stdout();
    eject(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 2: eject: 3\n"
                            "To client 1: ok\n");
}

Test(eject, check_eject_alone)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    eject(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: ko\n");
}
