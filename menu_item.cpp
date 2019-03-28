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

#include "menu_item.h"
#include "main.h"

menu_item::menu_item(const std::string& msg, const std::string& pmt, std::function<void()>* cb) : prompt(pmt),
    message(msg), callback(cb) {

    submenu_items = std::make_unique<std::vector<menu_item>>();

}

menu_item::menu_item(const std::string& msg, const std::string& pmt) {
    *this = menu_item(msg, pmt, nullptr);
}

menu_item::menu_item(const std::string& msg, std::function<void()>* cb) {
    *this = menu_item(msg, "", cb);
}

void menu_item::allocate(int items) {

    submenu_items->reserve((unsigned long)items);

}

void menu_item::setCallback(std::function<void()>* cb) { callback = cb; }
std::string menu_item::getMessage() const { return message; }

void menu_item::open() const {

    if (callback != nullptr) {
        (*callback)();
        return;
    }

    bool valid = false;
    int option = 0;
    while (!valid) {
        int count = 0;
        for (auto &item : *submenu_items) {

            print_sync(std::to_string(++count) + ". " + item.getMessage());

        }

        option = parse_int(get_input(prompt));

        if (option <= 0) {
            print_sync("Please enter a valid option!");
        } else {
            valid = true;
        }
    }

    (*submenu_items)[option - 1].open();

}

void menu_item::addSubItem(std::string msg, std::string pmt, std::function<void()>* cb) {
    submenu_items->emplace_back(msg, pmt, cb);
}

menu_item& menu_item::operator[](int index) {

    return (*submenu_items)[index];

}
