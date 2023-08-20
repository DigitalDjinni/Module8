// Michael Isenhour

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <stdexcept>

const int EXIT_CHOICE = 4;
const int STARS_COUNT = 28;

// Function to format a number as two digits
std::string formatTwoDigits(int num) {
    return (num < 10) ? "0" + std::to_string(num) : std::to_string(num);
}

// Function to repeat the '*' character for formatting
std::string repeatStars(int num) {
    return std::string(num, '*');
}

// Function to format time in 24-hour format
std::string formatTime24(struct tm time) {
    std::ostringstream oss;
    oss << formatTwoDigits(time.tm_hour) << ":" << formatTwoDigits(time.tm_min) << ":" << formatTwoDigits(time.tm_sec);
    return oss.str();
}

// Function to format time in 12-hour format
std::string formatTime12(struct tm time) {
    std::ostringstream oss;
    int hour = time.tm_hour % 12;
    if (hour == 0) {
        hour = 12; // Change 0 to 12 for 12 AM and 12 PM
    }
    oss << formatTwoDigits(hour) << ":" << formatTwoDigits(time.tm_min) << ":" << formatTwoDigits(time.tm_sec);
    if (time.tm_hour >= 12) {
        oss << " PM";
    }
    else {
        oss << " AM";
    }
    return oss.str();
}

// Function to display both 12-hour and 24-hour time formats side by side with a modified clock border
void displayBothFormats(struct tm time) {
    std::string format12 = formatTime12(time);
    std::string format24 = formatTime24(time);

    std::string starsLine(STARS_COUNT, '*');

    std::cout << starsLine << "           " << starsLine << std::endl;
    std::cout << "*       12 Hour Clock      *           *       24 Hour Clock      *" << std::endl;
    std::cout << "*        " << format12 << "       *" << "           " << "*          "  << format24 << "        *" << std::endl;
    std::cout << starsLine << "           " << starsLine << std::endl;
}

// Function to print out the menu
void printMenu() {
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Add One Hour" << std::endl;
    std::cout << "2. Add One Minute" << std::endl;
    std::cout << "3. Add One Second" << std::endl;
    std::cout << EXIT_CHOICE << ". Exit Program" << std::endl;
}

// Function to validate user input and retrieve the choice
int getUserChoice() {
    int choice;
    std::cout << "Enter your choice: ";
    while (!(std::cin >> choice) || choice < 1 || choice > EXIT_CHOICE) {
        std::cout << "Invalid input. Please enter a valid choice: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

// Function to add one hour to the clock's time
void addOneHour(struct tm& time) {
    time.tm_hour += 1;
    std::mktime(&time); // Normalize the time structure
}

// Function to add one minute to the clock's time
void addOneMinute(struct tm& time) {
    time.tm_min += 1;
    std::mktime(&time); // Normalize the time structure
}

// Function to add one second to the clock's time
void addOneSecond(struct tm& time) {
    time.tm_sec += 1;
    std::mktime(&time); // Normalize the time structure
}

// Function to get user input for the initial time
void getInitialTime(int& initialHour, int& initialMinute, int& initialSecond) {
    while(true) {
        std::cout << "Enter the initial time:" << std::endl;
        std::cout << "Hour (0-23): ";
        std::cin >> initialHour;
        std::cout << "Minute (0-59): ";
        std::cin >> initialMinute;
        std::cout << "Second (0-59): ";
        std::cin >> initialSecond;
        
        // Check for valid input
        if (initialHour >= 0 && initialHour <= 23 && 
            initialMinute >= 0 && initialMinute <= 59 &&
            initialSecond >= 0 && initialSecond <= 59) {
            break; // Exit the loop if input is valid
        } else {
            std::cout << "Invalid input. Please try again.\n";
            std::cin.clear(); // Clear the error flag on cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
        }
    }
}

int main() {
    // Get the initial time from the user
    int initialHour, initialMinute, initialSecond;
    getInitialTime(initialHour, initialMinute, initialSecond);

    // Get the current time
    time_t currentTime = time(NULL);
    struct tm time = *localtime(&currentTime);

    // Set the initial time values
    time.tm_hour = initialHour;
    time.tm_min = initialMinute;
    time.tm_sec = initialSecond;

    // Print out the menu
    printMenu();

    int menuChoice = getUserChoice();

    while (menuChoice != EXIT_CHOICE) {
        // Add the time to the struct based on user input
        try {
            if (menuChoice == 1) {
                addOneHour(time);
            }
            else if (menuChoice == 2) {
                addOneMinute(time);
            }
            else if (menuChoice == 3) {
                addOneSecond(time);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            break;
        }

        // Display both 12-hour and 24-hour time formats side by side
        displayBothFormats(time);

        // Print out the menu
        printMenu();
        menuChoice = getUserChoice();
    }

    std::cout << "Exiting program..." << std::endl;
    return 0;
}