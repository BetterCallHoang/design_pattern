/*Không muốn dùng kế thừa vì gây bùng nổ class*/
#include <iostream>

class Warrior { };

// Phải tạo class cho mọi tổ hợp
class FireWarrior      : public Warrior { }; // giáp lửa
class IceWarrior       : public Warrior { }; // giáp băng
class FireIceWarrior   : public Warrior { }; // giáp lửa + băng
class FirePoisonWarrior: public Warrior { }; // giáp lửa + độc
class IcePoisonWarrior : public Warrior { }; // giáp băng + độc
class FireIcePoisonWarrior : public Warrior {}; // lửa + băng + độc
// 3 loại giáp → 7 class tổ hợp
// 4 loại giáp → 15 class tổ hợp
// n loại giáp → 2^n - 1 class  ← thảm họa