#pragma once

#include <string>
#include "ASM.h"
#include "DIS.h"

std::string asm_all(std::string file_addr);
std::string dis_all(std::string file_addr);