#ifndef MAIN_H
#define MAIN_H

#include <string>

enum MessageType {

    DEBUG,
    INFO,
    ERROR

};

int parse_int(const std::string& input);
std::string get_input(const std::string& prompt);
void print_sync(const std::string& msg);
void print_sync(const std::string& msg, const MessageType& type);

#endif
