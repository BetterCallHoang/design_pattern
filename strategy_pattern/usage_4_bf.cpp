/*Trường hợp 4: Thay đổi cách sắp xếp (sorting strategy)*/
class Sorter {
public:
    void sort(int type) {
        if (type == 0)
            std::cout << "QuickSort\n";
        else if (type == 1)
            std::cout << "MergeSort\n";
    }
};