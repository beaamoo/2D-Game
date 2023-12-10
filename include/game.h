#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <array>


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
    std::array<sf::Texture, 8> planetTextures; // Array to store planet textures
    struct Planet {
        sf::Sprite sprite;
        float speed;
    };

    std::vector<Planet> planets;

    void initPlanets(); // Initialize planets
    void updatePlanets(sf::Time delta); // Update planets' positions
    void checkPlanetCollisions(); // Check for collisions with planets
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

