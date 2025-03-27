#pragma once

#include <SFML/Graphics.hpp>

// Game window
#define DEFAULT_WINDOW_HEIGHT   480 /**< Default window height 480px. */
#define DEFAULT_WINDOW_WIDTH    640 /**< Default window width 640px. */
#define DEFAULT_WINDOW_TITLE "PONG" /**< Default window name. */
#define DEFAULT_FPS              60 /**< Default game frame rate. */


#define DEFAULT_BALL_RADIUS              10 /**< Default ball radius. */
#define DEFAULT_BALL_COLOR   sf::Color::Red /**< Default ball color is RED. */



/**
 * This class manages all the game logic and also takes care of the resources
 * usage.
 */
class GameManager {

    sf::RenderWindow* game_window = nullptr; /**< The game window. */

    sf::VideoMode window_size; /**< To keep track of the window size. */

    sf::CircleShape* ball = nullptr; /**< To keep track of the game ball. */

    /**
     * This function processes the input recieved from keyboard and mouse during
     * game so the interaction may be acomplished. 
     */
    void processInput();

    /**
     * This function updates the game status and also updates the entities that 
     * compound it.
     */
    void update();

    /**
     * This function cleans the windows and renders all the elements that appear
     * on it.
     */
    void render();

    /**
     * Closes the game window and finishes the game.
     */
    void closeWindow();

    /**
     * This function manages all the logic executed when a key is pressed.
     * 
     * @param pressed_key The key that has been pressed.
     */
    void manageKeyPress(sf::Keyboard::Key& pressed_key);

    /**
     * This function manages all the logic executed when a key is released.
     * 
     * @param released_key The key that has been released.
     */
    void manageKeyRelease(sf::Keyboard::Key& released_key);

    public:

    /**
     * This constructor creates the window and starts the game.
     * 
     * @param window_width The desired window width, has the default value 
     *                     DEFAULT_WINDOW_WIDTH.
     * @param window_height The desired window height, has the default value 
     *                     DEFAULT_WINDOW_HEIGHT. 
     */
    GameManager(int window_width = DEFAULT_WINDOW_WIDTH, 
                int window_height = DEFAULT_WINDOW_HEIGHT);

    /**
     * Destructor for the class GameManager.
     */
    ~GameManager();

    /**
     * This function implements the game loop.
     */
    void runGame();
};


class Racket {

    sf::Texture* racket_texture;
};