#ifndef __SYS_LOGGER_H__
#define __SYS_LOGGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

// 获取当前时间的毫秒级时间戳

// 日志级别
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// 获取当前时间的毫秒级时间戳
#define getCurrentTimeMillis() \
    ({ \
        struct timeval tv; \
        gettimeofday(&tv, NULL); \
        (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000; \
    })

// 根据日志级别获取对应的字符串表示
#define getLogLevelString(level) \
    ((level == LOG_DEBUG) ? "DEBUG" : \
    (level == LOG_INFO) ? "INFO" : \
    (level == LOG_WARNING) ? "WARNING" : \
    (level == LOG_ERROR) ? "\x1B[1;31mERROR\x1B[0m" : "UNKNOWN")

// 从路径中提取文件名
const char* extractFileName(const char* path);

// 记录日志消息的宏
#define LOG_MESSAGE(level, format, ...) \
    do { \
        long long timestamp = getCurrentTimeMillis(); \
        time_t rawtime = (time_t)(timestamp / 1000); \
        struct tm* timeinfo = localtime(&rawtime); \
        char timeStr[30]; \
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo); \
        int milliseconds = (int)(timestamp % 1000); \
        const char* fileName = extractFileName(__FILE__);  \
        printf("[%s.%03d] [%s] [%s:%s:%d] " format "\n", \
                timeStr, milliseconds, getLogLevelString(level), \
                fileName, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)


#endif