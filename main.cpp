// Movie struct                         		Feb 2022
//
// Sample based on example on structures (structs) from cplusplus.com
//
// Demonstrates:
// Structs are used as Plain Old Data Types (PODs) (with no constructors, destructors or methods)
// Defining and declaring a struct (object)
// Accessing the members of a struct (which are public)
// Passing a struct object by value and by reference
// Arrays of Struct
// Allocating a struct in Dynamic Memory
//

// Structs are normally used when we want to store a data structure or record of data -
// such as a record of data read from a file.

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct movie_t {			// "_t" indicates that this is a type
    string title;
    int year;
};
//myFavouriteMovie;			// declares a struct called 'myFavouriteMovie', accessible throughout this .cpp file

// function prototypes
void print_movie(const movie_t& movie);
void pass_by_value_demo(movie_t movie);
movie_t return_a_struct_demo();

int main()
{
    cout << "Structs demo" << endl;

    string mystr;

    movie_t myFavouriteMovie; // declares a struct (object) in stack memory

    // we use the member access operator dot "." to access the members (fields)

    myFavouriteMovie.title = "2001 A Space Odyssey";
    myFavouriteMovie.year = 1968;
    cout << "My favorite movie is:\n ";
    print_movie(myFavouriteMovie);

    movie_t yourFavouriteMovie;				// declare a struct (object)  called 'yourFavouriteMovie' of type movie_t
    cout << "What is your favourite movie?" << endl;
    cout << "Enter title: ";
    getline(cin, yourFavouriteMovie.title);	// read dirctly into the struct

    cout << "Enter year: ";
    getline(cin, mystr);
    stringstream(mystr) >> yourFavouriteMovie.year;

    cout << "And yourFavouriteMovie is:\n ";
    print_movie(yourFavouriteMovie);

    cout << "Demonstrating pass-by-value" << endl;
    cout << "My favorite movie is:\n ";
    print_movie(myFavouriteMovie);
    cout << "... calling pass_by_value_demo() to attempt to modify movie struct details" << endl;
    pass_by_value_demo(myFavouriteMovie);
    cout << "My favorite movie is:\n ";
    print_movie(myFavouriteMovie);
    cout << "... you should see that the movie details have NOT been modified - explain!" << endl;

    // Return a struct demo
    movie_t myReturnedMovieStruct = return_a_struct_demo();  // declares a struct variable to hold the returned struct data
    cout << "Demo: struct returned by a function:" << endl;
    print_movie(myReturnedMovieStruct);

    // Array of structs
    movie_t myTop3Movies[3];	// define an array of structs on the stack
    myTop3Movies[0].title = "Jaws";
    myTop3Movies[0].year = 1978;
    myTop3Movies[1].title = "Alien";
    myTop3Movies[1].year = 1987;
    myTop3Movies[2].title = "Rug Rats";
    myTop3Movies[2].year = 1995;

    cout << "Demo: Array of struct" << endl;
    for (int i = 0; i < 3; i++)
        cout << i << ": " << myTop3Movies[i].title << ", " << myTop3Movies[i].year << endl;

    // DMA (Dynamic Memory Allocation)
    // Dynamically allocate a block of memory to store a single struct
    // and access it using a pointer

    movie_t* pMovie = new movie_t; // allocate a block of memory big enough to store one struct
    //(*pMovie).title = "Baby Driver";  // dereference the struct and assess its title field

    cout << "Dynamically allocate struct" << endl;
    pMovie->title = "Baby Driver";	// ARROW member access operator is easier to read
    pMovie->year = 2016;

    // cout << *pMovie;  - won't work as 'cout' doesn't know what a movie_t struct is
    // and thus, does not know how to interpret its contents for printing

    // can access each member using "->"
    cout << pMovie->title << endl;
    cout << pMovie->year << endl;

    // finished with it, so delete the memory
    delete pMovie;
    pMovie = nullptr;

    // Dynamically allocate an array of Structs

    cout << "Dynamically allocate Array of struct" << endl;

    int size;
    //cout << "Enter size of array:";
    //cin >> size;
    size = 3;
    movie_t* movies = new movie_t[size];	// allocate block of memory big enough to store 'size' movie structs

    // could ask user to enter movies, but I will hard code here...
    movies[0].title = "Judge Dredd";
    movies[0].year = 2012;

    movies[1].title = "Midnight Express";
    movies[1].year = 1987;

    movies[2].title = "Independence Day";
    movies[2].year = 2004;

    // print out second movie
    cout << movies[1].title << endl;
    cout << movies[1].year << endl;

    //TODO
    // Write a function that will accept the movies array and output all movies.
    // Remember to declare function prototype.


    // when finished - we must remember to free dynamic memory
    delete [] movies;	// 'delete' dynamically allocate array of memory from the Heap

    return 0;
}

/** Demo: pass-by-reference - 'movie' is a reference to a constant movie_t struct.
*  This is efficient, because we pass only a reference to the original struct.
*  We make the reference 'const' to prevent this function from changing the
*  contents of the original structure.
*  If we omit the keyword 'const' then the reference in this function will be able
   to directly modify the contents of the original struct passed (by reference) from main.
*/

void print_movie(const movie_t& movie)      // reference to a movie struct
{
    cout << movie.title;			// note public access to member data
    cout << " (" << movie.year << ")" << endl;
}

/** Demo: pass-by-value => a local struct called 'movie' of type 'movie_t' is created on the stack
	as an automatic variable.  It is populated using the values passed as arguments.
   Any changes made to the 'movie' struct are local to the function,
   and these changes have no effect on the original struct (passed from main).
   The 'movie' struct is discarded (from the stack) when the function exits.
   Note that this can be an expensive operation, as all the field values of the
   struct being passed must be copied into the struct fields of the parameter.

*/
void pass_by_value_demo(movie_t movie)
{
    cout << "... in pass_by_value_demo() " << "Title:" << movie.title << "Year: " << movie.year << endl;
    movie.title = "Flash Gordon";		// this will update ONLY the local copy of the movie structure
    movie.year = 1980;
}

/** Demo: Return a struct from a function.
A struct created in a function can be returned. What is actually returned, is a COPY of the
data in the local struct.  The data returned must be assigned to a struct variable by the calling function.

Note that the local movie struct will be discarded when the function returns. Therefore, it is
an error to return a reference to a local struct. (as it would no longer exist after the return)
*/
movie_t return_a_struct_demo()
{
    movie_t movie;	// creates a local struct object

    movie.title = "Joker";
    movie.year = 2019;

    return movie;	// returns a copy of the struct data
}


