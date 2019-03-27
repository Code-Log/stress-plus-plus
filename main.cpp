/*

    A lightweight program for stress-testing the CPU.
    Copyright (C) 2019  Jaco Malan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <thread>
#include <string.h>
#include <sstream>
#include <mutex>
#include <vector>
#include <signal.h>

#define COLOR_ERROR "\u001b[31m"
#define COLOR_WARN "\u001b[38:5:202m"
#define COLOR_INFO "\u001b[92m"
#define COLOR_ENDC "\u001b[0m"

std::mutex mu;
int thread_num = 0;
int max_threads = 0;
bool should_exit = false;
std::vector<std::thread> handles;
bool can_exit = false;
std::vector<std::string> menuItems;

enum MessageType {

    DEBUG,
    INFO,
    ERROR

};

std::string get_input(const char* prompt) {

    std::string input;
    std::cout << prompt;
    std::cin >> input;

    return input;

}

int parse_int(const std::string& input) {

    int result = 0;
    std::stringstream stream(input);
    stream >> result;

    return result;

}

inline int ack(int m, int n) {

    if (should_exit) { return 0; }

    if (m == 0) { return n + 1; }
    else if (m > 0 && n == 0) { return ack(m - 1, 1); }
    else if (m > 0 && n > 0) { return ack(m - 1, ack(m, n - 1)); }

    return 0;

}

void print_sync(const std::string& msg) {

    std::lock_guard<std::mutex> lg(mu);
    std::cout << msg << std::endl;
    mu.unlock();

}

void print_sync(const std::string& msg, MessageType type) {

    std::string cmsg;

    switch (type) {

        case INFO:
            cmsg = COLOR_INFO;
            break;

        case DEBUG:
            cmsg = COLOR_WARN;
            break;

        case ERROR:
            cmsg = COLOR_ERROR;
            break;

        default:
            cmsg = COLOR_INFO;
            break;
    }

    cmsg += msg;
    cmsg += COLOR_ENDC;

    print_sync(cmsg);

}

void do_work() {

    std::lock_guard<std::mutex> guard(mu);
    int this_thread = thread_num;
    thread_num++;
    mu.unlock();

    std::string msg = "Thread " + std::to_string(this_thread) + " started!";
    print_sync(msg, INFO);

    int run = 0;
    while (!should_exit || run < 4) {

        int m = this_thread + thread_num * run;

        for (int i = 0; i < 10; i++)
            ack(m, i);

        msg = "[" + std::to_string(this_thread) + "]: Run " + std::to_string(run + 1) + " completed!";
        print_sync(msg, DEBUG);
        run++;

    }

}

void sigint_receive(int signum) {

    print_sync(std::string("\n[") + std::to_string(signum) + "]:SIGINT: Waiting for threads to exit...\n", INFO);
    should_exit = true;

    for (std::thread& handle : handles) {
        handle.join();
    }

    print_sync("All threads exited...", INFO);
    can_exit = true;

}

int main(int argc, const char** argv) {

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "  Stress++ (v0.1.1)" << std::endl;
    std::cout << "      Copyright (C) 2019  Jaco Malan" << std::endl;
    std::cout << "----------------------------------------\n" << std::endl;

    menuItems.reserve(2);
    menuItems.emplace_back("Start stress test");
    menuItems.emplace_back("Exit");

    while (true) {

        // TODO: Add more options.

        for (int i = 0; i < menuItems.size(); i++)
            print_sync(std::to_string(i + 1) + ". " + menuItems[i]);

        std::cout << std::endl;

        int option = parse_int(get_input("Please select an option: "));

        if (option <= 0 || option > menuItems.size()) {

            print_sync("Please enter a valid option!");
            return -1;

        }

        if (option == 1) {

            max_threads = std::thread::hardware_concurrency();
            std::cout << "Starting 4 rounds of Ackermann stress-testing..." << std::endl;
            std::cout << "Press Ctrl-C to stop the test at any time...\n" << std::endl;

            std::cout << "Initializing " << max_threads << " threads..." << std::endl;
            handles.reserve((unsigned long)max_threads);
            for (int i = 0; i < max_threads; i++) {

                print_sync("Starting thread " + std::to_string(i) + "...", INFO);
                handles.emplace_back(do_work);

            }

            struct sigaction sigint_handler {};

            sigint_handler.sa_handler = sigint_receive;
            sigemptyset(&sigint_handler.sa_mask);
            sigint_handler.sa_flags = 0;

            sigaction(SIGINT, &sigint_handler, nullptr); // Dynamically create the callback for SIGINT

            while (!can_exit) {} // Just spin until this flag is set.

        } else {
            break;
        }

    }

    return 0;

}
