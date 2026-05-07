#pragma once
#include "zombie.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int createBackgroud(VertexArray &rVA, IntRect arena) {
    const int TILE_SIZE      = 50;
    const int VERTS_IN_QUADS = 4;
    const int TILE_TYPES     = 3; // starting index is 0 so # is 4

    int worldHeight = arena.height / TILE_SIZE;
    int worldWidth  = arena.width / TILE_SIZE;
    rVA.setPrimitiveType(Quads);
    rVA.resize(worldHeight * worldWidth * VERTS_IN_QUADS);

    int currentIndex = 0;
    for (int i = 0; i < worldHeight; i++) {
        for (int j = 0; j < worldWidth; j++) {
            // Extract the boundary coordinate for each tiles
            // where to draw
            rVA[currentIndex].position     = Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            rVA[currentIndex + 1].position = Vector2f(i * TILE_SIZE + TILE_SIZE, j * TILE_SIZE);
            rVA[currentIndex + 2].position = Vector2f(i * TILE_SIZE + TILE_SIZE, j * TILE_SIZE + TILE_SIZE);
            rVA[currentIndex + 3].position = Vector2f(i * TILE_SIZE, j * TILE_SIZE + TILE_SIZE);

            // from where to obtain the image
            if (i == 0 || i == worldHeight - 1 || j == 0 || j == worldWidth - 1) {
                // obtain the wall
                rVA[currentIndex].texCoords     = Vector2f(0, TILE_TYPES * TILE_SIZE);
                rVA[currentIndex + 1].texCoords = Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);
                rVA[currentIndex + 2].texCoords = Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE + TILE_SIZE);
                rVA[currentIndex + 3].texCoords = Vector2f(0, TILE_TYPES * TILE_SIZE + TILE_SIZE);
            } else {
                srand((int)time(0) + i * i + j);
                int morG    = rand() % TILE_TYPES;
                int yOffset = morG * TILE_SIZE;

                rVA[currentIndex].texCoords     = Vector2f(0, yOffset);
                rVA[currentIndex + 1].texCoords = Vector2f(TILE_SIZE, yOffset);
                rVA[currentIndex + 2].texCoords = Vector2f(TILE_SIZE, yOffset + TILE_SIZE);
                rVA[currentIndex + 3].texCoords = Vector2f(0, yOffset + TILE_SIZE);
            }
            currentIndex += VERTS_IN_QUADS;
        }
    }
    return TILE_SIZE;
}

Zombie *createZombieHorde(int num_Zombies, IntRect arena) {
    Zombie *zombies = new Zombie[num_Zombies];
    int     minX    = arena.left + 25;
    int     maxX    = arena.width - 25;
    int     minY    = arena.top + 25;
    int     maxY    = arena.height - 25;
    srand((int)time(0));
    for (int i = 0; i < num_Zombies; i++) {
        int side = rand() % 4;
        int x,y;
        switch (side) {
        case 0: x = minX;    // Left
                y = rand()%(maxY-minY)+minY;
            break;
        case 1: x = maxX;// Right
                y = rand()%(maxY-minY)+minY;
            break;
        case 2: y = minY; // Top
                x = rand()%(maxX-minX)+minX;
            break;
        case 3: y = maxY; // Bottom
                x = rand()%(maxX-minX)+minX;
            break;
        }
        int type = rand()%3;
        zombies[i].spawn(x, y, type, i);
    }

    return zombies;
}