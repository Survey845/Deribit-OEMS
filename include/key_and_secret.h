#pragma once
#include <string>
#ifndef KEY_AND_SECRET_H
#define KEY_AND_SECRET_H

extern std::string api_key;
extern std::string api_secret;

void load_env();

#endif // KEY_AND_SECRET_H