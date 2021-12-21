#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Game.h"

int main() {

   Life life(20, 20);

    new Game(life);

}