#include "dzb_tank.h"
#include "battle_game/core/bullets/cannon_ball.h"
#include "battle_game/core/game_core.h"

namespace battle_game {

MyTank::MyTank(GameCore* game_core, uint32_t id, uint32_t player_id)
    : Unit(game_core, id, player_id) {
    health_ = 1.0f;
    radius_ = 0.5f;
}

void MyTank::Render() {
    SetTexture(BATTLE_GAME_ASSETS_DIR "textures/particle3.png");
    
    // 军绿色
    glm::vec4 tank_color = glm::vec4{0.33f, 0.42f, 0.18f, 1.0f};
    auto player_color = game_core_->GetPlayerColor(GetPlayerId());
    tank_color = tank_color * 0.7f + player_color * 0.3f;
    
    // 渲染坦克履带
    SetColor(glm::vec4{0.2f, 0.2f, 0.2f, 1.0f});
    // 左履带
    SetTransformation(position_ + glm::vec2{cos(rotation_ + glm::radians(90.0f)), 
                                          sin(rotation_ + glm::radians(90.0f))} * 0.7f,
                     rotation_, glm::vec2{1.2f, 0.2f});
    DrawModel(0);
    // 右履带
    SetTransformation(position_ + glm::vec2{cos(rotation_ - glm::radians(90.0f)), 
                                          sin(rotation_ - glm::radians(90.0f))} * 0.7f,
                     rotation_, glm::vec2{1.2f, 0.2f});
    DrawModel(0);
    
    // 渲染六边形主体
    SetColor(tank_color);

    // 主装甲板（中央主体）
    SetTransformation(position_, rotation_, glm::vec2{1.2f, 0.8f});
    DrawModel(0);

    // 装甲板装饰线条（深色）
    SetColor(tank_color * 0.7f);
    // 水平装饰线
    SetTransformation(position_, rotation_, glm::vec2{1.1f, 0.05f});
    DrawModel(0);
    SetTransformation(position_ + glm::vec2{0.0f, 0.2f}, rotation_, glm::vec2{1.1f, 0.05f});
    DrawModel(0);
    SetTransformation(position_ - glm::vec2{0.0f, 0.2f}, rotation_, glm::vec2{1.1f, 0.05f});
    DrawModel(0);

    // 前部斜面装甲
    SetColor(tank_color * 0.9f);
    // 左前装甲板
    SetTransformation(
        position_ + glm::vec2{cos(rotation_), sin(rotation_)} * 0.6f,
        rotation_ + glm::radians(30.0f),
        glm::vec2{0.4f, 0.8f}
    );
    DrawModel(0);
    // 右前装甲板
    SetTransformation(
        position_ + glm::vec2{cos(rotation_), sin(rotation_)} * 0.6f,
        rotation_ - glm::radians(30.0f),
        glm::vec2{0.4f, 0.8f}
    );
    DrawModel(0);

    // 装甲板连接处装饰（高光）
    SetColor(tank_color * 1.1f);
    // 前部连接处
    SetTransformation(
        position_ + glm::vec2{cos(rotation_), sin(rotation_)} * 0.6f,
        rotation_,
        glm::vec2{0.1f, 0.7f}
    );
    DrawModel(0);

    // 后部斜面装甲
    SetColor(tank_color * 0.85f);  // 稍暗一些
    // 左后装甲板
    SetTransformation(
        position_ - glm::vec2{cos(rotation_), sin(rotation_)} * 0.6f,
        rotation_ + glm::radians(150.0f),
        glm::vec2{0.4f, 0.8f}
    );
    DrawModel(0);
    // 右后装甲板
    SetTransformation(
        position_ - glm::vec2{cos(rotation_), sin(rotation_)} * 0.6f,
        rotation_ - glm::radians(150.0f),
        glm::vec2{0.4f, 0.8f}
    );
    DrawModel(0);

    // 后部连接处装饰
    SetTransformation(
        position_ - glm::vec2{cos(rotation_), sin(rotation_)} * 0.6f,
        rotation_,
        glm::vec2{0.1f, 0.7f}
    );
    DrawModel(0);
    
    // 渲染炮塔底座（较大的圆形）
    SetColor(tank_color * 0.9f);
    SetTransformation(position_, turret_rotation_, glm::vec2{0.7f, 0.7f});
    DrawModel(0);
    
    // 渲染炮塔主体（中等圆形）
    SetColor(tank_color * 0.8f);
    SetTransformation(position_, turret_rotation_, glm::vec2{0.6f, 0.6f});
    DrawModel(0);
    
    // 渲染炮管
    // 炮管底座（圆形）
    SetTransformation(
        position_ + glm::vec2{cos(turret_rotation_), sin(turret_rotation_)} * 0.4f,
        turret_rotation_,
        glm::vec2{0.2f, 0.2f}
    );
    DrawModel(0);
    // 炮管主体（细长矩形）
    SetTransformation(
        position_ + glm::vec2{cos(turret_rotation_), sin(turret_rotation_)} * 0.7f,
        turret_rotation_,
        glm::vec2{0.8f, 0.15f}
    );
    DrawModel(0);
    // 炮管前端（制退器）
    // 主体部分（扁平矩形）
    SetTransformation(
        position_ + glm::vec2{cos(turret_rotation_), sin(turret_rotation_)} * 1.3f,
        turret_rotation_,
        glm::vec2{0.2f, 0.2f}  // 正方形形状
    );
    DrawModel(0);
    // 前端装饰（扁平矩形）
    SetTransformation(
        position_ + glm::vec2{cos(turret_rotation_), sin(turret_rotation_)} * 1.4f,
        turret_rotation_,
        glm::vec2{0.1f, 0.18f}  // 略扁的矩形
    );
    DrawModel(0);
}

void MyTank::Update() {
    auto& input_data = game_core_->GetPlayer(player_id_)->GetInputData();
    
    // 处理移动
    glm::vec2 new_position = position_;
    if (input_data.key_down['W']) {
        new_position += glm::vec2(cos(rotation_), sin(rotation_)) * 
                       move_speed_ * kSecondPerTick;
    }
    if (input_data.key_down['S']) {
        new_position -= glm::vec2(cos(rotation_), sin(rotation_)) * 
                       move_speed_ * kSecondPerTick;
    }
    
    // 检查新位置是否有效
    if (!game_core_->IsBlockedByObstacles(new_position) && 
        !game_core_->IsOutOfRange(new_position)) {
        game_core_->PushEventMoveUnit(id_, new_position);
    }
    
    // 处理旋转
    float rotation_offset = 0.0f;
    if (input_data.key_down['A']) {
        rotation_offset += rotation_speed_ * kSecondPerTick;
    }
    if (input_data.key_down['D']) {
        rotation_offset -= rotation_speed_ * kSecondPerTick;
    }
    game_core_->PushEventRotateUnit(id_, rotation_ + rotation_offset);
    
    // 更新炮塔旋转 - 始终朝向鼠标
    auto mouse_pos = input_data.mouse_cursor_position;
    auto direction = mouse_pos - position_;
    if (glm::length(direction) < 1e-4) {
        turret_rotation_ = rotation_;  // 如果鼠标在坦克位置，保持炮塔与车身同向
    } else {
        turret_rotation_ = std::atan2(direction.y, direction.x);
    }
    
    // 处理射击冷却
    if (current_cooldown_ > 0) {
        current_cooldown_ -= kSecondPerTick;
    }
    
    // 处理射击
    if ((input_data.mouse_button_down[0] || input_data.mouse_button_down[1]) && 
        current_cooldown_ <= 0) {
        current_cooldown_ = shoot_cooldown_;
        
        auto bullet_direction = glm::normalize(direction);
        auto bullet_speed = 30.0f;
        
        // 从炮管前端发射
        auto bullet_pos = position_ + bullet_direction * 1.4f;
        
        // 发射主炮弹（左键和右键都会发射）
        GenerateBullet<bullet::CannonBall>(
            bullet_pos,
            turret_rotation_,
            1.5f,
            bullet_direction * bullet_speed
        );
        
        // 右键点击时额外发射副炮弹
        if (input_data.mouse_button_down[1]) {
            float spread_angle = 0.1f;  // 扩散角度
            glm::vec2 left_dir = glm::vec2{
                cos(turret_rotation_ + spread_angle),
                sin(turret_rotation_ + spread_angle)
            };
            glm::vec2 right_dir = glm::vec2{
                cos(turret_rotation_ - spread_angle),
                sin(turret_rotation_ - spread_angle)
            };
            
            // 左侧子弹
            GenerateBullet<bullet::CannonBall>(
                bullet_pos + glm::vec2{-bullet_direction.y, bullet_direction.x} * 0.2f,
                turret_rotation_ + spread_angle,
                0.5f,  // 副炮伤害较小
                left_dir * (bullet_speed * 0.8f)  // 副炮速度较慢
            );
            
            // 右侧子弹
            GenerateBullet<bullet::CannonBall>(
                bullet_pos + glm::vec2{bullet_direction.y, -bullet_direction.x} * 0.2f,
                turret_rotation_ - spread_angle,
                0.5f,
                right_dir * (bullet_speed * 0.8f)
            );
        }
    }
}

bool MyTank::IsHit(glm::vec2 position) const {
    return glm::length(position - position_) <= radius_;
}

}  // namespace battle_game 