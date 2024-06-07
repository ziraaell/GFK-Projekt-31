#pragma once

//class Player {
//public:
//    Player() : pos_x(0.0), pos_y(0.0), angle(0.0), speed(0.0), turnSpeed(0.0){}
//    Player(float p_x, float p_y, float p_a, float p_s, float p_ts) : pos_x(p_x), pos_y(p_y), angle(p_a), speed(p_s), turnSpeed(p_ts) {}
//    void SetPlayerPosition(float x, float y) {
//        pos_x = x;
//        pos_y = y;
//    }
//    float GetAngle() const { return angle; }
//    float GetX() const { return pos_x; }
//    float GetY() const { return pos_y; }
//    //float GetAngle() const { return angle; }
//    float GetSpeed() const { return speed; }
//    //float GetIsRunning() const { return isRunning; }
//    float GetTurnSpeed() const { return turnSpeed; }
//
//    void SetAngle(float new_angle) { angle = new_angle; }
//
//private:
//    float pos_x, pos_y;
//    float angle;
//    float speed;
//    float turnSpeed;
//    //bool isRunning;
//};

struct Player {
    float pos_x, pos_y;
    float angle;
    float speed;
    float turnSpeed;
    bool isRunning;
};