#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Game {
public:
    Game();
    int run();

private:
    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture snakeTexture;
    sf::Texture snakeHeadTexture;
    std::list<sf::CircleShape> snake;
    sf::CircleShape food;
    sf::Vector2f direction;
    sf::Clock clock;
    unsigned int score;     // Score variable
    sf::Font font;          // Font for score text
    sf::Text scoreText;
    float moveDistanceX;
    float moveDistanceY; 

    void initWindow();
    void initBackground();
    void initSnake();
    void initFood();
    void processInput();
    void update(sf::Time delta);
    void render();
    void growSnake();
    void checkCollisions();
    void spawnFood();
    void updateScore();  // Updates the score display
};

