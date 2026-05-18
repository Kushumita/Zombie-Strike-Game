#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

using namespace sf;

class Bullet {
    RectangleShape m_BulletShape;
    int            m_Speed = 300;
    Vector2f       m_Position;
    Vector2f       m_TargetPos;
    float          m_gradient;
    int            m_DirectionX = 1;
    int            m_DirectionY = 1;
    bool           inFight      = false;

    // float m_MaxX;
    // float m_MaxY;
    // float m_MinX;
    // float m_MinY;

  public:
    Bullet();
    void            shoot(Vector2f playerPos, Vector2f TargetPos);
    void            stop();
    bool            isInFight();
    RectangleShape &getShape();
    FloatRect       getBounds();
    void            update(Time dt);
};

Bullet::Bullet() {
    m_BulletShape.setSize(Vector2f(15, 20));
    m_BulletShape.setFillColor(Color::Red);
}
void Bullet::shoot(Vector2f playerPos, Vector2f TargetPos) {
    inFight     = true;
    m_Position  = playerPos;
    m_TargetPos = TargetPos;
    m_gradient  = (m_TargetPos.y - m_Position.y) / (m_TargetPos.x - m_Position.x);
    if (m_gradient < 0.0f)
        m_gradient *= -1;
    if (m_Position.x > m_TargetPos.x)
        m_DirectionX = -1;
    else
        m_DirectionX = 1;
    if (m_Position.y > m_TargetPos.y)
        m_DirectionY = -1;
    else
        m_DirectionY = 1;
}
bool            Bullet::isInFight() { return inFight; }
void            Bullet::stop() { inFight = false; }
RectangleShape &Bullet::getShape() { return m_BulletShape; }
FloatRect       Bullet::getBounds() { return m_BulletShape.getGlobalBounds(); }
void            Bullet::update(Time dt) {
    if (inFight) {
        m_Position.x += (m_DirectionX)*(1 / (1 + m_gradient)) * m_Speed * dt.asSeconds();
        m_Position.y += (m_DirectionY)*(m_gradient / (1 + m_gradient)) * m_Speed * dt.asSeconds();
    }
    if (m_Position.x < 0 || m_Position.x > 500 || m_Position.y < 0 || m_Position.y > 500) {
        inFight = false;
    }

    m_BulletShape.setPosition(m_Position);
}