#include "SpyRuntimeError.h"


static const char *message = "No error";
static int parameter = -1;
static const char *file = 0;
static int line = -1;


void RuntimeError(const char *m, int p, const char *f, int l)
{
    message = m;
    parameter = p;
    file = f;
    line = l;
}

void SpyRuntimeError_Reset(void)
{
    message = "No error";
    parameter = -1;
}

const char *SpyRuntimeError_GetLastError(void) { return message; }

int SpyRuntimeError_GetLastParameter(void) { return parameter; }
