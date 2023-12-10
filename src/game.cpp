#include "game.h"

// Constructor
Game::Game() {
    initWindow();
    initBackground();
    initPlanets();
    if (!snakeTexture.loadFromFile("resources/sphere.png")) {
        // Handle error - texture file not found
    }
    if (!snakeHeadTexture.loadFromFile("resources/rocket.png")) {
        // Handle error - texture file not found
    }
    moveDistanceX = 5.0f; // Smaller values for slower movement
    moveDistanceY = 5.0f;
    initSnake();
    initFood();
    score = 100;
    if (!font.loadFromFile("resources/RethinkSans-VariableFont_wght.ttf")) { // Ensure the font file path is correct
        // Handle error
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    updateScore(); // Initialize score display
    if (!gameOverTexture.loadFromFile("resources/caughtAlien.png")) {
    // Handle error
    }
    gameOverSprite.setScale(0.2f, 0.2f); // Scale down the game over sprite
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(window.getSize().x / 2 - gameOverSprite.getGlobalBounds().width / 2, 
                            window.getSize().y / 2 - gameOverSprite.getGlobalBounds().height / 2); // Center the sprite

    isGameOver = false;
}

// Initialize the game window
void Game::initWindow() {
    window.create(sf::VideoMode(800, 600), "Space Game");
    window.setFramerateLimit(60);
}

// Initialize the background
void Game::initBackground() {
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        // Handle error - file not found
    }

    background.setTexture(backgroundTexture);

    // Calculate scale factors
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(scaleX, scaleY);
}

//Update the score display
void Game::updateScore() {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(10, 10); // Position the score text on the window
}

// Initialize the snake
void Game::initSnake() {
    // Create and set up the head
    sf::CircleShape head(40); // Size for the head
    head.setTexture(&snakeHeadTexture); // Texture for the head
    head.setPosition(400, 300); // Starting position of the head
    snake.push_back(head);

    direction = sf::Vector2f(10, 0); // Initial movement direction
}

// Render the game
void Game::render() {
    window.clear();
    // Draw the background
    window.draw(background);
    // Draw each segment of the snake
    for (const auto& segment : snake) {
        window.draw(segment);
    }
    // Draw planets
    for (const auto& planet : planets) {
        window.draw(planet.sprite);
    }
    // Draw the food
    window.draw(food);
    // Draw the score text
    window.draw(scoreText);
    // Draw the game over screen
    if (isGameOver) {
        window.draw(gameOverSprite);
        sf::Text gameOverText("Game Over! You were caught by enemy aliens. \n               Press R to Retry or Q to Quit", font);
        gameOverText.setCharacterSize(24);
        gameOverText.setFillColor(sf::Color::White);
        // Position the text below the sprite
        gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, 
                                 gameOverSprite.getPosition().y + gameOverSprite.getGlobalBounds().height + 10); // 10 is a padding value
        window.draw(gameOverText);
    }
    window.display();
}

// Main game loop
int Game::run() {
    while (window.isOpen()) {
        processInput();
        update(clock.restart());
        render();
    }
    return 0;
}

// Process user input
void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (isGameOver) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    // Reset the game to initial state
                    resetGame();
                } else if (event.key.code == sf::Keyboard::Q) {
                    window.close(); // Quit the game
                }
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up)
                direction = sf::Vector2f(0, -moveDistanceY);
            else if (event.key.code == sf::Keyboard::Down)
                direction = sf::Vector2f(0, moveDistanceY);
            else if (event.key.code == sf::Keyboard::Left)
                direction = sf::Vector2f(-moveDistanceX, 0);
            else if (event.key.code == sf::Keyboard::Right)
                direction = sf::Vector2f(moveDistanceX, 0);
        }
    }
}

void Game::initFood() {
    food.setRadius(10); // Food size
    food.setTexture(&snakeTexture); // Food texture
    spawnFood(); // Set initial position
}

void Game::spawnFood() {
    int maxX = static_cast<int>(window.getSize().x - food.getRadius() * 2);
    int maxY = static_cast<int>(window.getSize().y - food.getRadius() * 2);
    sf::Vector2f foodPosition(rand() % maxX, rand() % maxY);
    food.setPosition(foodPosition);
}

void Game::checkCollisions() {
    // Check for boundary wrapping
    auto& head = snake.front();
    sf::Vector2f headPos = head.getPosition();
    sf::Vector2u windowSize = window.getSize();

    // Wrap snake around horizontally
    if (headPos.x < 0) {
        head.setPosition(windowSize.x, headPos.y);
    } else if (headPos.x >= windowSize.x) {
        head.setPosition(0, headPos.y);
    }

    // Wrap snake around vertically
    if (headPos.y < 0) {
        head.setPosition(headPos.x, windowSize.y);
    } else if (headPos.y >= windowSize.y) {
        head.setPosition(headPos.x, 0);
    }

    // Check for food collision
    if (head.getGlobalBounds().intersects(food.getGlobalBounds())) {
        growSnake();
        spawnFood(); // Respawn the food after it's eaten
    }
}

void Game::growSnake() {
    sf::CircleShape newSegment(10); // Segment size, matching the head and other segments
    newSegment.setTexture(&snakeTexture); // Using the same texture as the other segments

    sf::Vector2f newPosition;
    if (snake.size() == 1) {
        // If there's only a head, add the segment directly below it
        const auto& head = snake.front();
        newPosition = head.getPosition();
        newPosition.y += head.getRadius() * 2; // Position it below the head
    } else {
        // For subsequent segments, add below the last segment
        const auto& tail = snake.back();
        newPosition = tail.getPosition();
        newPosition.y += tail.getRadius() * 2; // Adjust this to ensure proper spacing
    }

    newSegment.setPosition(newPosition);
    snake.push_back(newSegment);
    score += 10;
    updateScore();
}

void Game::initPlanets() {
    planetTextures.resize(8); // Resize to hold 8 textures

    for (int i = 0; i < 8; ++i) {
        if (!planetTextures[i].loadFromFile("resources/planet" + std::to_string(i + 1) + ".png")) {
            // Handle error - texture file not found
            continue;
        }

        Planet planet;
        planet.sprite.setTexture(planetTextures[i]);
        // Set initial position off the left edge of the window at a random height
        planet.sprite.setPosition(-planet.sprite.getGlobalBounds().width, rand() % window.getSize().y);
        // Assign a random speed to make the planet move quickly
        planet.speed = static_cast<float>(rand() % 100 + 50); // Speed range from 50 to 150

        planets.push_back(planet);
    }
}

bool Game::isOverlapping(const sf::Sprite& newPlanet) {
    for (const auto& planet : planets) {
        if (newPlanet.getGlobalBounds().intersects(planet.sprite.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

void Game::updatePlanets(sf::Time delta) {
    for (auto& planet : planets) {
        // Move each planet horizontally
        planet.sprite.move(planet.speed * delta.asSeconds(), 0);

        // If a planet goes off the right side of the screen, reposition it to the left
        if (planet.sprite.getPosition().x > window.getSize().x) {
            planet.sprite.setPosition(-planet.sprite.getGlobalBounds().width, rand() % window.getSize().y);
        }
    }
}

void Game::checkPlanetCollisions() {
    const auto& head = snake.front();
    for (auto& planet : planets) {
        if (head.getGlobalBounds().intersects(planet.sprite.getGlobalBounds())) {
            score -= 10;  // Deduct 10 points upon collison with a planet
            updateScore(); // Update the score display
            // Optionally, reposition the collided planet
            planet.sprite.setPosition(-planet.sprite.getGlobalBounds().width, rand() % window.getSize().y);
        }
    }
}

void Game::resetGame() {
    // Reset game variables
    score = 100;
    isGameOver = false;
    // Reset other game elements as needed

    updateScore();
    // ... more resetting as needed ...
}

// Update the game state
void Game::update(sf::Time delta) {
    //Check for game over
    if (score <= 0) {
        // Handle game over due to score reaching 0
        isGameOver = true;
        return;
    }
    //Check for winning
    if (score >= 200) {
        // Handle winning the game
        window.close(); // Or transition to a winning screen
        return;
    }

    sf::Vector2f prevPosition = snake.front().getPosition();

    // Move the head
    snake.front().move(direction * delta.asSeconds()* 40.0f); // Adjust the speed of the snake

    // Move the rest of the body
    for (auto it = ++snake.begin(); it != snake.end(); ++it) {
        sf::Vector2f currentPos = it->getPosition();
        it->setPosition(prevPosition);
        prevPosition = currentPos;
    }
    updatePlanets(delta);
    checkPlanetCollisions();
    checkCollisions();

}
