# README for 2D-Game

## Introduction
This is a simple 2D game using the SFML library.


https://github.com/beaamoo/2D-Game/assets/118908954/041e681f-c9e7-4850-840e-f1e2d4731865


## Getting Started
### Environment Assumptions for 2D-Game
#### Software Requirements
- Operating Systems: Windows 10+, macOS Mojave+, or a recent Linux distribution (e.g., Ubuntu 18.04+).
- Development Tools: GCC, Clang, or MSVC; SFML 2.5+; CMake 3.15+.
- IDE Recommendations: Visual Studio 2019 (Windows), Xcode (macOS), Code::Blocks or VSCode (Linux).

#### Hardware Requirements
- Minimum: 1 GHz CPU, 2 GB RAM, integrated graphics, 100 MB storage.
- Recommended: 2 GHz CPU, 4 GB RAM, dedicated GPU with OpenGL 3.0 support, 200 MB storage.

#### Additional Notes
- No internet connection required for gameplay.
- Performance may vary outside these specifications.

### Prerequisites
Before you begin, ensure you have the following installed:
- [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/download.php) for graphics and window management.
- A C++ compiler, such as GCC, Clang, or MSVC.
- [CMake](https://cmake.org/download/) to build the project.

### Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/beaamoo/2D-Game.git
   cd 2D-Game
   ```

2. **Build the Game:**
   ```bash
   mkdir build
   cd build
   rm CMakeCache.txt
   rm -rf _deps
   cmake ..
   make
   ```

### Running the Game

- Run the executable generated in the `build` directory:
  ```bash
  ./2D-Game
  ```

## Gameplay

1. **Start the Game:**
   - Upon launching, you'll be greeted with a welcome screen.
   - Press any key to begin your adventure.

2. **Game Mechanics:**
   - Use the arrow keys for navigation and interaction within the game.
   - Engage with different elements and challenges presented.

3. **Objective:**
   - The game's objective will vary depending on the current level and challenges.
   - Complete tasks, solve puzzles, or reach certain points to progress.

4. **Quitting and Restarting:**
   At win or gameover state:
   - Press 'Q' to quit the game.
   - Press 'R' to restart the game.
  
## Testing
### Overview
To ensure the reliability and correctness of our 2D-Game, we have implemented a robust testing strategy using the Google Test framework. Our tests are designed to cover critical functionalities of the game, focusing on various aspects including coordinate calculations, game mechanics, and collision detection. This approach helps us maintain high code quality and game performance.

### Running Tests
After building the project, you can run the tests by following these steps:

Navigate to the Build Directory: Change to the directory where your game is built.
```bash
cd build
./coordinate_test
```

### Test Coverage
Our testing suite includes a variety of test cases to ensure comprehensive coverage:

1. **Coordinate Calculations:** Tests the accuracy and reliability of coordinate transformations and movements, crucial for the game's spatial logic.

2. **Game Mechanics:** Evaluates the initialization, state transitions, and updates in game mechanics to ensure consistent behavior under different scenarios.

3. **Collision Detection:** Validates the detection of collisions between various game elements, a core aspect of game dynamics.

As the game evolves, we regularly update and expand our tests to include new features and scenarios, ensuring ongoing stability and performance.

## Contributing
We welcome contributions! If you have ideas, bug fixes, or improvements, feel free to fork the repository and submit pull requests.

## License
This project is open-source, licensed under the MIT License. See the [LICENSE.md](LICENSE.md) file for more details.

---

Get ready to soar through the stars in this 2D-Game, as you help Larry the Alien refuel his space ship! 🌟🎮🚀


