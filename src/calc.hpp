#pragma once

#include "part.hpp"
#include <vector>
#include <stdint.h>
#include <cmath>

typedef void (*calculations_func)(std::vector<pt>&);
extern calculations_func calculations; //black magic??

