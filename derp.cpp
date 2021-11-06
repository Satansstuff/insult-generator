#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <functional>
#include <array>
#include <ctime>
#include <cstdlib>
#include "httplib.hpp"
#include "json.hpp"

constexpr std::array<std::string_view, 6> arr = 
{{
    "\033[31m",
    "\033[32m",
    "\033[33m",
    "\033[34m",
    "\033[35m",
    "\033[36m",
}};
constexpr std::string_view reset = "\033[39m";
int main(int argc, char **argv)
{
    srand((unsigned)time(0));
    httplib::Client cl("https://evilinsult.com");
    std::string prev, full = "\n";
    for(;;)
    {
        auto res = cl.Get("/generate_insult.php?lang=en&type=json");
        auto jdump = nlohmann::json::parse(res->body);
        auto str = jdump["insult"];
        if(prev != str)
        {
            //std::cout << "\e[3J" << std::endl;
            prev = str;
            std::cout << arr.at((rand() % arr.size())) << str << reset << "\n\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //std::cout << full;
    return EXIT_SUCCESS;
}