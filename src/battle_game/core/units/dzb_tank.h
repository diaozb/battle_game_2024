#pragma once
#include "battle_game/core/unit.h"
#include "battle_game/core/input_data.h"

namespace battle_game {

class MyTank : public Unit {
public:
    MyTank(GameCore* game_core, uint32_t id, uint32_t player_id);
    
    void Render() override;
    void Update() override;
    [[nodiscard]] bool IsHit(glm::vec2 position) const override;
    
protected:
    [[nodiscard]] const char* UnitName() const override { return "tank1145"; }
    [[nodiscard]] const char* Author() const override { return "dzb 2024040156"; }
    
    [[nodiscard]] bool IsKeyPressed(int key) const;
    [[nodiscard]] bool IsMouseButtonPressed(int button) const;
    [[nodiscard]] glm::vec2 GetMousePosition() const;
    
private:
    float move_speed_ = 5.0f;
    float rotation_speed_ = 3.0f;
    float shoot_cooldown_ = 0.3f;
    float current_cooldown_ = 0.0f;
    float radius_ = 0.5f;
    float turret_rotation_ = 0.0f;  // 炮塔旋转角度
};

}  // namespace battle_game 