#ifndef MY_UNIT_H
#define MY_UNIT_H

#include "unit.h"

class MyUnit : public Unit {
public:
    MyUnit();
    ~MyUnit() override;

    // 重载必要的函数
    void update() override;
    void draw() override;
    void move() override;
    void shoot() override;

    // 重载 UnitName 和 Author 函数
    std::string UnitName() const override { return "MyUnit"; }
    std::string Author() const override { return "Kimi"; }
};
private:
    float speed = 5.0f;  // 移动速度
    float rotationSpeed = 5.0f;  // 旋转速度
    float shootingCooldown = 1.0f;  // 射击冷却时间
    float currentCooldown = 0.0f;  // 当前冷却时间
    std::vector<Bullet*> bullets;  // 存储子弹的列表
};

#endif // MY_UNIT_H