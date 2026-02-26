/*Trường hợp 2: UI Menu nhiều cấp*/
/*🔴 Rất nhanh sẽ thành rối khi menu lồng nhiều cấp*/
class MenuItem {
public:
    void click() {
        std::cout << "Execute action\n";
    }
};

class MenuGroup {
public:
    std::vector<MenuItem*> items;
    std::vector<MenuGroup*> groups;

    void show() {
        // phải xử lý riêng item và group
    }
};