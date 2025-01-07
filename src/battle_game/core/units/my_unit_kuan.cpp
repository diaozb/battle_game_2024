#include "my_unit.h"
#include <cmath>

MyUnit::MyUnit() {
    // 初始化代码
    // 例如，设置初始位置、方向等
    this->setPosition(100, 100);  // 假设初始位置在 (100, 100)
    this->setDirection(0);  // 初始方向为0度
}

MyUnit::~MyUnit() {
    // 释放子弹资源
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void MyUnit::update() {
    // 更新单位状态
    if (currentCooldown > 0) {
        currentCooldown -= 0.016f;  // 假设每帧时间间隔为16毫秒
    }

    // 更新子弹状态
    for (Bullet* bullet : bullets) {
        bullet->update();
        if (bullet->isDead()) {
            delete bullet;
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
        }
    }
}

void MyUnit::draw() {
    // 绘制单位
    // 这里假设有一个绘制函数 drawSprite()，你需要根据实际的图形库实现
    drawSprite("tank_sprite.png", getPosition().x, getPosition().y, getDirection());
}

void MyUnit::move() {
    // 移动逻辑
    float dx = speed * std::cos(getDirection() * M_PI / 180.0f);
    float dy = speed * std::sin(getDirection() * M_PI / 180.0f);
    setPosition(getPosition().x + dx, getPosition().y + dy);
}

void MyUnit::shoot() {
    // 射击逻辑
    if (currentCooldown <= 0) {
        // 创建一个新的子弹
        Bullet* bullet = new Bullet(getPosition(), getDirection());
        bullets.push_back(bullet);
        currentCooldown = shootingCooldown;
    }
}