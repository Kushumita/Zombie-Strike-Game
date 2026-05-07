#include <SFML/Graphics.hpp>
#include<cmath>
using namespace sf;

class Player {
  private:
    const int INIT_HEALTH = 100;
    const int INIT_SPEED  = 200;
    
    Vector2f m_Position;
    int      m_Speed;
    int      m_health;
    Texture  m_Texture;
    Sprite   m_Sprite;
    IntRect  m_Arena;
    int tile_Size;

    bool m_LeftPressed  = false;
    bool m_RightPressed = false;
    bool m_UpPressed    = false;
    bool m_DownPressed  = false;

  public:
    Player();
    void     spawnPlayer(IntRect arena,int tileSize);
    Sprite  &getSprite();
    Vector2f getCenter();
    void     moveLeft();
    void     stopLeft();
    void     moveRight();
    void     stopRight();
    void     moveUp();
    void     stopUp();
    void     moveDown();
    void     stopDown();

    void update(Time dt,Vector2i mouseScreenPos,RenderWindow &window);
};
Player::Player() {
    m_Speed  = INIT_SPEED;
    m_health = INIT_HEALTH;
    m_Texture.loadFromFile("graphics/player.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25, 25);
}
void Player::spawnPlayer(IntRect arena,int tileSize) {
    m_Arena.left   = arena.left;
    m_Arena.top    = arena.top;
    m_Arena.width  = arena.width;
    m_Arena.height = arena.height;
    m_Position.x   = arena.width / 2;
    m_Position.y   = arena.height / 2;
    m_Sprite.setPosition(m_Position);
    tile_Size = tileSize;
}
Sprite &Player::getSprite() { return m_Sprite; }

Vector2f Player::getCenter() { return m_Position; }

void Player::moveLeft() { m_LeftPressed = true; }
void Player::stopLeft() { m_LeftPressed = false; }
void Player::moveRight() { m_RightPressed = true; }
void Player::stopRight() { m_RightPressed = false; }
void Player::moveUp() { m_UpPressed = true; }
void Player::stopUp() { m_UpPressed = false; }
void Player::moveDown() { m_DownPressed = true; }
void Player::stopDown() { m_DownPressed = false; }

void Player::update(Time dt,Vector2i mouseScreenPos,RenderWindow &window) {
    if (m_LeftPressed && m_Position.x >= m_Arena.left+tile_Size)
        m_Position.x -= m_Speed * dt.asSeconds();
    if (m_RightPressed && m_Position.x <= m_Arena.width-tile_Size)
        m_Position.x += m_Speed * dt.asSeconds();
    if (m_UpPressed && m_Position.y >= m_Arena.top+tile_Size)
        m_Position.y -= m_Speed * dt.asSeconds();
    if (m_DownPressed && m_Position.y <= m_Arena.height-tile_Size)
        m_Position.y += m_Speed * dt.asSeconds();
    m_Sprite.setPosition(m_Position);

    Vector2i playerScreenPos = window.mapCoordsToPixel(m_Position);
    float angle = atan2((mouseScreenPos.y - playerScreenPos.y),(mouseScreenPos.x - playerScreenPos.x))*180/3.1415;
    m_Sprite.setRotation(angle);
}
