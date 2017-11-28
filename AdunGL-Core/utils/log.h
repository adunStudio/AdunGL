//
// Created by ADUNGL on 2017. 11. 28..
//

#ifndef ADUNGLGL_LOG_H
#define ADUNGLGL_LOG_H

#include <iostream>

#define ADUNGL_LOG_LEVEL_FATAL 0
#define ADUNGL_LOG_LEVEL_ERROR 1
#define ADUNGL_LOG_LEVEL_WARN  2
#define ADUNGL_LOG_LEVEL_INFO  3

#ifndef ADUNGL_LOG_LEVEL
#define ADUNGL_LOG_LEVEL ADUNGL_LOG_LEVEL_INFO
#endif

#if ADUNGL_LOG_LEVEL >= ADUNGL_LOG_LEVEL_FATAL
#define ADUNGL_FATAL(x, ...) do { printf("[ADUNGL][FATAL]: "); printf(x, __VA_ARGS__); printf("\n"); ADUNGL_ASSERT(false, ""); } while(0)
#endif

#if ADUNGL_LOG_LEVEL >= ADUNGL_LOG_LEVEL_ERROR
#define ADUNGL_ERROR(x, ...) do { printf("[ADUNGL][ERROR]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#else
#define ADUNGL_ERROR(x, ...) {}
#endif

#if ADUNGL_LOG_LEVEL >= ADUNGL_LOG_LEVEL_WARN
#define ADUNGL_WARN(x, ...) do { printf("[ADUNGL][WARN]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#else
#define ADUNGL_WARN(x, ...) {}
#endif

#if ADUNGL_LOG_LEVEL >= ADUNGL_LOG_LEVEL_INFO
#define ADUNGL_INFO(x, ...) do { printf("[ADUNGL][INFO]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#else
#define ADUNGL_INFO(x, ...) {}
#endif


#endif //ADUNGLGL_LOG_H
