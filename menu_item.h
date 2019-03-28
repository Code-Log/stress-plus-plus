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

#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <functional>
#include <memory>

class menu_item {

private:
    std::string message;
    std::string prompt;
    std::unique_ptr<std::vector<menu_item>> submenu_items;
    std::function<void()>* callback;

public:
    menu_item(const std::string& msg, const std::string& pmt, std::function<void()>* cb);
    menu_item(const std::string& msg, const std::string& pmt);
    menu_item(const std::string& msg, std::function<void()>* cb);
    void setCallback(std::function<void()>* cb);
    std::string getMessage() const;
    void open() const;
    void addSubItem(std::string msg, std::string pmt, std::function<void()>* cb);
    void allocate(int items);

    menu_item& operator[](int index);

};

#endif
