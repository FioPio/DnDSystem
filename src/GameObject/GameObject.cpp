#include "GameObject.h"



////////////////////////////////////////////////////////////////////////////////
// GameManager
////////////////////////////////////////////////////////////////////////////////


GameManager::GameManager(int window_width, int window_height) {

    // Game window formatting
    window_size = sf::VideoMode(window_width, window_height);
    game_window = new sf::RenderWindow(window_size, DEFAULT_WINDOW_TITLE);
    game_window->setFramerateLimit(DEFAULT_FPS);

    // Ball creation
    ball = new sf::CircleShape(DEFAULT_BALL_RADIUS);
    ball->setFillColor(DEFAULT_BALL_COLOR);
}


GameManager::~GameManager() {

    delete game_window;
    delete ball;
}


/**
 * This function processes the input recieved from keyboard and mouse during
 * game so the interaction may be acomplished. 
 */
void GameManager::processInput() {

    sf::Event event;
    while(game_window->pollEvent(event)) {
        
        switch (event.type)
        {
        case sf::Event::Closed:  /**< When the window is closed. */
            closeWindow();
            break;

        case sf::Event::KeyPressed: /**< When key is pressed. */
            manageKeyPress(event.key.code);
            break;
        
        case sf::Event::KeyReleased: /**< When a key is released. */
            manageKeyRelease(event.key.code);
            break;

        }

    }
}


/**
 * This function updates the game status and also updates the entities that 
 * compound it.
 */
void GameManager::update() {

}


/**
 * This function clens the windows and renders all the elements that appear
 * on it.
 */
void GameManager::render() {

}


/**
 * Closes the game window and finishes the game.
 */
void GameManager::closeWindow() {

    game_window->close();
}


/**
 * This function manages all the logic executed when a key is pressed.
 * 
 * @param pressed_key The key that has been pressed.
 */
void GameManager::manageKeyPress(sf::Keyboard::Key& pressed_key) {

    switch (pressed_key)
    {
    case sf::Keyboard::Escape:
        closeWindow();
        break;
    
    default:
        break;
    }

}


/**
 * This function manages all the logic executed when a key is released.
 * 
 * @param released_key The key that has been released.
 */
void GameManager::manageKeyRelease(sf::Keyboard::Key& released_key) {

    switch (released_key)
    {
    case sf::Keyboard::Escape:
        closeWindow();
        break;
    
    default:
        break;
    }
}


/**
 * This function implements the game loop.
 */
void GameManager::runGame() {

    while(game_window->isOpen()) {

        processInput();

        update();

        render();
    }
}


