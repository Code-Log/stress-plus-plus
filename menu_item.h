#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <functional>
#include <string>

class menu_item {

private:
    std::string message;
    std::string prompt;
    std::vector<menu_item>* submenu_items;
    std::function<void()> callback;

public:
    menu_item(const std::string& msg, const std::string& pmt, const std::function<void()>& cb);
    menu_item(const std::string& msg, const std::string& pmt);
    menu_item(const std::string& msg, const std::function<void()>& cb);
    void setCallback(const std::function<void()>& cb);
    std::string getMessage() const;
    void open() const;
    void addSubItem(const std::string& msg, const std::string& pmt, const std::function<void()>& cb);
    ~menu_item();

    menu_item& operator[](int index);

};

#endif
