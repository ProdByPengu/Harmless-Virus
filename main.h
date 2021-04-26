#pragma once

#include <windows.h>
#include <iostream>
#include <cassert>
#include <thread>
#include <random>
#include <chrono>
#include <string>
#include <ctime>

#include "xorstr.h"

using namespace std::chrono_literals;

namespace random {
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>( std::time( nullptr ) ) };
}

namespace config {
    static bool do_mousejitter = false,
        do_browser = false,
        browser_opened = false;

    static int do_scare = 0,
        do_scare_min = 1,
        do_scare_max = 3;
}

namespace launch {
    namespace thread {
        extern auto main( ),
            mousejitter( ),
            browser( );
    }
}

namespace console {
    extern void log( std::string input );

    namespace text {
        extern void color( int code );
    }
}