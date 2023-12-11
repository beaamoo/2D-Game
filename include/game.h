#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <array>


class Game {
public:
    Game();
    int run();
    void resetGame(); // Resets the game to initial state

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
    std::vector<sf::Texture> planetTextures; // Vector to store planet textures
    struct Planet {
        sf::Sprite sprite;
        float speed;
    };
    std::vector<Planet> planets;
    sf::Texture gameOverTexture;  // Texture for the game over screen
    sf::Sprite gameOverSprite;    // Sprite for the game over screen
    sf::Texture winTexture;
    sf::Sprite winSprite;
    sf::Text winText; // Text to display when the player wins
    sf::Texture welcomeTexture;
    sf::Sprite welcomeSprite;
    
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
    bool isOverlapping(const sf::Sprite& newPlanet); // Checks if a planet is overlapping with another planet
    bool isGameOver;
    bool isWin; // Flag to indicate if the player has won
    bool showWelcomeScreen;
    void setupGameOverSprite();
    void setupWinSprite();
    void setupWelcomeSprite();
    void setupScoreText();
    void setupWinText();
};

