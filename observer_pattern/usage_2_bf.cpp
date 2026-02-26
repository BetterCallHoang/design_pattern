#include <iostream>

// Player phải biết và giữ trực tiếp từng hệ thống
class UISystem {
public:
    void showGameOver() {
        std::cout << "[UI] Hiển thị màn hình Game Over\n";
    }
};

class SoundSystem {
public:
    void playFailMusic() {
        std::cout << "[Sound] Phát nhạc thất bại\n";
    }
};

class AchievementSystem {
public:
    void unlockFirstDeath() {
        std::cout << "[Achievement] Mở khóa: 'Chết lần đầu'\n";
    }
};

class Player {
    // Gắn cứng – Player phải include và biết tất cả các hệ thống
    UISystem ui;
    SoundSystem sound;
    AchievementSystem achievement;

public:
    void die() {
        std::cout << "Nhân vật đã chết!\n\n";

        // Muốn thêm AnalyticsSystem, SaveSystem... → phải vào đây sửa
        // Mỗi lần thêm hệ thống mới → Player phải compile lại
        ui.showGameOver();
        sound.playFailMusic();
        achievement.unlockFirstDeath();
    }
};

int main() {
    Player player;
    player.die();
}