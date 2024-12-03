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
    this->board = new std::vector<std::vector<Cell>>(DEFAULT_BOARD_DIMENSION,
                                                     vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY));
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

bool Board::placePlayer(Position position)
{
    bool placeSuccessfully = true;

    // Check if the position is within the board or boundaries or if it's blocked
    if (position.x < 0 || position.x >= DEFAULT_BOARD_DIMENSION ||
        position.y < 0 || position.y >= DEFAULT_BOARD_DIMENSION ||
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

    // Check if the next position is outside the board boundaries
    if ((nextForwardPosition.x < 0
         || nextForwardPosition.x >= DEFAULT_BOARD_DIMENSION)
        || (nextForwardPosition.y < 0
            || nextForwardPosition.y >= DEFAULT_BOARD_DIMENSION)) {
        playerMove = OUTSIDE_BOUNDS;
    }
        // Check if the next position is being blocked
    else if ((*board)[nextForwardPosition.y]
             [nextForwardPosition.x] == BLOCKED) {
        playerMove = CELL_BLOCKED;
    }

    // Check if the player can move, update the position of the player on the board accordingly
    if (playerMove == PLAYER_MOVED) {
        (*board)[player->position.y][player->position.x] = EMPTY;
        player->updatePosition(nextForwardPosition);
        (*board)[player->position.y][player->position.x] = PLAYER;
    }
    return playerMove;
}

void Board::display(Player* player)
{
    // Display the column numbers
    std::cout << LINE_OUTPUT << " ";
    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; ++i) {
        std::cout << LINE_OUTPUT << i;
    }
    std::cout << LINE_OUTPUT;
    std::cout << std::endl;

    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; ++i) {

        // Display the row number
        std::cout << LINE_OUTPUT << i << LINE_OUTPUT;

        for (int j = 0; j < DEFAULT_BOARD_DIMENSION; ++j) {
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
