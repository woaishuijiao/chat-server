#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>

namespace jiong {

pid_t GetThreadId();

u_int32_t GetFiberId();

}

#endif
