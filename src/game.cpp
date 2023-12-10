#include "game.h"

// Constructor
Game::Game() {
    initWindow();
    initBackground();
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
    score = 0;
    if (!font.loadFromFile("resources/RethinkSans-VariableFont_wght.ttf")) { // Ensure the font file path is correct
        // Handle error
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    updateScore(); // Initialize score display
}

// Initialize the game window
void Game::initWindow() {
    window.create(sf::VideoMode(800, 600), "Snake Game");
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
    // Draw the food
    window.draw(food);
    // Draw the score text
    window.draw(scoreText);
    // Display the rendered frame
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

    // Check for self-collision
    /**for (auto it = std::next(snake.begin()); it != snake.end(); ++it) {
        if (head.getGlobalBounds().intersects(it->getGlobalBounds())) {
            window.close(); // You can add more sophisticated game over handling here
            return;
        }
    }
**/
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

// Update the game state
void Game::update(sf::Time delta) {
    sf::Vector2f prevPosition = snake.front().getPosition();

    // Move the head
    snake.front().move(direction * delta.asSeconds()* 40.0f); // Adjust the speed of the snake

    // Move the rest of the body
    for (auto it = ++snake.begin(); it != snake.end(); ++it) {
        sf::Vector2f currentPos = it->getPosition();
        it->setPosition(prevPosition);
        prevPosition = currentPos;
    }

    checkCollisions();
}
