// During implementation, I approached game development by starting with the main menu,
// where the player can choose between playing the game, viewing information, or exiting.
// Once the player chooses to play the game, instructions are displayed,
// followed by panels where the player can enter and play.
// However, I ran into some problems during the process.
// Displaying the tables did not meet my expectations
// and I had difficulty with the use of while loops.
// For example, when the player chooses to load table 1 and then wants to load table 2,
// the inner loop is accidentally exited,
// causing the program to switch to the outer loop and not load table 2.
// For potential improvements functionality,
// further improvements can be made to the on-board display to ensure better visual
// and intuitive user interaction.
// Additionally, refining the handling of while loops will improve overall usability
// and prevent unwanted behavior.

#include "game.h"
#include "helper.h"

using std::string;

// Function to display the main menu
void displayMenu() {
    std::cout << "Welcome to Vacuum Cleaning Game!" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "1. Play Game" << std::endl;
    std::cout << "2. Show student information" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "\nPlease enter your choice: ";
}

// Function display the student information
void showStudentInformation(string name, string id, string email){
    std::cout << "-------------------" << std::endl;
    std::cout << "Name: "<< name << std::endl;
    std::cout << "Student ID: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "-------------------" << std::endl;
}

int main()
{
    bool  isRunning = true;
    while (isRunning) {
        displayMenu(); // Display the main menu

        string input = Helper::readInput(); // Read the input
        if (input == "1") {
            // If the input is 1, the game will start
            Game game;
            game.start();
        } else if (input == "2") {
            // If the input is 2, show the student information
            showStudentInformation("Thuy Linh Do",
                                   "s3927777",
                                   "s3927777@student.rmit.edu.au");
        } else if (input == "3") {
            // If the input is 3, exit the loop
            isRunning = false;
        } else {
            Helper::printInvalidInput(); // Display message for invalid input
        }

    };

    std::cout << "\nGood bye!\n\n";

    return EXIT_SUCCESS;
}