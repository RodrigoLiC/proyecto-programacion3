#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "headers/database.h"
#include "headers/search.h"
#include "headers/trie.h"
#include "headers/ui.h"
#include "headers/utility.h"
#include "headers/load.h"
#include "headers/user.h"

void displaySearchResults(const std::vector<int>& indexes, Database* db, int start, int end) {
    for (int i = start; i < end && i < indexes.size(); i++) {
        std::cout << i + 1 << ". ";
        db->getMovies()[indexes[i]].imprimirPreview();
    }
}

bool handleUserChoice(int choice, int movieIndex, User& user) {
    bool continueSearching = true;
    switch (choice) {
        case 1:
            user.likeMovie(movieIndex);
            break;
        case 2:
            user.addWatchLater(movieIndex);
            break;
        case 3:
            std::cout << "Returning to search...\n";
            return true; // Continue searching
        default:
            std::cout << "Invalid choice. Returning to search...\n";
            return true; // Continue searching
    }

    // After liking or adding to watch later, ask if the user wants to continue searching or return to main menu
    int nextChoice;
    std::cout << "Options:\n1. Continue Searching\n2. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> nextChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    if (nextChoice == 2) {
        continueSearching = false; // Return to main menu
    }

    return continueSearching;
}

void showMenu(User& user, Database* db) {
    int option = 0;
    while (option != 4) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Show Liked Movies\n";
        std::cout << "2. Show Watch Later Movies\n";
        std::cout << "3. Search Movies\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        switch (option) {
            case 1:
                user.showLikedMovies(db);
                break;
            case 2:
                user.showWatchLaterMovies(db);
                break;
            case 3:
                return; // Exit the menu to search movies
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

bool movieSelectionMenu(const std::vector<int>& indexes, Database* db, User& user) {
    int page = 0;
    bool continueSearching = true;
    while (continueSearching) {
        int start = page * 5;
        int end = start + 5;
        displaySearchResults(indexes, db, start, end);

        std::cout << "\nOptions:\n";
        std::cout << "1. Select Movie\n";
        if (end < indexes.size()) {
            std::cout << "2. See Next 5 Movies\n";
        }
        if (page > 0) {
            std::cout << "3. See Previous 5 Movies\n";
        }
        std::cout << "4. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        if (choice == 1) {
            std::cout << "Enter the number of the movie to select: ";
            int movieChoice;
            std::cin >> movieChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

            if (movieChoice > 0 && movieChoice <= 5 && (start + movieChoice - 1) < indexes.size()) {
                int movieIndex = indexes[start + movieChoice - 1];
                db->getMovies()[movieIndex].imprimirPelicula(); // Show full details of the movie
                int userChoice;
                std::cout << "Options:\n1. Like\n2. Watch Later\n3. Return to Search\n4. Return to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> userChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

                if (userChoice == 4) {
                    return true; // Return to main menu
                } else {
                    if (!handleUserChoice(userChoice, movieIndex, user)) {
                        return true; // Return to main menu
                    }
                }
            } else {
                std::cout << "Invalid choice. Returning to search...\n";
                continueSearching = false; // Invalid choice, return to search
            }
        } else if (choice == 2 && end < indexes.size()) {
            page++; // Go to next 5 movies
        } else if (choice == 3 && page > 0) {
            page--; // Go to previous 5 movies
        } else if (choice == 4) {
            return true; // Return to main menu
        } else {
            std::cout << "Invalid choice. Returning to search...\n";
            continueSearching = false; // Invalid choice, return to search
        }
    }
    return false;
}

int main() {
    Database* db = Database::getInstance();
    std::string trieFile = "../datasets/trie_data.txt";

    std::ifstream infile(trieFile);
    if (!infile.good()) {
        std::cout << "No existing trie file found. Loading data and generating trie..." << std::endl;
        load_data();
        db->generateTrie();
        db->saveTrieToFile(trieFile);
    } else {
        load_data();
        std::cout << "Loading trie from file..." << std::endl;
        db->loadTrieFromFile(trieFile);
    }

    User user;
    MovieSearchCommand searchCommand;
    while (true) {
        showMenu(user, db);

        std::string input;
        std::cout << "\nIngrese parte de la pelicula que desea buscar: ";
        getline(std::cin, input);

        std::vector<int> indexes = searchCommand.execute(input, db);

        if (indexes.empty()) {
            std::cout << "No movies found for the given prefix." << std::endl;
        } else {
            if (movieSelectionMenu(indexes, db, user)) {
                continue; // Return to main menu
            }
        }
    }

    return 0;
}
