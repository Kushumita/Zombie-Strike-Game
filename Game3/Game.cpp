#include "Player.cpp"
#include "utility.cpp"
#include "zombie.cpp"
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

int main() {
#pragma region VM
    VideoMode    vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(vm, "ViewConcepts", Style::Fullscreen);
    Vector2f     resolution(1920, 1080);
    View         mainView(FloatRect(0, 0, resolution.x, resolution.y));
#pragma endregion

#pragma region Declaring_Variables
    IntRect arena;
    int     wave = 2;
    arena.left   = 0;
    arena.top    = 0;
    arena.width  = wave * 250;
    arena.height = wave * 250;
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
    // zombie.spawn(500,250,2,0);
    Clock clock;
    Time  dt;

    Vector2i mouseScreenPosition;  // +ve values
    Vector2f mouseWorldPosition;  // can get +ve as well as -ve coordinates;

#pragma endregion

    while (window.isOpen()) {
        Event event;
        dt = clock.restart();
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

        window.setView(mainView);
        player.update(dt,Mouse::getPosition(),window);
        for (size_t i = 0; i < num_Zombies; i++)
        {
            zombies[i].update(dt,player.getCenter());
        }
        
        window.clear();
        // window.draw(rectWindow);
        // window.draw(rectArena);
        window.draw(rVA,&textureBackground);
        for (int i = 0; i < num_Zombies; i++)
        {
            window.draw(zombies[i].getSprite());
        }
        
        window.draw(player.getSprite());
        window.display();
    }
    return 0;
}