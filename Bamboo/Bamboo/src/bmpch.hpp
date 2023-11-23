#pragma once
#include "Bamboo/Core.hpp"

#include <future>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <cinttypes>
#include <limits.h>
#include <chrono>

#if defined(BAMBOO_SYSTEM_WINDOWS)
	#include <Windows.h>
#endif

#include "Core.hpp"
#include "Types.hpp"
#include "Logger.hpp"
#include "Timer.hpp"
#include "Bamboo/Log.hpp"
#include "Bamboo/Status.hpp"
#include "Bamboo/Viewport/CatchError.hpp"