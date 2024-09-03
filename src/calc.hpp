#pragma once

#include "part.hpp"
#include <vector>
#include <stdint.h>
#include <cmath>
#include <thread>

typedef void (*calculations_func)(std::vector<pt>&);
extern calculations_func calculations; //black magic??
void calculationsv1(std::vector<pt>& pts);
void calculationsv2(std::vector<pt>& pts);
void calculationsv3(std::vector<pt>& pts);
void calculationsv4(std::vector<pt>& pts);

