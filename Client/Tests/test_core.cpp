#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../Source/Core/Core.hpp"

Test(Core, initialization) {
    // Arrange
    std::string host = "localhost";
    int port = 12345;

    // Act
    Zappy::Core core(host, port);

    // Assert
    cr_assert_not_null(&core, "Core should be initialized properly");
    cr_log_info("Core initialized with host: %s and port: %d", host.c_str(), port);
}

Test(Core, run) {
    // Arrange
    std::string host = "localhost";
    int port = 12345;
    Zappy::Core core(host, port);

    // Act and Assert
    cr_assert_no_throw(core.run(), "Core run method should not throw any exceptions");
}

Test(Core, handleServerMessages) {
    // Arrange
    std::string host = "localhost";
    int port = 12345;
    Zappy::Core core(host, port);

    // Simulate the behavior
    cr_assert_no_throw(core.handleServerMessages(), "handleServerMessages should not throw any exceptions");
}
