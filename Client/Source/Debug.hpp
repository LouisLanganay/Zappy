/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Debug
*/


#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

#define COLOR_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_RED "\033[1;31m"
#define COLOR_RESET "\033[0m"

#define DEBUG_SUCCESS(message) DEBUG_LOG("success", message)
#define DEBUG_INFO(message) DEBUG_LOG("info", message)
#define DEBUG_ERROR(message) DEBUG_LOG("error", message)


#define DEBUG_LOG(type, message) do { \
    static std::string prev_message; \
    static long long int message_count = 1; \
    auto t = std::time(nullptr); \
    auto tm = *std::localtime(&t); \
    std::ostringstream oss; \
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); \
    std::string formatted_message = message; \
    std::replace(formatted_message.begin(), formatted_message.end(), '\n', ' '); \
    if (formatted_message != prev_message) { \
        if (message_count > 1) { \
            std::cout << " (x" << message_count << ")" << std::endl; \
        } else if (message_count == 1) { \
            std::cout << std::endl; \
        } \
        prev_message = formatted_message; \
        message_count = 1; \
        std::cout << "[" << oss.str() << "] "; \
        if (type == "success") { \
            std::cout << COLOR_GREEN << "[SUCCESS] "; \
        } else if (type == "info") { \
            std::cout << "[INFO] "; \
        } else if (type == "error") { \
            std::cout << COLOR_RED << "[ERROR] "; \
        } \
        std::cout << formatted_message; \
    } else { \
        ++message_count; \
        std::cout << "\r\x1B[K[" << oss.str() << "] "; \
        if (type == "success") { \
            std::cout << COLOR_GREEN << "[SUCCESS] "; \
        } else if (type == "info") { \
            std::cout << "[INFO] "; \
        } else if (type == "error") { \
            std::cout << COLOR_RED << "[ERROR] "; \
        } \
        std::cout << formatted_message << " (x" << message_count << ")" << std::flush; \
    } \
    std::cout << COLOR_RESET << std::flush; \
} while (0)

#endif /* !DEBUG_HPP_ */
