#include <iostream>
#include <memory>
#include <string>

class Character {
public:
    virtual std::string getName()   const = 0;
    virtual int getDefense()        const = 0;
    virtual std::string getEffect() const = 0;
    virtual ~Character() = default;
};

class Warrior : public Character {
public:
    std::string getName()   const override { return "Chiến Binh"; }
    int getDefense()        const override { return 10; }
    std::string getEffect() const override { return "Không có"; }
};

class ArmorDecorator : public Character {
protected:
    std::unique_ptr<Character> character;
public:
    ArmorDecorator(std::unique_ptr<Character> c) : character(std::move(c)) {}
};

class FireArmor : public ArmorDecorator {
public:
    FireArmor(std::unique_ptr<Character> c) : ArmorDecorator(std::move(c)) {}

    std::string getName()   const override { return character->getName() + " [Giáp Lửa]"; }
    int getDefense()        const override { return character->getDefense() + 15; }
    std::string getEffect() const override { return character->getEffect() + " + Phản sát thương lửa"; }
};

class IceArmor : public ArmorDecorator {
public:
    IceArmor(std::unique_ptr<Character> c) : ArmorDecorator(std::move(c)) {}

    std::string getName()   const override { return character->getName() + " [Giáp Băng]"; }
    int getDefense()        const override { return character->getDefense() + 12; }
    std::string getEffect() const override { return character->getEffect() + " + Làm chậm kẻ địch"; }
};

class PoisonArmor : public ArmorDecorator {
public:
    PoisonArmor(std::unique_ptr<Character> c) : ArmorDecorator(std::move(c)) {}

    std::string getName()   const override { return character->getName() + " [Giáp Độc]"; }
    int getDefense()        const override { return character->getDefense() + 8; }
    std::string getEffect() const override { return character->getEffect() + " + Gây độc kẻ địch"; }
};

void printCharacter(const Character& c) {
    std::cout << "Tên    : " << c.getName()   << "\n";
    std::cout << "Phòng  : " << c.getDefense() << "\n";
    std::cout << "Hiệu ứng: " << c.getEffect() << "\n";
    std::cout << "---\n";
}

int main() {
    // Chiến binh thường
    auto w = std::make_unique<Warrior>();
    printCharacter(*w);

    // Chiến binh + Giáp Lửa + Giáp Băng
    auto w2 = std::make_unique<IceArmor>(
                  std::make_unique<FireArmor>(
                      std::make_unique<Warrior>()));
    printCharacter(*w2);

    // Chiến binh + cả 3 giáp
    auto w3 = std::make_unique<PoisonArmor>(
                  std::make_unique<IceArmor>(
                      std::make_unique<FireArmor>(
                          std::make_unique<Warrior>())));
    printCharacter(*w3);
}
```

**Output:**
```
Tên    : Chiến Binh
Phòng  : 10
Hiệu ứng: Không có
---
Tên    : Chiến Binh [Giáp Lửa] [Giáp Băng]
Phòng  : 37
Hiệu ứng: Không có + Phản sát thương lửa + Làm chậm kẻ địch
---
Tên    : Chiến Binh [Giáp Lửa] [Giáp Băng] [Giáp Độc]
Phòng  : 45
Hiệu ứng: Không có + Phản sát thương lửa + Làm chậm kẻ địch + Gây độc kẻ địch
---