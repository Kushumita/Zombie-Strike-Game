#include "Player.cpp"
#include "utility.cpp"
#include "zombie.cpp"
#include "Bullet.cpp"
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

#define NUM_BULLETS 6

int main() {
#pragma region VM
    VideoMode    vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(vm, "ViewConcepts", Style::Fullscreen);
    Vector2f     resolution(1920, 1080);
    View         mainView(FloatRect(0, 0, resolution.x, resolution.y));
    View         hudView(FloatRect(0, 0, resolution.x, resolution.y));
#pragma endregion

#pragma region Declaring_Variables
    IntRect arena;
    int     wave = 2;
    arena.left   = 0;
    arena.top    = 0;
    arena.width  = wave * 250;
    arena.height = wave * 250;
    float fireRate = 4;
    // RectangleShape rectArena(Vector2f(arena.width, arena.height));
    // rectArena.setFillColor(Color::Green);
    VertexArray rVA;
    int TILE_SIZE = createBackgroud(rVA,arena);
    int num_Zombies = 5;

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background_sheet.png");

    Player player;
    player.spawnPlayer(arena,TILE_SIZE);
    Zombie *zombies;
    zombies = createZombieHorde(num_Zombies,arena);
    Bullet bullets[NUM_BULLETS];
    int score = 0;
    Font font;
    font.loadFromFile("fonts/zombiecontrol.ttf");
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: 0");
    scoreText.setOrigin(scoreText.getLocalBounds().width/2,scoreText.getLocalBounds().height/2);
    // scoreText.setPosition(50,50);
    scoreText.setPosition(resolution.x/2,50);
    // zombie.spawn(500,250,2,0);
    Clock clock;
    Time  dt;
    Time gameTotal;
    Time lasthit;

    Vector2i mouseScreenPosition;  // +ve values
    Vector2f mouseWorldPosition;  // can get +ve as well as -ve coordinates;

#pragma endregion

    int currentBullet = 0;
    while (window.isOpen()) {
        Event event;
        dt = clock.restart();
        gameTotal+=dt;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if (event.key.code == Keyboard::C){
                    cout<<"Player (Global): ("<< player.getCenter().x<<" , "<<player.getCenter().y<<")"<<endl;

                    Vector2i playerScreenPos = window.mapCoordsToPixel(player.getCenter());
                    cout<<"Player (Screen): ("<< playerScreenPos.x<<" , "<<playerScreenPos.y<<")"<<endl;
                }
                if (event.key.code == Keyboard::M){
                    mouseScreenPosition = Mouse::getPosition();
                    cout<<"Mouse Screen: ("<< mouseScreenPosition.x<<" , "<<mouseScreenPosition.y<<")"<<endl;

                    mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition);
                    cout<<"Mouse World: ("<< mouseWorldPosition.x<<" , "<<mouseWorldPosition.y<<")"<<endl;
                }
            }
            if(event.type==Event::MouseButtonPressed){
                if(gameTotal.asMilliseconds()-lasthit.asMilliseconds()>(1000/fireRate)){
                    bullets[currentBullet++].shoot(player.getCenter(),window.mapPixelToCoords(Mouse::getPosition()));
                    lasthit = gameTotal;
                    if(currentBullet==NUM_BULLETS)
                        currentBullet = 0;
                }
            }
        }
#pragma region PlayerMovement
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.moveUp();
        } else {
            player.stopUp();
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.moveLeft();
        } else {
            player.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.moveDown();
        } else {
            player.stopDown();
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.moveRight();
        } else {
            player.stopRight();
        }
#pragma endregion
        // mainView.setCenter(Vector2f(arena.width / 2, arena.height / 2));
        mainView.setCenter(player.getCenter());

        player.update(dt,Mouse::getPosition(),window);
        
        for (int i = 0; i < NUM_BULLETS; i++){
            if (bullets[i].isInFight()){
                // cout<<"B: "<<Mouse::getPosition().x<<", "<<Mouse::getPosition().y<<"\n";
                bullets[i].update(dt);
            }
        }
        for (size_t i = 0; i < num_Zombies; i++)
        {
            if(zombies[i].isAlive())
                zombies[i].update(dt,player.getCenter());
        }


        
        window.clear();
        window.setView(mainView);
        // window.draw(rectWindow);
        // window.draw(rectArena);
        window.draw(rVA,&textureBackground);
        for (int i = 0; i < num_Zombies; i++)
        {
            window.draw(zombies[i].getSprite());
        }
        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if(bullets[i].isInFight()){
                window.draw(bullets[i].getShape());
            }
        }
        for (size_t i = 0; i < NUM_BULLETS; i++)
        {
            for (size_t j = 0; j < num_Zombies; j++)
            {
                if(bullets[i].isInFight()&&zombies[j].isAlive()){
                    if(bullets[i].getBounds().intersects(zombies[j].getBounds())){
                        bullets[i].stop();
                        if(zombies[j].hit()){
                            score+=10;
                            scoreText.setString("Score: "+std::to_string(score));
                        }
                    }
                }
            }
            
        }
        window.draw(player.getSprite());
        
        window.setView(hudView);
        window.draw(scoreText);
        window.setView(mainView);
        window.display();
    }
    return 0;
}