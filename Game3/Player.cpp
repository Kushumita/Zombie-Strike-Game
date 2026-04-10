#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
  private:
    const float START_SPEED  = 200;
    const float START_HEALTH = 100;

    int      m_Health;
    int      m_Speed;
    Vector2f m_Position;
    Sprite   m_Sprite;
    Texture  m_Texture;
    IntRect  m_Arena;
    Vector2f m_Resolution;

    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

  public:
    Player();
    void    spawn(IntRect);
    Sprite &getSprite();
    Vector2f getCenter();
    void    moveLeft();
    void    stopLeft();
    void    moveRight();
    void    stopRight();
    void    moveUp();
    void    stopUp();
    void    moveDown();
    void    stopDown();
    void    update(Time dt);
};
Player::Player() {
    m_Health = START_HEALTH;
    m_Speed  = START_SPEED;
    m_Texture.loadFromFile("graphics/player.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25, 25);
}
void Player::spawn(IntRect arena) {
    m_Arena.left   = arena.left;
    m_Arena.top    = arena.top;
    m_Arena.width  = arena.width;
    m_Arena.height = arena.height;

    m_Position.x = m_Arena.width / 2;
    m_Position.y = m_Arena.height / 2;
    m_Sprite.setPosition(m_Position);
}

Sprite &Player::getSprite() { return m_Sprite; }

void Player::moveLeft() { m_LeftPressed = true; }
void Player::stopLeft() { m_LeftPressed = false; }
void Player::moveRight() { m_RightPressed = true; }
void Player::stopRight() { m_RightPressed = false; }
void Player::moveUp() { m_UpPressed = true; }
void Player::stopUp() { m_UpPressed = false; }
void Player::moveDown() { m_DownPressed = true; }
void Player::stopDown() { m_DownPressed = false; }

Vector2f Player::getCenter(){return m_Position;}
void Player::update(Time dt){
    if(m_LeftPressed && m_Position.x>=m_Arena.left){
        m_Position.x-= m_Speed*dt.asSeconds();  
    }
    if(m_RightPressed && m_Position.x<=m_Arena.width){
        m_Position.x+= m_Speed*dt.asSeconds();  
    }
    if(m_UpPressed && m_Position.y>=m_Arena.top){
        m_Position.y-= m_Speed*dt.asSeconds();  
    }
    if(m_DownPressed && m_Position.y<=m_Arena.height){
        m_Position.y+= m_Speed*dt.asSeconds();  
    }
    m_Sprite.setPosition(m_Position);
}