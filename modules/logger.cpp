module;

#include <iostream>

export module logger;

export namespace logger {
    void log() {
                std::cout << "logging...\n";

    }
}
