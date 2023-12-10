#include "game.h"

// Constructor
Game::Game() {
    initWindow();
    initBackground();
    initSnake();
    moveDistanceX = 5.0f; // Smaller values for slower movement
    moveDistanceY = 5.0f;
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
}

//Update the score display
void Game::updateScore() {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(10, 10); // Position the score text on the window
}

// Initialize the snake
void Game::initSnake() {
    sf::CircleShape segment(10); // Size of each segment
    segment.setFillColor(sf::Color::Green);
    segment.setPosition(400, 300); // Starting position of the snake
    snake.push_back(segment);

    direction = sf::Vector2f(10, 0); // Initial movement direction
}

// Render the game
void Game::render() {
    window.clear();
    window.draw(background);
    for (const auto& segment : snake) {
        window.draw(segment);
    }
    window.draw(food); // Draw the food
    window.draw(scoreText); // Draw the score
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
    food.setRadius(20); // Example size
    food.setFillColor(sf::Color::Red); // Example color
    spawnFood(); // Set initial position
}

void Game::spawnFood() {
    // Randomly position the food within the window bounds
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
    for (auto it = ++snake.begin(); it != snake.end(); ++it) {
        if (head.getGlobalBounds().intersects(it->getGlobalBounds())) {
            // Handle game over due to self-collision
            // For now, let's close the window. You can replace this with more complex game over logic.
            window.close();
            return;
        }
    }

    // Check for food collision
    if (snake.front().getGlobalBounds().intersects(food.getGlobalBounds())) {
        growSnake();
        spawnFood(); // Respawn the food after it's eaten
        // Increment score here (if you have a scoring system)
        }
}

void Game::growSnake() {
    // Create a new segment
    sf::CircleShape newSegment(10);
    newSegment.setFillColor(sf::Color::Green);

    // Position the new segment at the tail of the snake
    const auto& tail = snake.back();
    newSegment.setPosition(tail.getPosition()); // You can adjust this logic based on your movement mechanics

    // Add the new segment to the snake
    snake.push_back(newSegment);
    score += 10;  // Increment the score
    updateScore();  // Update the score display
}

// Update the game state
void Game::update(sf::Time delta) {
    // Move the snake
    for (auto it = snake.rbegin(); it != snake.rend(); ++it) {
        if (it == snake.rbegin()) {
            // Move the head
            it->move(direction);
        } else {
            // Move the body
            auto next = it;
            --next;
            it->setPosition(next->getPosition());
        }
    }

    checkCollisions();
}