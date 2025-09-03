#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdint>
#include <string>

#include "utils/protection/encrypter.h"
#include "utils/auth/auth.hpp"
using namespace KeyAuth;
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);
void sessionStatus();

std::string name = skCrypt("name").decrypt();
std::string ownerid = skCrypt("ownerid").decrypt();
std::string version = skCrypt("1.0").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
std::string path = skCrypt("").decrypt();

api KeyAuthApp(name, ownerid, version, url, path);

void sessionStatus() {
    KeyAuthApp.check(true);
    if (!KeyAuthApp.response.success) {
        exit(0);
    }

    if (KeyAuthApp.response.isPaid) {
        for (;;) {
            Sleep(20000);
            KeyAuthApp.check();
            if (!KeyAuthApp.response.success) {
                exit(0);
            }
        }
    }
}

void checkAuthenticated(std::string ownerid) {
    for (;;) {
        if (GlobalFindAtomA(ownerid.c_str()) == 0) {
            exit(13);
        }
        Sleep(1000);
    }
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}