#include "iostream"
#include "Game.h"

Game::Game()
{
    std::cout << "Game constructor called" << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called" << std::endl;
}

void Game::Run()
{
    std::cout << "Game run called" << std::endl;
}