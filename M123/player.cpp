#include "player.h"
#include "game.h"

// Set default constructor for position
Position::Position()
{
    x = 0;
    y = 0;
}

// Parameterized constructor for position
Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Set default constructor for player
Player::Player()
{
    moves = 0;
}

// Initilize player's position, direction and moves
void Player::initialisePlayer(Position* position, Direction direction)
{
    this->position = *position;
    this->direction = direction;
    this->moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{
    // Check if the player turns right
    if (turnDirection == TurnDirection::TURN_RIGHT) {
        // Check the direction of player when turning right
        if (direction == Direction::NORTH) {
            direction = Direction::EAST;
        } else if (direction == Direction::EAST) {
            direction = Direction::SOUTH;
        } else if (direction == Direction::SOUTH) {
            direction = Direction::WEST;
        } else if (direction == Direction::WEST) {
            direction = Direction::NORTH;
        }
    }

        // Check if the player turns left
    else if (turnDirection == TurnDirection::TURN_LEFT) {
        // Check the direction of player when turning left
        if (direction == Direction::NORTH) {
            direction = Direction::WEST;
        } else if (direction == Direction::WEST) {
            direction = Direction::SOUTH;
        } else if (direction == Direction::SOUTH) {
            direction = Direction::EAST;
        } else if (direction == Direction::EAST) {
            direction = Direction::NORTH;
        }
    }
}

Position Player::getNextForwardPosition()
{
    Position nextForwardPosition = this->position;

    // Calculate the position one step forward when player is in the direction
    if (this->direction == Direction::NORTH) {
        nextForwardPosition.y--;
    } else if (this->direction == Direction::EAST) {
        nextForwardPosition.x++;
    } else if (this->direction == Direction::SOUTH) {
        nextForwardPosition.y++;
    } else if (this->direction == Direction::WEST) {
        nextForwardPosition.x--;
    }
    return nextForwardPosition;
}

// Update player's position and increment moves counter
void Player::updatePosition(Position position)
{
    this->position = position;
    moves++;
}

// Display arrow indicating the direction
void Player::displayDirection()
{
    if (direction == Direction::NORTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH << LINE_OUTPUT;
    } else if (direction == Direction::EAST) {
        std::cout << DIRECTION_ARROW_OUTPUT_EAST << LINE_OUTPUT;
    } else if (direction == Direction::SOUTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH << LINE_OUTPUT;
    } else if (direction == Direction::WEST) {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST << LINE_OUTPUT;
    }
}
