#include "menu_item.h"

menu_item::menu_item(const std::string& msg, const std::function<void()>& cb) : message(msg), callback(cb) {

    submenu_items = new std::vector<menu_item>();

}

menu_item::menu_item(const std::string& msg) {
    menu_item(msg, nullptr);
}

menu_item::~menu_item() {

    delete submenu_items;

}

void menu_item::setCallback(const std::function<void()>& cb) { callback = cb; }
std::string menu_item::getMessage() const { return message; }

void menu_item::open() const {

}

void menu_item::addSubItem(const std::string& msg, const std::function<void()> cb) {

    submenu_items->emplace_back(msg, cb);

}
