//
// Library System cpp file.
//

#include "LibrarySystem.h" // Including library header file.
#include <vector>          // Including necessary "external" library files.
#include <sstream>

extern ifstream commandFileObj;
extern ofstream outputFileObj;

// Library system constructor with read command function in order to read and operate command
// with given order.
LibrarySystem::LibrarySystem(){
    movieLast = nullptr;
    userLast = nullptr;
    cout << "===Movie Library System===" << endl;
//    cout << endl;

    readCommands();

}

// Read commands function to check every line and words and make operations according to its value.
void LibrarySystem::readCommands() {
    vector<string> tokens;
    vector<string> oldTokens;
    oldTokens.push_back("joker");
    string oldCommandLine;
    string commandLine;

    while (getline(commandFileObj,commandLine)){

        istringstream iss(commandLine);
        string token;
        tokens.clear();
        while(std::getline(iss, token, '\t'))   // but we can specify a different one
            tokens.push_back(token);

        if(commandLine.find("addMovie") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===addMovie() method test===" << endl;
            }
            addMovie(stoi(tokens.at(1)),tokens.at(2),tokens.at(3));
        }
        else if(commandLine.find("deleteMovie") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===deleteMovie() method test===" << endl;
            }
            deleteMovie(stoi(tokens.at(1)));
        }
        else if(commandLine.find("addUser") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===addUser() method test===" << endl;
            }
            addUser(stoi(tokens.at(1)),tokens.at(2));
        }
        else if(commandLine.find("deleteUser") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===deleteUser() method test===" << endl;
            }
            deleteUser(stoi(tokens.at(1)));
        }
        else if(commandLine.find("checkoutMovie") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===checkoutMovie() method test===" << endl;
            }
            checkoutMovie(stoi(tokens.at(1)),stoi(tokens.at(2)));
        }
        else if(commandLine.find("showUser") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===showUser() method test===" << endl;
            }
            showUser(stoi(tokens.at(1)));
        }
        else if(commandLine.find("showMovie") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===showMovie() method test===" << endl;
            }
            showMovie(stoi(tokens.at(1)));
        }
        else if(commandLine.find("showAllMovie") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===showAllMovie() method test===" << endl;
            }
            showAllMovies();
        }
        else if(commandLine.find("returnMovie") != string::npos){
            if(tokens.at(0) != oldTokens.at(0)){
                cout << endl;
                cout << "===returnMovie() method test===" << endl;
            }
            returnMovie(stoi(tokens.at(1)));
        }
        oldTokens.clear();
        istringstream iss2(commandLine);
        string oldToken;
        while(std::getline(iss2, oldToken, '\t'))   // but we can specify a different one
            oldTokens.push_back(oldToken);
    }
    commandFileObj.close();
}

// addMovie function in order to add movie to unchecked movie list. It also checks
// whether the movie with the given ID does belong to any user or not.
void LibrarySystem::addMovie(const int valueID, const string valueTitle, const string valueYear) {
    struct UserNode* startUser;
    if (userLast != nullptr){
        startUser = userLast->next;
        while (startUser != userLast){
            struct MovieNode* startMovie;
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;
                while (startMovie != startUser->movie){
                    if (startMovie->movieID == valueID){
                        cout << "Movie " << valueID << " already existsLAAAAAAN" << endl;
                        return;
                    }
                    startMovie= startMovie->next;
                }
            }
            startUser = startUser->next;
        }
        if (startUser == userLast){
            struct MovieNode* startMovie;
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;
                while (startMovie != startUser->movie){
                    if (startMovie->movieID == valueID){
                        cout << "Movie " << valueID << " already existsLAAAAAAN" << endl;
                        return;
                    }
                    startMovie= startMovie->next;
                }
                if (startMovie == startUser->movie){
                    if (startMovie->movieID == valueID){
                        cout << "Movie " << valueID << " already existsLAAAAAAN" << endl;
                        return;
                    }
                }
            }
        }
    }

    MovieNode *start;
    if (movieLast != nullptr){
        start = movieLast->next;
        /* If List has only one element*/
        if (movieLast->next == movieLast && movieLast->movieID == valueID)
        {
            //cout << "one element in movielist and it is already here" << endl;
            cout << "Movie " << valueID << " already exists" << endl;
            return;
        }
        if (start->movieID == valueID)  /*First Element Search*/
        {
            cout << "Movie " << valueID << " already exists" << endl;
            return;
        }
        while (start->next != movieLast)
        {
            if (start->next->movieID == valueID)
            {
                cout << "Movie " << valueID << " already exists" << endl;
                return;
            }
            start = start->next;
        }
        /*Search of last element*/
        if (start->next->movieID == valueID)
        {
            cout << "Movie " << valueID << " already exists" << endl;
            return;
        }
    }

    if (movieLast == nullptr){
        struct MovieNode *temp = new MovieNode;

        // Assign the data.
        temp->movieID = valueID;
        temp->movieTitle = valueTitle;
        temp->movieYear = valueYear;
        movieLast = temp;

        // Create the link.
        movieLast->next = movieLast;
        cout << "Movie " << valueID << " has been added" << endl;
        return;
    }

    //else create a new node
    struct MovieNode *temp = new MovieNode;

    //assign data to new node
    temp->movieID = valueID;
    temp->movieTitle = valueTitle;
    temp->movieYear = valueYear;

    temp->next = movieLast->next;
    movieLast->next = temp;
    movieLast = temp;
    cout << "Movie " << valueID << " has been added" << endl;
}

// deleteMovie function in order to delete movie from unchecked movie list or users' movies. It also checks
// whether the movie with the given ID does not belong to any user or does.
void LibrarySystem::deleteMovie(const int valueID) {
    struct MovieNode *temp, *start;

//    if (movieLast== nullptr){
//        cout << "No movie in list to delete" << endl;
//        return;
//    }
    if (movieLast != nullptr){
        start = movieLast->next;
        /* If List has only one element*/
        if (movieLast->next == movieLast && movieLast->movieID == valueID)
        {
            temp = movieLast;
            movieLast = nullptr;
            free(temp);
            cout << "Movie " << valueID << " has not been checked out" << endl;
            cout << "Movie " << valueID << " has been deleted" << endl;
            return;
        }
        if (start->movieID == valueID)  /*First Element Deletion*/
        {
            temp = start;
            movieLast->next = start->next;
            free(temp);
            cout << "Movie " << valueID << " has not been checked out" << endl;
            cout << "Movie " << valueID << " has been deleted" << endl;
            return;
        }
        while (start->next != movieLast)
        {
            /*Deletion of Element in between*/
            if (start->next->movieID == valueID)
            {
                temp = start->next;
                start->next = temp->next;
                free(temp);
                cout << "Movie " << valueID << " has not been checked out" << endl;
                cout << "Movie " << valueID << " has been deleted" << endl;
                return;
            }
            start = start->next;
        }
        /*Deletion of last element*/
        if (start->next->movieID == valueID)
        {
            temp = start->next;
            start->next = movieLast->next;
            free(temp);
            movieLast = start;
            cout << "Movie " << valueID << " has not been checked out" << endl;
            cout << "Movie " << valueID << " has been deleted" << endl;
            return;
        }
    }
    struct UserNode* startUser;
    if (userLast != nullptr){
        startUser = userLast->next;
        while (startUser != userLast){
            struct MovieNode* startMovie;
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;

                if (startUser->movie->next == startUser->movie && startUser->movie->movieID == valueID)
                {
                    temp = startUser->movie;
                    startUser->movie = nullptr;
                    free(temp);
                    cout << "Movie " << valueID << " has been checked out"<< endl;
                    cout << "Movie " << valueID << " has been deleted" << endl;
                    return;
                }
                if (startMovie->movieID == valueID)  /*First Element Deletion*/
                {
                    struct MovieNode* temp2;
                    temp2 = startMovie->next;
                    temp = startMovie;
                    startUser->movie->next = temp2;
                    free(temp);
                    cout << "Movie " << valueID << " has been checked out"<< endl;
                    cout << "Movie " << valueID << " has been deleted" << endl;
                    return;
                }
                while (startMovie->next != startUser->movie)
                {
                    /*Deletion of Element in between*/
                    if (startMovie->next->movieID == valueID)
                    {
                        struct MovieNode* temp2;
                        temp2 = startMovie->next->next;
                        temp = startMovie->next;
                        startMovie->next = temp2;
                        free(temp);
                        cout << "Movie " << valueID << " has been checked out"<< endl;
                        cout << "Movie " << valueID << " has been deleted" << endl;
                        return;
                    }
                    startMovie = startMovie->next;
                }
                /*Deletion of last element*/
                if (startMovie->next->movieID == valueID)
                {
                    struct MovieNode* temp2;
                    temp2= startMovie->next->next;
                    temp = startMovie->next;
                    startMovie->next = temp2;
                    free(temp);
                    startUser->movie = startMovie;
                    cout << "Movie " << valueID << " has been checked out"<< endl;
                    cout << "Movie " << valueID << " has been deleted" << endl;
                    return;
                }
            }
            startUser = startUser->next;
        }
        if (startUser == userLast){
            struct MovieNode* startMovie;
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;

                if (startUser->movie->next == startUser->movie && startUser->movie->movieID == valueID)
                {
                    temp = startUser->movie;
                    startUser->movie = nullptr;
                    free(temp);
                    cout << "Movie " << valueID << " has been checked out"<< endl;
                    cout << "Movie " << valueID << " has been deleted" << endl;
                    return;
                }
                if (startMovie->movieID == valueID)  /*First Element Deletion*/
                {
                    struct MovieNode* temp2;
                    temp2 = startMovie->next;
                    temp = startMovie;
                    startUser->movie->next = temp2;
                    free(temp);
                    cout << "Movie " << valueID << " has been checked out"<< endl;
                    cout << "Movie " << valueID << " has been deleted" << endl;
                    return;
                }
                while (startMovie->next != startUser->movie)
                {
                    /*Deletion of Element in between*/
                    if (startMovie->next->movieID == valueID)
                    {
                        struct MovieNode* temp2;
                        temp2 = startMovie->next->next;
                        temp = startMovie->next;
                        startMovie->next = temp2;
                        free(temp);
                        cout << "Movie " << valueID << " has been checked out"<< endl;
                        cout << "Movie " << valueID << " has been deleted" << endl;
                        return;
                    }
                    startMovie = startMovie->next;
                }
                /*Deletion of last element*/
                if (startMovie->next->movieID == valueID)
                {
                    struct MovieNode* temp2;
                    temp2= startMovie->next->next;
                    temp = startMovie->next;
                    startMovie->next = temp2;
                    free(temp);
                    startUser->movie = startMovie;
                    cout << "Movie " << valueID << " has been checked out"<< endl;
                    cout << "Movie " << valueID << " has been deleted" << endl;
                    return;
                }
            }
        }
    }
    cout << "Movie " << valueID << " does not exist" << endl;
}

// addUser function in order to add user to user list. It also checks
// whether the user with the given ID does belong to user list or not.
void LibrarySystem::addUser(const int valueUserID, const string valueUserName) {

    struct UserNode *start;

    if (userLast != nullptr){
        start = userLast->next;
        /* If List has only one element*/
        if (userLast->next == userLast && userLast->userID == valueUserID)
        {
            //cout << "one element in movielist and it is already here" << endl;
            cout << "User " << valueUserID << " already exists" << endl;
            return;
        }
        if (start->userID == valueUserID)  /*First Element Search*/
        {
            cout << "User " << valueUserID << " already exists" << endl;
            return;
        }
        while (start->next != userLast)
        {
            if (start->next->userID == valueUserID)
            {
                cout << "User " << valueUserID << " already exists" << endl;
                return;
            }
            start = start->next;
        }
        /*Search of last element*/
        if (start->next->userID == valueUserID)
        {
            cout << "User " << valueUserID << " already exists" << endl;
            return;
        }

    }


    if (userLast == nullptr){
        struct UserNode *temp = new UserNode;

        // Assign the data.
        temp->userID = valueUserID;
        temp->userName = valueUserName;
        temp->movie = nullptr;
        userLast = temp;

        // Create the link.
        userLast->next = userLast;
        userLast->prev = userLast;
        cout << "User " << valueUserID << " has been added" << endl;
    }
    else if (userLast->next==userLast){

        //else create a new node
        struct UserNode *temp = new UserNode;

        //assign data to new node
        temp->userID = valueUserID;
        temp->userName = valueUserName;
        temp->movie = nullptr;

        userLast->next = temp;
        temp->next = userLast;
        temp->prev = userLast;
        userLast->prev = temp;
        userLast = temp;
        cout << "User " << valueUserID << " has been added" << endl;
    }
    else{
        //else create a new node
        struct UserNode *temp = new UserNode;

        //assign data to new node
        temp->userID = valueUserID;
        temp->userName = valueUserName;
        temp->movie = nullptr;

        temp->next = userLast->next;
        temp->prev = userLast;
        userLast->next = temp;
        userLast = temp;
        cout << "User " << valueUserID << " has been added" << endl;
    }
}

// deleteUser function in order to delete user from user list. It also checks
// whether the user with the given ID does not belong to user list or does.
void LibrarySystem::deleteUser(const int valueUserID) {
    struct UserNode *temp, *start;

    if (userLast != nullptr){
        start = userLast->next;

        /* If List has only one element*/
        if (start == userLast && userLast->userID == valueUserID)
        {
            temp = userLast;
            userLast = nullptr;
            free(temp);
            cout << "User " << valueUserID << " has been deleted" << endl;
            return;
        }
        if (start->userID == valueUserID)  /*First Element Deletion*/
        {
            temp = start;
            userLast->next = start->next;
            start->next->prev = userLast;
            free(temp);
            cout << "User " << valueUserID << " has been deleted" << endl;
            return;
        }
        while (start->next != userLast)
        {
            /*Deletion of Element in between*/
            if (start->next->userID == valueUserID)
            {
                temp = start->next;
                start->next = temp->next;
                temp->next->prev = start;
                free(temp);
                cout << "User " << valueUserID << " has been deleted" << endl;
                return;
            }
            start = start->next;
        }
        /*Deletion of last element*/
        if (start->prev->userID == valueUserID)
        {
            temp = start->prev;
            temp->prev->next =start;
            start->prev = temp->prev;
            free(temp);
            userLast = start->prev;
            cout << "User " << valueUserID << " has been deleted" << endl;
            return;
        }
    }
    if (userLast== nullptr){
        cout << "No user in list to delete" << endl;
        return;
    }

    cout << "User " << valueUserID << " does not exist" << endl;
}

// checkoutMovie function for purchase operations. It also checks
// if the given movie does exist or available or not.
void LibrarySystem::checkoutMovie(const int valueMovieID, const int valueUserID) {

    struct MovieNode *start,*temp;

    if(movieLast != nullptr){
        start = movieLast->next;

        /* If List has only one element*/

        if (movieLast->next == movieLast && movieLast->movieID == valueMovieID)
        {
            temp = movieLast;
            struct UserNode *startUser;

            if (userLast != nullptr){
                startUser = userLast->next;
                /* If List has only one element*/
                if (userLast->next == userLast && userLast->userID == valueUserID)
                {
                    if (userLast->movie == nullptr){
                        userLast->movie = temp;
                        userLast->movie->next = userLast->movie;
                    }
                    else{
                        temp->next = userLast->movie->next;
                        userLast->movie->next = temp;
                        userLast->movie = temp;
                    }
                    movieLast = nullptr;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
                if (startUser->userID == valueUserID)  /*First Element Search*/
                {
                    if (startUser->movie == nullptr){
                        startUser->movie = temp;
                        startUser->movie->next = startUser->movie;
                    }
                    else{
                        temp->next = startUser->movie->next;
                        startUser->movie->next = temp;
                        startUser->movie = temp;
                    }
                    movieLast = nullptr;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;

                }
                while (startUser->next != userLast)
                {
                    if (startUser->next->userID == valueUserID)
                    {
                        struct UserNode *userTemp;
                        userTemp = startUser->next;

                        if (userTemp->movie == nullptr){
                            userTemp->movie = temp;
                            userTemp->movie->next = userTemp->movie;
                        }
                        else{

                            temp->next = userTemp->movie->next;
                            userTemp->movie->next = temp;
                            userTemp->movie = temp;
                        }
                        movieLast = nullptr;
                        cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                        return;
                    }
                    startUser = startUser->next;
                }
                /*Search of last element*/
                if (startUser->next->userID == valueUserID)
                {
                    if (startUser->next->movie == nullptr){
                        startUser->next->movie = temp;
                        startUser->next->movie->next = startUser->next->movie;
                    }
                    else{
                        temp->next = startUser->next->movie->next;
                        startUser->next->movie->next = temp;
                        startUser->next->movie = temp;
                    }
                    movieLast = nullptr;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
            }
            //cout << "one element in movielist and it is already here" << endl;
            cout << "User " << valueUserID << " does not exist for checkout" << endl;
            return;
        }
        if (start->movieID == valueMovieID)  /*First Element Search*/
        {
            struct MovieNode *temp2;
            temp2 = start->next;
            temp = start;
            struct UserNode *startUser;

            if (userLast != nullptr){
                startUser = userLast->next;
                /* If List has only one element*/
                if (userLast->next == userLast && userLast->userID == valueUserID)
                {
                    if (userLast->movie == nullptr){
                        userLast->movie = temp;
                        userLast->movie->next = userLast->movie;
                    }
                    else{

                        temp->next = userLast->movie->next;
                        userLast->movie->next = temp;
                        userLast->movie = temp;
                    }
                    movieLast->next = temp2;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
                if (startUser->userID == valueUserID)  /*First Element Search*/
                {
                    if (startUser->movie == nullptr){
                        startUser->movie = temp;
                        startUser->movie->next = startUser->movie;
                    }
                    else{
                        temp->next = startUser->movie->next;
                        startUser->movie->next = temp;
                        startUser->movie = temp;
                    }
                    movieLast->next = temp2;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
                while (startUser->next != userLast)
                {
                    if (startUser->next->userID == valueUserID)
                    {
                        if (startUser->next->movie == nullptr){
                            startUser->next->movie = temp;
                            startUser->next->movie->next = startUser->next->movie;
                        }
                        else{
                            temp->next = startUser->next->movie->next;
                            startUser->next->movie->next = temp;
                            startUser->next->movie = temp;
                        }
                        movieLast->next = temp2;
                        cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                        return;
                    }
                    startUser = startUser->next;
                }
                /*Search of last element*/
                if (startUser->next->userID == valueUserID)
                {
                    if (startUser->next->movie == nullptr){
                        startUser->next->movie = temp;
                        startUser->next->movie->next = startUser->next->movie;
                    }
                    else{
                        temp->next = startUser->next->movie->next;
                        startUser->next->movie->next = temp;
                        startUser->next->movie = temp;
                    }
                    movieLast->next = temp2;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
            }

            //cout << "one element in movielist and it is already here" << endl;
            cout << "User " << valueUserID << " does not exist for checkout" << endl;
            return;
        }

        while (start->next != movieLast)
        {
            if (start->next->movieID == valueMovieID)
            {
                struct MovieNode *temp2;
                temp2 = start->next->next;
                temp = start->next;
                struct UserNode *startUser;
                if(userLast != nullptr){
                    startUser = userLast->next;
                    /* If List has only one element*/
                    if (userLast->next == userLast && userLast->userID == valueUserID)
                    {
                        if (userLast->movie == nullptr){
                            userLast->movie = temp;
                            userLast->movie->next = userLast->movie;
                        }
                        else{
                            temp->next = userLast->movie->next;
                            userLast->movie->next = temp;
                            userLast->movie = temp;
                        }
                        start->next = temp2;

                        cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                        return;
                    }
                    if (startUser->userID == valueUserID)  /*First Element Search*/
                    {
                        if (startUser->movie == nullptr){
                            startUser->movie = temp;
                            startUser->movie->next = startUser->movie;
                        }
                        else{
                            temp->next = startUser->movie->next;
                            startUser->movie->next = temp;
                            startUser->movie = temp;
                        }
                        start->next = temp2;
                        cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                        return;
                    }
                    while (startUser->next != userLast)
                    {
                        if (startUser->next->userID == valueUserID)
                        {
                            if (startUser->next->movie == nullptr){
                                startUser->next->movie = temp;
                                startUser->next->movie->next = startUser->next->movie;
                            }
                            else{
                                temp->next = startUser->next->movie->next;
                                startUser->next->movie->next = temp;
                                startUser->next->movie = temp;
                            }
                            start->next = temp2;
                            cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                            return;
                        }
                        startUser = startUser->next;
                    }
                    /*Search of last element*/
                    if (startUser->next->userID == valueUserID)
                    {
                        if (startUser->next->movie == nullptr){
                            startUser->next->movie = temp;
                            startUser->next->movie->next = startUser->next->movie;
                        }
                        else{
                            temp->next = startUser->next->movie->next;
                            startUser->next->movie->next = temp;
                            startUser->next->movie = temp;
                        }
                        start->next = temp2;
                        cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                        return;
                    }
                }
                cout << "User " << valueUserID << " does not exist for checkout" << endl;
                return;
            }
            start = start->next;
        }
        /*Search of last element*/
        if (start->next->movieID == valueMovieID)
        {
            struct MovieNode *temp2;
            temp2 = start->next->next;
            temp = start->next;
            struct UserNode *startUser;
            if (userLast != nullptr){
                startUser = userLast->next;
                /* If List has only one element*/
                if (startUser == userLast && userLast->userID == valueUserID)
                {
                    if (startUser->movie == nullptr){
                        startUser->movie = temp;
                        startUser->movie->next = startUser->movie;
                    }
                    else{
                        temp->next = startUser->movie->next;
                        startUser->movie->next = temp;
                        startUser->movie = temp;
                    }
                    start->next= temp2;
                    movieLast = start;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
                if (startUser->userID == valueUserID)  /*First Element Search*/
                {
                    if (startUser->movie == nullptr){
                        startUser->movie = temp;
                        startUser->movie->next = startUser->movie;
                    }
                    else{
                        temp->next = startUser->movie->next;
                        startUser->movie->next = temp;
                        startUser->movie = temp;
                    }
                    start->next= temp2;
                    movieLast = start;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
                while (startUser->next != userLast)
                {
                    if (startUser->next->userID == valueUserID)
                    {
                        if (startUser->next->movie == nullptr){
                            startUser->next->movie = temp;
                            startUser->next->movie->next = startUser->next->movie;
                        }
                        else{
                            temp->next = startUser->next->movie->next;
                            startUser->next->movie->next = temp;
                            startUser->next->movie = temp;
                        }
                        start->next= temp2;
                        movieLast = start;
                        cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                        return;
                    }
                    startUser = startUser->next;
                }
                /*Search of last element*/
                if (startUser->next->userID == valueUserID)
                {
                    if (startUser->next->movie == nullptr){
                        startUser->next->movie = temp;
                        startUser->next->movie->next = startUser->next->movie;
                    }
                    else{
                        temp->next = startUser->next->movie->next;
                        startUser->next->movie->next = temp;
                        startUser->next->movie = temp;
                    }
                    start->next= temp2;
                    movieLast = start;
                    cout << "Movie " << valueMovieID << " has been checked out by User " << valueUserID << endl;
                    return;
                }
            }
            cout << "User " << valueUserID << " does not exist for checkout" << endl;
            return;
        }
    }
    cout << "Movie " << valueMovieID << " does not exist for checkout" << endl;
}

// returnMovie function for returning operations. It also checks
// if the given movie has already been purchased or not.
void LibrarySystem::returnMovie(const int valueMovieID) {
    struct MovieNode *startMovie,*temp;
    struct UserNode *startUser;
    if(userLast != nullptr){
        startUser = userLast->next;

        if (userLast->next == userLast && userLast->prev == userLast)   // USER TEK İSE
        {
            if (userLast->movie != nullptr){
                startMovie = userLast->movie->next;

                if (userLast->movie->movieID == valueMovieID && userLast->movie->next == userLast->movie){  // userın tek filmi varsa ve aranansa
                    temp = userLast->movie;

                    if (movieLast == nullptr){
                        movieLast = temp;
                        movieLast->next = movieLast;
                    }
                    else{
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    userLast->movie = nullptr;
                    return;
                }
                if (startMovie->movieID == valueMovieID)  /*First Element Search*/
                {
                    struct MovieNode *temp2;
                    temp2 = startMovie->next;
                    temp = startMovie;
                    if (movieLast == nullptr){
                        movieLast = temp;
                        movieLast->next = movieLast;
                    }
                    else{
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    userLast->movie->next = temp2;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
                while (startMovie->next != userLast->movie)
                {
                    if (startMovie->next->movieID == valueMovieID)
                    {
                        struct MovieNode *temp2;
                        temp2 = startMovie->next->next;
                        temp = startMovie->next;
                        if (movieLast == nullptr){
                            movieLast = temp;
                            movieLast->next = movieLast;
                        }
                        else{
                            temp->next = movieLast->next;
                            movieLast->next = temp;
                            movieLast = temp;
                        }
                        startMovie->next = temp2;
                        cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                        return;
                    }
                    startMovie = startMovie->next;
                }
                if (startMovie->next->movieID == valueMovieID)
                {
                    struct MovieNode *temp2;
                    temp2 = startMovie->next->next;
                    temp = startMovie->next;
                    if (movieLast == nullptr){
                        movieLast = temp;
                        movieLast->next = movieLast;
                    }
                    else{
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    startMovie->next = temp2;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
            }
            // else kullanıcının moviesi yok returnleyecek
        }
        while (startUser != userLast)
        {
            if (startUser->movie != nullptr) {
                startMovie = startUser->movie->next;

                if (startUser->movie->movieID == valueMovieID && startUser->movie->next == startUser->movie) {  // userın tek filmi varsa ve aranansa
                    temp = startUser->movie;

                    if (movieLast == nullptr) {
                        movieLast = temp;
                        movieLast->next = movieLast;
                    } else {
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    startUser->movie = nullptr;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
                if (startMovie->movieID == valueMovieID)  /*First Element Search*/
                {
                    struct MovieNode *temp2;
                    temp2 = startMovie->next;
                    temp = startMovie;
                    if (movieLast == nullptr) {
                        movieLast = temp;
                        movieLast->next = movieLast;
                    } else {
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    startUser->movie->next = temp2;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
                while (startMovie->next != startUser->movie) {
                    if (startMovie->next->movieID == valueMovieID) {
                        struct MovieNode *temp2;
                        temp2 = startMovie->next->next;
                        temp = startMovie->next;
                        if (movieLast == nullptr) {
                            movieLast = temp;
                            movieLast->next = movieLast;
                        } else {
                            temp->next = movieLast->next;
                            movieLast->next = temp;
                            movieLast = temp;
                        }
                        startMovie->next = temp2;
                        cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                        return;
                    }
                    startMovie = startMovie->next;
                }
                if (startMovie->next->movieID == valueMovieID) {
                    struct MovieNode *temp2;
                    temp2 = startMovie->next->next;
                    temp = startMovie->next;
                    if (movieLast == nullptr) {
                        movieLast = temp;
                        movieLast->next = movieLast;
                    } else {
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    startMovie->next = temp2;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
            }

            startUser = startUser->next;
        }
        if (startUser == userLast){

            if (startUser->movie != nullptr) {
                startMovie = startUser->movie->next;

                if (startUser->movie->movieID == valueMovieID && startUser->movie->next == startUser->movie) {  // userın tek filmi varsa ve aranansa
                    temp = startUser->movie;

                    if (movieLast == nullptr) {
                        movieLast = temp;
                        movieLast->next = movieLast;
                    } else {
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    startUser->movie = nullptr;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
                if (startMovie->movieID == valueMovieID)  /*First Element Search*/
                {
                    struct MovieNode *temp2;
                    temp2 = startMovie->next;
                    temp = startMovie;
                    if (movieLast == nullptr) {
                        movieLast = temp;
                        movieLast->next = movieLast;
                    } else {
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    startUser->movie->next = temp2;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
                struct MovieNode *prevOne;
                while (startMovie != startUser->movie) {
                    if (startMovie->movieID == valueMovieID) {
                        struct MovieNode *temp2;
                        temp2 = startMovie->next;
                        temp = startMovie;
                        if (movieLast == nullptr) {
                            movieLast = temp;
                            movieLast->next = movieLast;
                        } else {
                            temp->next = movieLast->next;
                            movieLast->next = temp;
                            movieLast = temp;
                        }
                        prevOne->next = temp2;
                        cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                        return;
                    }
                    prevOne = startMovie;
                    startMovie = startMovie->next;

                }
                if (startMovie->movieID == valueMovieID) {
                    struct MovieNode *temp2;
                    temp2 = startMovie->next;
                    temp = startMovie;
                    if (movieLast == nullptr) {
                        movieLast = temp;
                        movieLast->next = movieLast;
                    } else {
                        temp->next = movieLast->next;
                        movieLast->next = temp;
                        movieLast = temp;
                    }
                    prevOne->next = temp2;
                    cout << "Movie " << valueMovieID << " has been returned" <<  endl;
                    return;
                }
            }
        }
    }
    else{
        cout << "User does not exist for any checkout operation." << endl;
    }

    if (movieLast != nullptr){
        struct MovieNode* temp3;
        temp3 = movieLast->next;
        while (temp3 != movieLast){
            if (temp3->movieID == valueMovieID){
                cout << "Movie " << valueMovieID << " has not been checked out"<< endl;
                return;
            }
            temp3 = temp3->next;
        }
        if (temp3 == movieLast){
            if (temp3->movieID == valueMovieID){
                cout << "Movie " << valueMovieID << " has not been checked out"<< endl;
                return;
            }
        }
        cout << "Movie " << valueMovieID << " not exist in the library" << endl;
    }
}

// showAllMovies function to show all movies with their details in the program.
void LibrarySystem::showAllMovies() {
    struct MovieNode *s,*startMovie;
    cout << "Movie id - Movie name - Year - Status" << endl;
//    if (movieLast == nullptr)
//    {
//        cout<<"Unchecked Movie List is empty, nothing to display"<<endl;
//    }
    if(movieLast != nullptr){
        s = movieLast->next;
        while (s != movieLast)
        {
            cout<< s->movieID << " " << s->movieTitle << " " << s->movieYear << " Not checked out" <<endl;
            s = s->next;
        }
        cout<< s->movieID << " " << s->movieTitle << " " << s->movieYear << " Not checked out" <<endl;
    }

    if (userLast != nullptr){
        struct UserNode *startUser;
        startUser = userLast->next;

        while (startUser != userLast){
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;

                while (startMovie != startUser->movie){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked out by User " << startUser->userID << " " <<  endl;
                    startMovie = startMovie->next;
                }
                if (startMovie == startUser->movie){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked out by User " << startUser->userID << " " <<  endl;
                }
            }
            startUser = startUser->next;
        }
        if (startUser == userLast){
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;

                while (startMovie != startUser->movie){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked out by User " << startUser->userID << " " <<  endl;
                    startMovie = startMovie->next;
                }
                if (startMovie == startUser->movie){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked out by User " << startUser->userID << " " <<  endl;
                }
            }
        }
    }
}

// showMovie function to show specific movie with its details in the program.
// It also checks for validity and existence of the movie.
void LibrarySystem::showMovie(const int valueMovieID) {

    struct MovieNode *s,*startMovie;
    if (movieLast == nullptr)
    {
        cout<<"Unchecked Movie List is empty, nothing to display"<<endl;
    }
    else if(movieLast != nullptr){
        s = movieLast->next;
        while (s != movieLast)
        {
            if (s->movieID == valueMovieID){
                cout<< s->movieID << " " << s->movieTitle << " " << s->movieYear << " Not checked out" <<endl;
                return;
            }
            s = s->next;
        }
        if (s->movieID == valueMovieID){
            cout<< s->movieID << " " << s->movieTitle << " " << s->movieYear << " Not checked out" <<endl;
            return;
        }
    }

    if (userLast != nullptr){
        struct UserNode *startUser;
        startUser = userLast->next;

        while (startUser != userLast){
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;

                while (startMovie != startUser->movie){
                    if (startMovie->movieID == valueMovieID){
                        cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked by User " << startUser->userID << " " << startUser->userName << endl;
                        return;
                    }
                    startMovie = startMovie->next;
                }
                if (startMovie == startUser->movie && startMovie->movieID == valueMovieID){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked by User " << startUser->userID << " " << startUser->userName << endl;
                    return;
                }
            }
            startUser = startUser->next;
        }
        if (startUser == userLast){
            if (startUser->movie != nullptr){
                startMovie = startUser->movie->next;

                while (startMovie != startUser->movie) {
                    if (startMovie->movieID == valueMovieID) {
                        cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear
                             << " checked by User " << startUser->userID << " " << startUser->userName << endl;
                        return;
                    }
                }
                if (startMovie == startUser->movie && startMovie->movieID == valueMovieID){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear << " checked by User " << startUser->userID << " " << startUser->userName << endl;
                    return;
                }
            }
        }
    }
    cout << "Movie with the id " << valueMovieID << " does not exist" << endl;
}

// showUser function to show specific user with its movies in the program.
// It also checks for validity and existence of the user.
void LibrarySystem::showUser(const int valueUserID) {
    struct UserNode *startUser;
    startUser = userLast->next;
    while (startUser != userLast){
        if (startUser->userID == valueUserID){
            cout << "User id: " << valueUserID << " User name : " << startUser->userName << endl;
            cout << "User "<< valueUserID << " checked out the following Movies:" << endl;
            if (startUser->movie != nullptr){
                struct MovieNode *startMovie;
                startMovie = startUser->movie->next;
                cout << "Movie id - Movie name - Year"<< endl;
                while (startMovie != startUser->movie){
                    cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear <<endl;
                    startMovie = startMovie->next;
                }
                cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear <<endl;
            }
        }
            startUser = startUser->next;
    }
    if (startUser->userID == valueUserID){
        cout << "User id: " << valueUserID << " User name : " << startUser->userName << endl;
        cout << "User "<< valueUserID << " checked out the following Movies:" << endl;
        if (startUser->movie != nullptr){
            struct MovieNode *startMovie;
            startMovie = startUser->movie->next;
            cout << "Movie id - Movie name - Year"<< endl;
            while (startMovie != startUser->movie){
                cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear <<endl;
                startMovie = startMovie->next;
            }
            cout << startMovie->movieID << " " << startMovie->movieTitle << " " << startMovie->movieYear <<endl;
        }
    }
}

// Destructor method of library system.
LibrarySystem::~LibrarySystem() {}