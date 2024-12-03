#include "game.h"

// Constructor for the game
Game::Game()
{
    player = new Player();
    board = new Board();
}

// Deconstructor for the game
Game::~Game()
{
    delete player;
    delete board;
}

// Start the game
void Game::start()
{
    // Display the menu when starting the game
    std::cout << "You can use the following commands "
                 "to play the game:" << std::endl;
    std::cout << COMMAND_GENERATE_RANDOM << " <d><p>>" << std::endl;
    std::cout << "\td: the dimension of the board to be generated "
                 "(between 10 and 30)" << std::endl;
    std::cout << "\tp: the probability of the blocks on the board to be "
                 "generated randomly (between 0 and 1)" << std::endl;
    std::cout << COMMAND_INIT << " <x>,<y>,<direction>" << std::endl;
    std::cout << "\tx: horizontal position of the vacuum cleaner "
                 "in the room (between 0 & 9)" << std::endl;
    std::cout << "\ty: vertical position of the vacuum cleaner "
                 "in the room (between 0 & 9)" << std::endl;
    std::cout << "\tdirection: direction of the vacuum cleaner’s movement "
                 "(north, east, south, west)" << std::endl;
    std::cout << COMMAND_FORWARD << std::endl;
    std::cout << COMMAND_TURN_LEFT << " (or l)" << std::endl;
    std::cout << COMMAND_TURN_RIGHT << " (or r)" << std::endl;
    std::cout << COMMAND_QUIT << std::endl;

    // Check if the board is loaded and player is initialized successfully,
    // the game with start
    if(loadBoard()) {
        if (initializePlayer()) {
            play();
        }
    }
}

// Load the game board
bool Game::loadBoard()
{
    bool isLoaded = false;
    bool isRunning = true;

    while (isRunning) {
        // Display the available commands for the loading board
        std::cout << "\nAt this stage of the program, "
                     "only two commands are acceptable:" << std::endl;
        std::cout << COMMAND_GENERATE_RANDOM << " <d><p>"<< std::endl;
        std::cout << COMMAND_QUIT << std::endl;

        std::string input = Helper::readInput(); // Read user input

        std::vector<std::string> tokens;
        Helper::splitString(input, tokens, " ");

        if(!tokens.empty()) {
            if (tokens[0] == "quit") {
                isRunning = false;
                isLoaded = false;
            } else if (tokens[0] == "generate" && tokens.size() == 2) {
                std::vector<std::string> numbers;
                Helper::splitString(tokens[1], numbers, ",");
                if (numbers.size() == 2 && Helper::isNumber(numbers[0])
                    && Helper::isNumber(numbers[1])) {
                    int dim = std::stoi(numbers[0]);
                    float prob = std::stof(numbers[1]);

                    if ((dim >= 10 && dim <= 30) && (prob >= 0 && prob <= 1)) {
                        this->board->generate(dim, prob);
                        isRunning = false;
                        isLoaded = true;
                    } else {
                        Helper::printInvalidInput();
                    }
                } else {
                    Helper::printInvalidInput();
                }
            } else {
                Helper::printInvalidInput();
            }
        } else{
            Helper::printInvalidInput();
        }
    }
    // Return the flag indicating board loading status
    return isLoaded;
}

// Initialize the player
bool Game::initializePlayer()
{
    bool isRunning = true;
    bool isInitializingPlayer = false;

    while (isRunning) {
        board->display(player); // Display the board
        // Display the menu when initializing the player
        std::cout << "At this stage of the program, "
                     "only three commands are acceptable:" << std::endl;
        std::cout << COMMAND_GENERATE_RANDOM << " <d><p>"<< std::endl;
        std::cout << COMMAND_INIT << " <x>,<y>,<direction>" << std::endl;
        std::cout << COMMAND_QUIT << std::endl;

        std::string input = Helper::readInput(); // Read user input
        std::vector<std::string> tokens;
        Helper::splitString(input, tokens, " ");

        if(!tokens.empty()) {
            if (tokens[0] == "quit") {
                isRunning = false;
                isInitializingPlayer = false;
            } else if (tokens[0] == "generate" && tokens.size() == 2) {
                std::vector<std::string> numbers;
                Helper::splitString(tokens[1], numbers, ",");
                if (numbers.size() == 2 && Helper::isNumber(numbers[0])
                    && Helper::isNumber(numbers[1])) {
                    int dim = std::stoi(numbers[0]);
                    float prob = std::stof(numbers[1]);

                    if ((dim >= 10 && dim <= 30) && (prob >= 0 && prob <= 1)) {
                        this->board->generate(dim, prob);
                    } else {
                        Helper::printInvalidInput();
                    }
                } else {
                    Helper::printInvalidInput();
                }
            } else {
                // Split the input into tokens
                std::vector<std::string> tokens;
                Helper::splitString(input, tokens, " ");

                if ((tokens.size() > 0
                     && tokens.size() <= 2)
                    && tokens[0] == COMMAND_INIT) {
                    Helper::splitString(tokens[1], tokens, ",");
                    if (Helper::isNumber(tokens[0])
                        && Helper::isNumber(tokens[1])
                        && StringIsDirection(tokens[2])) {
                        int x = std::stoi(tokens[0]);
                        int y = std::stoi(tokens[1]);
                        Position* position = new Position(x,y);
                        if (board->placePlayer(*position)) {
                            Direction direction = NORTH;
                            if (tokens[2] == DIRECTION_NORTH) {
                                direction = NORTH;
                            } else if (tokens[2] == DIRECTION_EAST) {
                                direction = EAST;
                            } else if (tokens[2] == DIRECTION_SOUTH) {
                                direction = SOUTH;
                            } else if (tokens[2] == DIRECTION_WEST) {
                                direction = WEST;
                            } else {
                                Helper::printInvalidInput();
                            }
                            player->initialisePlayer(position, direction);
                            isInitializingPlayer = true;
                            isRunning = false;
                        } else {
                            Helper::printInvalidInput();
                        }
                    } else {
                        Helper::printInvalidInput();
                    }
                } else {
                    Helper::printInvalidInput();
                }
            }
        }
        else {
            Helper::printInvalidInput();
        }
    }
    return isInitializingPlayer;
}

// Play the game
void Game::play()
{
    bool isRunning = true;

    while (isRunning) {
        board->display(player); // Display the board

        // Print the instruction menu for player
        std::cout << "At this stage of the program, "
                     "only four commands are acceptable:" << std::endl;
        std::cout << COMMAND_FORWARD << " (or f)" << std::endl;
        std::cout << COMMAND_TURN_LEFT << " (or l)" << std::endl;
        std::cout << COMMAND_TURN_RIGHT << " (or r)" << std::endl;
        std::cout << COMMAND_QUIT << std::endl;

        std::string input = Helper::readInput(); // Read user input

        if(!input.empty()) {
            if (input == COMMAND_QUIT) {
                // Check if the user wants to quit, display the moves
                isRunning = false;
                std::cout << "Player's moves: " << player->moves << std::endl;
            }
                // Check if the want to turn the specified direction
            else if (input == COMMAND_TURN_LEFT
                     || input == COMMAND_TURN_LEFT_SHORTCUT) {
                player->turnDirection(TurnDirection::TURN_LEFT);
            } else if (input == COMMAND_TURN_RIGHT
                       || input == COMMAND_TURN_RIGHT_SHORTCUT) {
                player->turnDirection(TurnDirection::TURN_RIGHT);
            } else if (input == COMMAND_FORWARD
                       || input == COMMAND_FORWARD_SHORTCUT) {
                // Move the player forward and check the next situation
                PlayerMove move = board->movePlayerForward(player);

                // Check if the next move is blocked
                if (move == CELL_BLOCKED) {
                    std::cout << "Error: Unable to move "
                                 "- cell is blocked" << std::endl;
                }
                    // Check if the next move is out of the bound
                else if (move == OUTSIDE_BOUNDS) {
                    std::cout<<"The vacuum cleaner is at the edge of the board and"
                               " cannot move further in that direction"<<std::endl;
                } else {
                    std::cout << "Move successfully" << std::endl;
                }
            }  else {
                Helper::printInvalidInput();
            }
        }
        else {
            Helper::printInvalidInput();
        }
    }
}

// Check if the input represents a valid direction
bool Game::StringIsDirection(const std::string& string) {
    return string == DIRECTION_NORTH
           || string == DIRECTION_SOUTH
           || string == DIRECTION_EAST
           || string == DIRECTION_WEST;
};