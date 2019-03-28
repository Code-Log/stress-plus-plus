#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <functional>

class menu_item {

private:
    std::string message;
    std::string prompt;
    std::vector<menu_item>* submenu_items;
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
