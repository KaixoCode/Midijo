



#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifndef INITGUID
#define INITGUID
#endif

#include <mmeapi.h>

#undef min
#undef max

#include <vector>
#include <cassert>
#include <concepts>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>

#define LOGL(x) std::cout << x << std::endl
#define LOG(x) std::cout << x 

