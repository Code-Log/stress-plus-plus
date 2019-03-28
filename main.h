#ifndef MAIN_H
#define MAIN_H

#include <string>

enum MessageType;

void print_sync(const std::string& msg);
void print_sync(const std::string& msg, const MessageType& type);

#endif
