#include <SFML/Graphics.hpp>
#include"Player.cpp"
using namespace sf;

int            main() {
#pragma region VM,Window
    VideoMode    vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(vm, "View Concepts", Style::Fullscreen);
    Vector2i     resolution(1920, 1080);
    View         mainView(FloatRect(0, 0, resolution.x, resolution.y));
    
#pragma endregion

    #pragma region DeclaringVariables
    IntRect arena;
    arena.left = 0;
    arena.top = 0;
    arena.width = 500;
    arena.height = 500;

    Player player;
    player.spawn(arena);
    Clock clock;
    Time dt;

    RectangleShape arenaRect(Vector2f(arena.width,arena.height));
    arenaRect.setFillColor(Color::Green);

    RectangleShape viewRect(Vector2f(resolution.x,resolution.y));
    viewRect.setFillColor(Color::Red);
    #pragma endregions
    while (window.isOpen())
    {
        Event event;
        dt = clock.restart();
        while (window.pollEvent(event))
        {
            if(event.type==Event::Closed)
                window.close();
            if(event.type==Event::KeyPressed){
                if(event.key.code == Keyboard::Escape)
                    window.close();
            }
        }
#pragma region Movement_player
        if(Keyboard::isKeyPressed(Keyboard::A)){
            player.moveLeft();
        }else{
            player.stopLeft();
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            player.moveRight();
        }else{
            player.stopRight();
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            player.moveUp();
        }else{
            player.stopUp();
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            player.moveDown();
        }else{
            player.stopDown();
        }
#pragma endregion
        player.update(dt);
        // mainView.setCenter(player.getCenter());
        mainView.setCenter(Vector2f(arena.width/2,arena.height/2));

        window.setView(mainView);
        window.clear();
        window.draw(viewRect);
        window.draw(arenaRect);
        window.draw(player.getSprite());
        window.display();
    }
    
    return 0;
}