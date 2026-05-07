#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Zombie {
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED  = 80;
    const float CRAWLER_SPEED = 20;

    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH  = 1;
    const float CRAWLER_HEALTH = 3;

    const int MAX_VARIANCES = 30;

    Vector2f m_Position;
    float    m_Speed;
    float    m_Health;
    Sprite   m_Sprite;
    Texture textureZombie;

  public:
    void spawn(int x, int y, int type,int seed);
    Sprite& getSprite();
    FloatRect getBounds();
    Vector2f getPosition();
    void update(Time dt,Vector2f playerPos);
};
void Zombie::spawn(int x, int y, int type, int seed) {
    switch (type) {
    case 0: // Bloater
        m_Speed  = BLOATER_SPEED;
        m_Health = BLOATER_HEALTH;
        textureZombie.loadFromFile("graphics/bloater.png");
        m_Sprite.setTexture(textureZombie);
        break;
    case 1:
        m_Speed  = CHASER_SPEED;
        m_Health = CHASER_HEALTH;
        textureZombie.loadFromFile("graphics/chaser.png");
        m_Sprite.setTexture(textureZombie);
        break;
    case 2:
        m_Speed  = CRAWLER_SPEED;
        m_Health = CRAWLER_HEALTH;
        textureZombie.loadFromFile("graphics/crawler.png");
        m_Sprite.setTexture(textureZombie);
        break;
    }
    srand((int)time(0) + seed);
    int var  = rand() % MAX_VARIANCES * 2 + (100 - MAX_VARIANCES);
    m_Health = m_Health * ((float)var / 100.0);

    srand((int)time(0) + seed+25);
    var  = rand() % MAX_VARIANCES * 2 + (100 - MAX_VARIANCES);
    m_Speed = m_Speed * ((float)var / 100.0);

    m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);

    m_Position.x = x;
    m_Position.y = y;
    m_Sprite.setPosition(m_Position);
}
Sprite& Zombie::getSprite() {return m_Sprite;}
FloatRect Zombie::getBounds() {return m_Sprite.getLocalBounds();}
Vector2f Zombie::getPosition() {return m_Position;}
void Zombie::update(Time dt,Vector2f playerPos) {
    if(playerPos.x > m_Position.x)
        m_Position.x += m_Speed*dt.asSeconds();
    if(playerPos.x < m_Position.x)
        m_Position.x -= m_Speed*dt.asSeconds();
    if(playerPos.y > m_Position.y)
        m_Position.y += m_Speed*dt.asSeconds();
    if(playerPos.y < m_Position.y)
        m_Position.y -= m_Speed*dt.asSeconds();
    m_Sprite.setPosition(m_Position);

    float angle = atan2((playerPos.y-m_Position.y),(playerPos.x-m_Position.x))*180/3.1415;
    m_Sprite.setRotation(angle);
}