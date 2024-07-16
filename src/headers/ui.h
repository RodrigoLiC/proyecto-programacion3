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
    vector<int> indexes;
    int page = 0;

public:
    MovieSelectionMenu(const vector<int>& idx) : indexes(idx) {}

    void display() override {
        Database* db = Database::getInstance();
        int start = page * 5;
        int end = start + 5;
        for (int i = start; i < end && i < indexes.size(); ++i) {
            cout << i + 1 << ". ";
            MovieFactory::displayMovie(MovieFactory::PREVIEW, db->getMovies()[indexes[i]]);
        }

        cout << "\nOptions:\n";
        cout << "1. Select Movie\n";
        if (end < indexes.size()) {
            cout << "2. See Next 5 Movies\n";
        }
        if (page > 0) {
            cout << "3. See Previous 5 Movies\n";
        }
        cout << "4. Return to Main Menu\n";
        cout << "Enter your choice: ";
    }

    void handleInput(User& user, Database* db) override {
        bool continueSearching = true;
        while (continueSearching) {
            display();

            int choice;
            while (true) {
                string input;
                getline(cin, input);
                try {
                    choice = stoi(input);
                    if (choice >= 1 && choice <= 4) {
                        break;
                    } else {
                        cout << "Invalid choice. Please try again: ";
                    }
                } catch (const invalid_argument&) {
                    cout << "Invalid choice. Please try again: ";
                }
            }

            switch (choice) {
                case 1: {
                    cout << "Enter the number of the movie to select: ";
                    int movieChoice;
                    while (true) {
                        string input;
                        getline(cin, input);
                        try {
                            movieChoice = stoi(input);
                            if (movieChoice > 0 && movieChoice <= 5 && (page * 5 + movieChoice - 1) < indexes.size()) {
                                break;
                            } else {
                                cout << "Invalid choice. Please try again: ";
                            }
                        } catch (const invalid_argument&) {
                            cout << "Invalid choice. Please try again: ";
                        }
                    }

                    int movieIndex = indexes[page * 5 + movieChoice - 1];
                    MovieFactory::displayMovie(MovieFactory::FULL, db->getMovies()[movieIndex]);

                    int userChoice;
                    cout << "Options:\n1. Like\n2. Watch Later\n3. Return to Search\n4. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    while (true) {
                        string input;
                        getline(cin, input);
                        try {
                            userChoice = stoi(input);
                            if (userChoice >= 1 && userChoice <= 4) {
                                break;
                            } else {
                                cout << "Invalid choice. Please try again: ";
                            }
                        } catch (const invalid_argument&) {
                            cout << "Invalid choice. Please try again: ";
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
                cout << "Invalid choice. Returning to search...\n";
                return false;
        }

        int nextChoice;
        cout << "Options:\n1. Continue Searching\n2. Return to Main Menu\n";
        cout << "Enter your choice: ";
        while (true) {
            string input;
            getline(cin, input);
            try {
                nextChoice = stoi(input);
                if (nextChoice == 1 || nextChoice == 2) {
                    break;
                } else {
                    cout << "Invalid choice. Please try again: ";
                }
            } catch (const invalid_argument&) {
                cout << "Invalid choice. Please try again: ";
            }
        }

        return nextChoice == 1;
    }
};



// Movie Search Menu Class
class MovieSearchMenu : public Menu {
public:
    void display() override {
        cout << "\nSearch:\n";
        cout << "1. Search by word\n";
        cout << "2. Search by tags\n";
        cout << "3. Back to main menu\n";
        cout << "Enter your choice: ";
    }

    void handleInput(User& user, Database* db) override {
        int option;
        while (true) {
            string input;
            getline(cin, input);
            try {
                option = stoi(input);
                if (option >= 1 && option <= 3) {
                    break;
                } else {
                    cout << "Invalid choice. Please try again: ";
                }
            } catch (const invalid_argument&) {
                cout << "Invalid choice. Please try again: ";
            }
        }

        switch (option) {
            case 1: {
                cout << "\nEnter part of the movie name: ";
                string input;
                getline(cin, input);

                MovieSearchCommand searchCommand;
                vector<int> indexes = searchCommand.execute(input, db);

                if (indexes.empty()) {
                    cout << "No movies found for the given input." << endl;
                } else {
                    MovieSelectionMenu selectionMenu(indexes);
                    selectionMenu.handleInput(user, db);
                }
                break;
            }
            case 2: {
                vector<string> tags = {
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
                cout << "\nAvailable tags:\n";
                for (const auto& tag : tags) {
                    cout << "[" << tag << "] ";
                }
                cout << "\nWrite a tag: ";
                string input;
                getline(cin, input);

                if (find(tags.begin(), tags.end(), input) != tags.end()) {
                    TagSearchCommand searchCommand;
                    vector<int> indexes = searchCommand.execute(input, db);

                    if (indexes.empty()) {
                        cout << "No movies found for the given tags." << endl;
                    } else {
                        MovieSelectionMenu selectionMenu(indexes);
                        selectionMenu.handleInput(user, db);
                    }
                } else {
                    int choice;
                    cout << "Invalid tag. Options:\n1. Try again\n2. Exit\n";
                    cout << "Enter your choice: ";
                    while (true) {
                        string input;
                        getline(cin, input);
                        try {
                            choice = stoi(input);
                            if (choice == 1 || choice == 2) {
                                break;
                            } else {
                                cout << "Invalid choice. Please try again: ";
                            }
                        } catch (const invalid_argument&) {
                            cout << "Invalid choice. Please try again: ";
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
        cout << "\nMain Menu:\n";
        cout << "1. Show Liked Movies\n";
        cout << "2. Show Watch Later Movies\n";
        cout << "3. Search Movies\n";
        cout << "4. Show Recommendations\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
    }

    void handleInput(User& user, Database* db) override {
        int option;
        while (true) {
            string input;
            getline(cin, input);
            try {
                option = stoi(input);
                if (option >= 1 && option <= 5) {
                    break;
                } else {
                    cout << "Invalid choice. Please try again: ";
                }
            } catch (const invalid_argument&) {
                cout << "Invalid choice. Please try again: ";
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
                cout<<"Showing Recommendations...\n";
                user.showRecommendations(db);
                break;
            case 5:
                cout << "Exiting...\n";
                exit(0);
        }
    }
};


#endif