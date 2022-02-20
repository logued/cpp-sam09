// Movie struct                         		Feb 2022
//
// Sample based on example on structures (structs) from cplusplus.com
// Structs are often used as Plain Old Data Types (PODs) (with no constructors, destructors or methods)

// Demonstrates:
// Defining and declaring a struct (object)
// Accessing the members of a struct (which are all public)
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

struct movie_type {			// indicates that this is a type
    string title;
    int year;
};
//myFavouriteMovie;			// declares a struct called 'myFavouriteMovie', accessible throughout this .cpp file

// function prototypes
void print_movie_pass_by_reference(const movie_type& movie);
void print_movie_pass_by_value(movie_type movie);
movie_type return_a_struct_copy();

int main()
{
    cout << "Structs demo" << endl;

    movie_type myFavouriteMovie; // declares a struct (object) in stack memory

    // we use the member access operator dot "." to access individual members (fields)

    myFavouriteMovie.title = "2001 A Space Odyssey";    // possible because struct members are public
    myFavouriteMovie.year = 1968;
    
    cout << "My favorite movie is:\n ";
    print_movie_pass_by_reference(myFavouriteMovie);

    movie_type yourFavouriteMovie;				// declare a struct (object)  called 'yourFavouriteMovie' of type movie_type
    cout << "What is your favourite movie?" << endl;
    cout << "Enter title: ";
    getline(cin, yourFavouriteMovie.title);	// read directly into the struct

    string input;   // creates a string object (variable)
    cout << "Enter year: ";
    getline(cin, input);
    stringstream(input) >> yourFavouriteMovie.year;

    cout << "And yourFavouriteMovie is:\n ";
    print_movie_pass_by_reference(yourFavouriteMovie);

    cout << "Demonstrating pass-by-value" << endl;
    cout << "My favorite movie is:\n ";
    cout << "... print_movie_pass_by_value() to attempt to modify movie struct details" << endl;
    cout << "... passing a struct by-value is expensive, because a COPY of all member data is passed." << endl;
    cout << "... (Note: Java can never do this because Java always passes references to objects.))" << endl;

    print_movie_pass_by_value(myFavouriteMovie);

    cout << "My favorite movie is:\n ";
    print_movie_pass_by_value(myFavouriteMovie);
    cout << "... you should see that the movie details have NOT been modified - explain!" << endl;

    cout << "Demo: return (by-value) a struct object that was defined in a function:" << endl;

    // Return a struct demo
    movie_type myReturnedMovieStruct;   // a struct to store a returned struct object
    myReturnedMovieStruct = return_a_struct_copy();

    // declares a struct variable to hold the returned struct data
    // the return_a_struct_copy() function creates and populates a struct with data,
    // and then returns the struct. A COPY of the struct data is assigned into the
    // myReturnedMovieStruct variable, field by field (each member is copied)

    print_movie_pass_by_reference(myReturnedMovieStruct);   // verify that the data was copied


    ////////////////////////////// Array of struct ////////////////////////////////////////////////

    movie_type myTop3Movies[3];	// defines an array of structs on the STACK
    myTop3Movies[0].title = "Jaws";
    myTop3Movies[0].year = 1978;
    myTop3Movies[1].title = "Alien";
    myTop3Movies[1].year = 1987;
    myTop3Movies[2].title = "Rug Rats";
    myTop3Movies[2].year = 1995;

    cout << "Demo: Array of struct" << endl;
    for (int i = 0; i < 3; i++)
        cout << i << ": " << myTop3Movies[i].title << ", " << myTop3Movies[i].year << endl;

    ////////////////////////////////   DMA (Dynamic Memory Allocation) //////////////////////////////

    // Dynamically allocate a block of memory to store a single struct
    // and access it using a pointer.  Remember that 'new' always returns an address
    // of the memory allocated, so we must use a pointer to store the returned address.

    movie_type* movie_ptr = new movie_type; // allocate a block of memory big enough to store one movie_type struct
                                            // the movie struct object is stored in the HEAP.

    // Assign some data to the struct members (fields)
    (*movie_ptr).title = "Casablanca";  // dereference the struct and access its title field.  Brackets are needed.

    // the above is a cumbersome syntax, so the arrow access operator "->" is preferred

    movie_ptr->title = "Baby Driver";	// ARROW member access operator is easier to read
    movie_ptr->year = 2016;

    // cout << *movie_ptr;  - won't work as 'cout' doesn't know what a movie_type struct is
    // and thus, does not know how to interpret its contents for printing
    // Therefore, we must output by accessing each member individually.
    cout << "\nDynamically allocated struct" << endl;

    cout << movie_ptr->title << endl;
    cout << movie_ptr->year << endl;

    // finished with it, so delete the memory
    // Remember, if we allocate memory using "new" then we MUST always free that memory using "delete"
    delete movie_ptr;
    movie_ptr = nullptr;

    //////////////////////// Dynamically allocate an Array of Struct ////////////////////////

    cout << "\nDynamically allocate Array of struct" << endl;

    int size;

    // We could input the size of the array required.
    //cout << "Enter size of array:";
    //cin >> size;

    size = 3;

    movie_type* movies = new movie_type[size];

    // Above - allocate block of memory big enough to store 'size' number of movie_type structs
    // That is - an array of movie_type structs.
    // "movies" is a pointer to the first movie_type struct element in the array.
    // If using array notation, it is clearer to simply name the pointer 'movies', and use array notation
    // to treat it as a 'movies' array.  The code then looks more intuitive.
    // If we wished to use pointer notation, we could call the pointer movies_ptr in order
    // to improve readability.  However, both are equivalent.

    // could ask user to enter movie details, or get details from a database,
    // but here we will hard code values for convenience.
    movies[0].title = "Judge Dredd";    // first array element, title member
    movies[0].year = 2012;

    movies[1].title = "Midnight Express";
    movies[1].year = 1987;

    movies[2].title = "Independence Day";
    movies[2].year = 2004;

    // print out second element in the movies array
    cout << "movies[1]:" << endl;
    cout << "movies[1].title = " << movies[1].title << endl;
    cout << "movies[1].year  = " << movies[1].year << endl;

    cout << "\nAll elements in the dynamically allocates movies[] array:" << endl;
    for(int i=0; i<size; i++) {
        cout << "movies[" << i << "] ";
        cout << "title=" << movies[i].title << ", ";
        cout << "year =" << movies[i].year << "." << endl;
    }
    
    // when finished - we must remember to free dynamic memory
    delete [] movies;	// 'delete' dynamically allocate array of memory from the Heap

    return 0;
}

//TODO
// Write a function that will accept an array of movie_type objects
// as an argument and output details of all movies.
// Remember to declare a function prototype.


/** Demo: pass-by-reference - 'movie' is a reference to a constant movie_type struct.
*  This is efficient, because we pass only a reference to the original struct.
*  We make the reference 'const' to prevent this function from changing the
*  contents of the original structure.
*  If we omit the keyword 'const' then the reference in this function will be able
   to directly modify the contents of the original struct passed (by reference) from main.
*/

void print_movie_pass_by_reference(const movie_type& movie)      // reference to a movie struct
{
    cout << movie.title;			// note public access to member data
    cout << " (" << movie.year << ")" << endl;
}

/** Demo: pass-by-value => a local struct called 'movie' of type 'movie_type' is created on the stack
	as an automatic variable.  It is populated using the values passed as arguments.
   Any changes made to the 'movie' struct are local to the function,
   and these changes have no effect on the original struct (passed from main).
   The 'movie' struct is discarded (from the stack) when the function exits.
   Note that this can be an expensive operation, as all the field values of the
   struct being passed must be copied into the struct fields of the parameter.

*/
void print_movie_pass_by_value(movie_type movie)
{
    cout << "... in print_movie_pass_by_value() " << "Title:" << movie.title << "Year: " << movie.year << endl;
    movie.title = "Flash Gordon";		// this will update ONLY the local copy of the movie structure
    movie.year = 1980;
}

/** Demo: Return a struct from a function.
A struct created in a function can be returned. What is actually returned, is a COPY of the
data in the local struct.  The data returned must be assigned to a struct variable by the calling function.

Note that the local movie struct will be discarded when the function returns. Therefore, it is
an error to return a reference to a local struct. (as it would no longer exist after the return)
*/
movie_type return_a_struct_copy()
{
    movie_type movie;	// creates a local struct object (on stack)

    movie.title = "Joker";
    movie.year = 2019;

    return movie;	// returns a copy of the struct data
}


