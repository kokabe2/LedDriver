#pragma once


void RuntimeError(const char *message, int paramter, const char *file,
                  int line);
#define RUNTINE_ERROR(description, parameter) \
    RuntimeError(description, parameter, __FILE__, __LINE__)
