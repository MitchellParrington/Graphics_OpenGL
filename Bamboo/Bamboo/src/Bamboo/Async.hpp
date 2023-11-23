#pragma once
#include "bmpch.hpp"

#define ASYNC(func, ...) std::async(std::launch::async, func, ##__VA_ARGS__)