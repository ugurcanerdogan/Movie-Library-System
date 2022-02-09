//
// Library System header file.
//

#ifndef ASG2_LIBRARYSYSTEM_H
#define ASG2_LIBRARYSYSTEM_H

#include <iostream> // Including necessary library files.
#include <string>
#include <fstream>

using namespace std;

struct MovieNode {      // Struct for each movie node.
    int movieID;
    string movieTitle;
    string movieYear;
    MovieNode* next;
};

struct UserNode{    // Struct for each user node.
    int userID;
    string userName;
    UserNode* next;
    UserNode* prev;
    MovieNode* movie;
};

class LibrarySystem{
    public:
        MovieNode* movieLast;   // movieLast is the last movie of unchecked movies lists. nullptr if list is void.
        UserNode* userLast;     // userLast is the last user of user lists. nullptr if list is void.

        LibrarySystem();    // Constructor of library system class. Also operates readcommand operations.
        ~LibrarySystem();   // Destructor of library system class.

        // add movie function to add movie to movie list.
        void addMovie(const int movieID, const string movieTitle, const string year);
        // delete movie function to delete movie from all movies.
        void deleteMovie(const int movieID);
        // add user function to add use to user list.
        void addUser(const int userID, const string userName);
        // delete user function to delete  user from user list.
        void deleteUser(const int userID);
        // check out function for purchase process of the user.
        void checkoutMovie(const int movieID,const int userID);
        // return function for returning process of the film.
        void returnMovie(const int movieID);
        // show all movies function to show all movies and their details in the program.
        void showAllMovies();
        // show movie function to show a specific movie and its details.
        void showMovie(const int movieID);
        // show user function for showing a specific user's details.
        void showUser(const int userID);
        // command reading function in order to operate commands of command file.
        void readCommands();
};

#endif //ASG2_LIBRARYSYSTEM_H
