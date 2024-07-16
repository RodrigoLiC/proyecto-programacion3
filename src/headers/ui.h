//src/headers/ui.h
#ifndef PROYECTO_PROGRAMACION3_UI_H
#define PROYECTO_PROGRAMACION3_UI_H

#include "database.h"
#include "search.h"
#include "trie.h"
#include "utility.h"
#include "load.h"
#include "user.h"

/* Base menu class*/
class Menu {
public:
    virtual void display() = 0;
    virtual void handleInput(User& user, Database* db) = 0;
};

// Selection Menu Class
class MovieSelectionMenu : public Menu {
private:
    std::vector<int> indexes;
    int page = 0;

public:
    MovieSelectionMenu(const std::vector<int>& idx) : indexes(idx) {}

    void display() override {
        Database* db = Database::getInstance();
        int start = page * 5;
        int end = start + 5;
        for (int i = start; i < end && i < indexes.size(); ++i) {
            std::cout << i + 1 << ". ";
            MovieFactory::displayMovie(MovieFactory::PREVIEW, db->getMovies()[indexes[i]]);
        }

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
    }

    void handleInput(User& user, Database* db) override {
        bool continueSearching = true;
        while (continueSearching) {
            display();

            int choice;
            while (true) {
                std::string input;
                std::getline(std::cin, input);
                try {
                    choice = std::stoi(input);
                    if (choice >= 1 && choice <= 4) {
                        break;
                    } else {
                        std::cout << "Invalid choice. Please try again: ";
                    }
                } catch (const std::invalid_argument&) {
                    std::cout << "Invalid choice. Please try again: ";
                }
            }

            switch (choice) {
                case 1: {
                    std::cout << "Enter the number of the movie to select: ";
                    int movieChoice;
                    while (true) {
                        std::string input;
                        std::getline(std::cin, input);
                        try {
                            movieChoice = std::stoi(input);
                            if (movieChoice > 0 && movieChoice <= 5 && (page * 5 + movieChoice - 1) < indexes.size()) {
                                break;
                            } else {
                                std::cout << "Invalid choice. Please try again: ";
                            }
                        } catch (const std::invalid_argument&) {
                            std::cout << "Invalid choice. Please try again: ";
                        }
                    }

                    int movieIndex = indexes[page * 5 + movieChoice - 1];
                    MovieFactory::displayMovie(MovieFactory::FULL, db->getMovies()[movieIndex]);

                    int userChoice;
                    std::cout << "Options:\n1. Like\n2. Watch Later\n3. Return to Search\n4. Return to Main Menu\n";
                    std::cout << "Enter your choice: ";
                    while (true) {
                        std::string input;
                        std::getline(std::cin, input);
                        try {
                            userChoice = std::stoi(input);
                            if (userChoice >= 1 && userChoice <= 4) {
                                break;
                            } else {
                                std::cout << "Invalid choice. Please try again: ";
                            }
                        } catch (const std::invalid_argument&) {
                            std::cout << "Invalid choice. Please try again: ";
                        }
                    }

                    if (userChoice == 4) {
                        return; // Return to main menu
                    } else {
                        continueSearching = handleUserChoice(userChoice, movieIndex, user);
                    }
                    break;
                }
                case 2:
                    if ((page + 1) * 5 < indexes.size()) {
                        ++page; // Go to next 5 movies
                    }
                    break;
                case 3:
                    if (page > 0) {
                        --page; // Go to previous 5 movies
                    }
                    break;
                case 4:
                    return; // Return to main menu
            }
        }
    }

    bool handleUserChoice(int choice, int movieIndex, User& user) {
        switch (choice) {
            case 1:
                user.likeMovie(movieIndex);
                break;
            case 2:
                user.addWatchLater(movieIndex);
                break;
            case 3:
                return true;
            default:
                std::cout << "Invalid choice. Returning to search...\n";
                return false;
        }

        int nextChoice;
        std::cout << "Options:\n1. Continue Searching\n2. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        while (true) {
            std::string input;
            std::getline(std::cin, input);
            try {
                nextChoice = std::stoi(input);
                if (nextChoice == 1 || nextChoice == 2) {
                    break;
                } else {
                    std::cout << "Invalid choice. Please try again: ";
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid choice. Please try again: ";
            }
        }

        return nextChoice == 1;
    }
};



// Movie Search Menu Class
class MovieSearchMenu : public Menu {
public:
    void display() override {
        std::cout << "\nSearch:\n";
        std::cout << "1. Search by word\n";
        std::cout << "2. Search by tags\n";
        std::cout << "3. Back to main menu\n";
        std::cout << "Enter your choice: ";
    }

    void handleInput(User& user, Database* db) override {
        int option;
        while (true) {
            std::string input;
            std::getline(std::cin, input);
            try {
                option = std::stoi(input);
                if (option >= 1 && option <= 3) {
                    break;
                } else {
                    std::cout << "Invalid choice. Please try again: ";
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid choice. Please try again: ";
            }
        }

        switch (option) {
            case 1: {
                std::cout << "\nEnter part of the movie name: ";
                std::string input;
                getline(std::cin, input);

                MovieSearchCommand searchCommand;
                std::vector<int> indexes = searchCommand.execute(input, db);

                if (indexes.empty()) {
                    std::cout << "No movies found for the given input." << std::endl;
                } else {
                    MovieSelectionMenu selectionMenu(indexes);
                    selectionMenu.handleInput(user, db);
                }
                break;
            }
            case 2: {
                std::vector<std::string> tags = {
                        "cult", "horror", "gothic", "murder", "atmospheric", "violence", "romantic",
                        "inspiring", "stupid", "feel-good", "cruelty", "dramatic", "action",
                        "revenge", "sadist", "queer", "flashback", "mystery", "suspenseful",
                        "neo noir", "prank", "psychedelic", "tragedy", "autobiographical",
                        "home movie", "good versus evil", "depressing", "realism", "boring",
                        "haunting", "sentimental", "paranormal", "historical", "storytelling",
                        "comedy", "fantasy", "philosophical", "adult comedy", "cute",
                        "entertaining", "bleak", "humor", "plot twist", "christian film",
                        "pornographic", "insanity", "brainwashing", "sci-fi", "dark",
                        "claustrophobic", "psychological", "melodrama", "historical fiction",
                        "absurd", "satire", "alternate reality", "alternate history",
                        "comic", "grindhouse film", "thought-provoking", "clever", "western",
                        "blaxploitation", "whimsical", "intrigue", "allegory", "anti war",
                        "avant garde", "suicidal", "magical realism", "non fiction"
                };
                std::cout << "\nAvailable tags:\n";
                for (const auto& tag : tags) {
                    std::cout << "[" << tag << "] ";
                }
                std::cout << "\nWrite a tag: ";
                std::string input;
                getline(std::cin, input);

                if (std::find(tags.begin(), tags.end(), input) != tags.end()) {
                    TagSearchCommand searchCommand;
                    std::vector<int> indexes = searchCommand.execute(input, db);

                    if (indexes.empty()) {
                        std::cout << "No movies found for the given tags." << std::endl;
                    } else {
                        MovieSelectionMenu selectionMenu(indexes);
                        selectionMenu.handleInput(user, db);
                    }
                } else {
                    int choice;
                    std::cout << "Invalid tag. Options:\n1. Try again\n2. Exit\n";
                    std::cout << "Enter your choice: ";
                    while (true) {
                        std::string input;
                        std::getline(std::cin, input);
                        try {
                            choice = std::stoi(input);
                            if (choice == 1 || choice == 2) {
                                break;
                            } else {
                                std::cout << "Invalid choice. Please try again: ";
                            }
                        } catch (const std::invalid_argument&) {
                            std::cout << "Invalid choice. Please try again: ";
                        }
                    }
                    if (choice == 1) {
                        handleInput(user, db);
                    }
                }
                break;
            }
            case 3:
                return; // Back to main menu
        }
    }
};

// Main Menu Class
class MainMenu : public Menu {
public:
    void display() override {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Show Liked Movies\n";
        std::cout << "2. Show Watch Later Movies\n";
        std::cout << "3. Search Movies\n";
        std::cout << "4. Show Recommendations\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
    }

    void handleInput(User& user, Database* db) override {
        int option;
        while (true) {
            std::string input;
            std::getline(std::cin, input);
            try {
                option = std::stoi(input);
                if (option >= 1 && option <= 5) {
                    break;
                } else {
                    std::cout << "Invalid choice. Please try again: ";
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid choice. Please try again: ";
            }
        }

        switch (option) {
            case 1:
                user.showLikedMovies(db);
                break;
            case 2:
                user.showWatchLaterMovies(db);
                break;
            case 3: {
                MovieSearchMenu searchMenu;
                searchMenu.display();
                searchMenu.handleInput(user, db);
                break;
            }
            case 4:
                std::cout << "Por implementar.\n";
//                user.showRecommendations(db);
                break;
            case 5:
                std::cout << "Exiting...\n";
                exit(0);
        }
    }
};











//void displaySearchResults(const std::vector<int>& indexes, Database* db, int start, int end) {
//    for (int i = start; i < end && i < indexes.size(); i++) {
//        std::cout << i + 1 << ". ";
//        MovieFactory::displayMovie(MovieFactory::PREVIEW,db->getMovies()[indexes[i]]);
//    }
//}
//
//bool handleUserChoice(int choice, int movieIndex, User& user) {
//    bool continueSearching = true;
//    switch (choice) {
//        case 1:
//            user.likeMovie(movieIndex);
//            break;
//        case 2:
//            user.addWatchLater(movieIndex);
//            break;
//        case 3:
//            std::cout << "Returning to search...\n";
//            return true;
//        default:
//            std::cout << "Invalid choice. Returning to search...\n";
//            return true; // Continue searching
//    }
//
//    // After liking or adding to watch later, ask if the user wants to continue searching or return to main menu
//    int nextChoice;
//    std::cout << "Options:\n1. Continue Searching\n2. Return to Main Menu\n";
//    std::cout << "Enter your choice: ";
//    std::cin >> nextChoice;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
//
//    if (nextChoice == 2) {
//        continueSearching = false; // Return to main menu
//    }
//
//    return continueSearching;
//}
//
//void showMenu(User& user, Database* db) {
//    int option = 0;
//    while (option != 4) {
//        std::cout << "\nMain Menu:\n";
//        std::cout << "1. Show Liked Movies\n";
//        std::cout << "2. Show Watch Later Movies\n";
//        std::cout << "3. Search Movies\n";
//        std::cout << "4. Exit\n";
//        std::cout << "Enter your choice: ";
//        std::cin >> option;
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
//
//        switch (option) {
//            case 1:
//                user.showLikedMovies(db);
//                break;
//            case 2:
//                user.showWatchLaterMovies(db);
//                break;
//            case 3:
//                return; // Exit the menu to search movies
//            case 4:
//                std::cout << "Exiting...\n";
//                break;
//            default:
//                std::cout << "Invalid choice. Please try again.\n";
//                break;
//        }
//    }
//}
//
//bool movieSelectionMenu(const std::vector<int>& indexes, Database* db, User& user) {
//    int page = 0;
//    bool continueSearching = true;
//    while (continueSearching) {
//        int start = page * 5;
//        int end = start + 5;
//        displaySearchResults(indexes, db, start, end);
//
//        std::cout << "\nOptions:\n";
//        std::cout << "1. Select Movie\n";
//        if (end < indexes.size()) {
//            std::cout << "2. See Next 5 Movies\n";
//        }
//        if (page > 0) {
//            std::cout << "3. See Previous 5 Movies\n";
//        }
//        std::cout << "4. Return to Main Menu\n";
//        std::cout << "Enter your choice: ";
//        int choice;
//        std::cin >> choice;
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
//
//        if (choice == 1) {
//            std::cout << "Enter the number of the movie to select: ";
//            int movieChoice;
//            std::cin >> movieChoice;
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
//
//            if (movieChoice > 0 && movieChoice <= 5 && (start + movieChoice - 1) < indexes.size()) {
//                int movieIndex = indexes[start + movieChoice - 1];
//                MovieFactory::displayMovie(MovieFactory::FULL,db->getMovies()[movieIndex]);
//                int userChoice;
//                std::cout << "Options:\n1. Like\n2. Watch Later\n3. Return to Search\n4. Return to Main Menu\n";
//                std::cout << "Enter your choice: ";
//                std::cin >> userChoice;
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
//
//                if (userChoice == 4) {
//                    return true; // Return to main menu
//                } else {
//                    if (!handleUserChoice(userChoice, movieIndex, user)) {
//                        return true; // Return to main menu
//                    }
//                }
//            } else {
//                std::cout << "Invalid choice. Returning to search...\n";
//                continueSearching = false; // Invalid choice, return to search
//            }
//        } else if (choice == 2 && end < indexes.size()) {
//            page++; // Go to next 5 movies
//        } else if (choice == 3 && page > 0) {
//            page--; // Go to previous 5 movies
//        } else if (choice == 4) {
//            return true; // Return to main menu
//        } else {
//            std::cout << "Invalid choice. Returning to search...\n";
//            continueSearching = false; // Invalid choice, return to search
//        }
//    }
//    return false;
//}



#endif