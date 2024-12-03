#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
        {
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
                { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY },
                { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
        };

const vector<vector<Cell>> Board::BOARD_2 =
        {
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
                { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
                { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY },
                { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
                { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
        };

// Allocate a vector for board with default board dimension rows and columns.
// Each element of the board is initialized to empty
Board::Board()
{
    this->board = new std::vector<std::vector<Cell>>(10,
                                                     vector<Cell>(10, EMPTY));
}

// Deallocate the memory for the board vector
Board::~Board()
{
    delete board;
}

// Load the specified board by assigning the corresponding predefined board
void Board::load(int boardId)
{
    if (boardId == 1) {
        *board = BOARD_1;
    } else if (boardId == 2) {
        *board = BOARD_2;
    }
}

void Board::generate(int dim, float prob) {
    if (this->board) {
        delete this->board;
        this->board = nullptr;
    }

    this->board = new std::vector<std::vector<Cell>>(dim,
                                                     vector<Cell>(dim, EMPTY));

    int seed = 100;
    std::default_random_engine engine(seed);
    std::uniform_real_distribution<float> uniform_dist(0.0, 1.0);

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            float value = uniform_dist(engine);
            if (value <= prob) {
                (*board)[i][j] = BLOCKED;
            }
        }
    }
}

bool Board::placePlayer(Position position)
{
    bool placeSuccessfully = true;
    int size = (int) this->board->size();
    
    // Check if the position is within the board or boundaries or if it's blocked
    if (position.x < 0 || position.x >= size ||
        position.y < 0 || position.y >= size ||
        (*board)[position.y][position.x] == BLOCKED) {
        placeSuccessfully = false;
    } else {
        // Place the player on the board at the exact position
        (*board)[position.y][position.x] = PLAYER;
    }

    return placeSuccessfully;
}

PlayerMove Board::movePlayerForward(Player* player)
{
    // Get the position where the player will move next
    Position nextForwardPosition = player->getNextForwardPosition();
    PlayerMove playerMove = PLAYER_MOVED;

    int size = (int) this->board->size();

    // Check if the next position is outside the board boundaries
    if ((nextForwardPosition.x < 0
         || nextForwardPosition.x >= size)
        || (nextForwardPosition.y < 0
            || nextForwardPosition.y >= size)) {
        playerMove = OUTSIDE_BOUNDS;
    }
        // Check if the next position is being blocked
    else if ((*board)[nextForwardPosition.y]
             [nextForwardPosition.x] == BLOCKED) {
        playerMove = CELL_BLOCKED;
    }

    // Check if the player can move,
    // update the position of the player on the board accordingly
    if (playerMove == PLAYER_MOVED) {
        (*board)[player->position.y][player->position.x] = EMPTY;
        player->updatePosition(nextForwardPosition);
        (*board)[player->position.y][player->position.x] = PLAYER;
    }
    return playerMove;
}

void Board::display(Player* player)
{
    int size = (int) this->board->size();
    // Display the column numbers
    std::cout << "  ";
    for (int i = 0; i < size; ++i) {
        std::cout << LINE_OUTPUT << int(i/10);
    }
    std::cout << LINE_OUTPUT;
    std::cout << std::endl;

    std::cout << "  ";
    for (int i = 0; i < size; i++) {
        std::cout << LINE_OUTPUT << int(i % 10);
    }
    std::cout << LINE_OUTPUT;
    std::cout << std::endl;

    for (int i = 0; i < size; ++i) {

        // Display the row number
        std::cout << int(i / 10) << int(i % 10) << LINE_OUTPUT;

        for (int j = 0; j < size; ++j) {
            if ((*board)[i][j] == EMPTY) {
                // Display an empty cell
                std::cout << EMPTY_OUTPUT << LINE_OUTPUT;
            } else if ((*board)[i][j] == BLOCKED) {
                // Display a blocked cell
                std::cout << BLOCKED_OUTPUT << LINE_OUTPUT;
            } else if ((*board)[i][j] == PLAYER) {
                // Display the player's direction
                player->displayDirection();
            }
        }
        std::cout << std::endl;
    }
}

