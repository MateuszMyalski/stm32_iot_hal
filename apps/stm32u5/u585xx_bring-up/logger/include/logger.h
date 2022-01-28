#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifndef _LOGGER_PRINTF
#define _LOGGER_PRINTF(...) printf(__VA_ARGS__)
#endif // _LOGGER_PRINTF

#ifndef LOGGER_NO_LOGS
#define LOG_INFO(...) _LOGGER_PRINTF(__VA_ARGS__)
#else
#define LOG_INFO(...) (...)
#endif // LOGGER_NO_LOGS

#ifndef LOGGER_NO_LOGS
#define LOG_WARN(fmt, ...) _LOGGER_PRINTF("#ORG#" fmt, ##__VA_ARGS__)
#else
#define LOG_WARN(...) (...)
#endif // LOGGER_NO_LOGS

#ifndef LOGGER_NO_LOGS
#define LOG_ERR(fmt, ...) _LOGGER_PRINTF("#RED#" fmt, ##__VA_ARGS__)
#else
#define LOG_ERR(...) (...)
#endif // LOGGER_NO_LOGS

#ifndef LOGGER_NO_LOGS
#define LOG_SUCCESS(fmt, ...) _LOGGER_PRINTF("#GRN#" fmt, ##__VA_ARGS__)
#else
#define LOG_SUCCESS(...) (...)
#endif // LOGGER_NO_LOGS

#endif
