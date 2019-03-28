#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <functional>
#include <string>

class menu_item {

private:
    std::string message;
    std::vector<menu_item>* submenu_items;
    std::function<void()> callback;

public:
    menu_item(const std::string& msg, const std::function<void()>& cb);
    menu_item(const std::string& msg);
    void setCallback(const std::function<void()>& cb);
    std::string getMessage() const;
    void open() const;
    void addSubItem(const std::string& msg, const std::function<void()> cb);
    ~menu_item();

};

#endif
