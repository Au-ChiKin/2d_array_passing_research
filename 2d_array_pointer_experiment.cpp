#include <iostream>

using namespace std;

void to_two_d_array(char arr [10][10]) {
    cout << "to_two_d_array works" << endl;
}

void to_ptr_to_arr(char (* arr) [10]) {
    cout << "to_ptr_to_arr works" << endl;
}

void to_arr_of_ptr(char * arr [10]) {
    cout << "to_arr_of_ptr works" << endl;
}

void to_ptr_to_ptr(char ** arr) {
    cout << "to_ptr_to_ptr works" << endl;
}

void to_ptr_to_ptr_to_const(char const ** arr) {
    cout << "to_ptr_to_ptr_to_const works" << endl; 
}

void to_ptr_to_const_ptr(char * const * arr) {
    cout << "to_ptr_to_const_ptr works" << endl; 
}

void to_const_ptr_to_ptr(char ** const arr) {
    cout << "to_const_ptr_to_ptr works" << endl; 
}

void to_ptr_to_const_ptr_to_const(char const * const * arr) {
    cout << "to_ptr_to_const_ptr_to_const works" << endl;
}

void strange_conversion() {
    const char * chain[100]; // an array of pointers to const char
    char line[] = "Hello"; // a string or a array of char (not const)

    *chain = line; // *chain is chain[0], a pointer to const char
                   // line is &line[0], a pointer to char (not const)
                   // 
                   // *chain is still a pinter to const char which means you cannot
                   // change *chain[0]. 
                   // 
                   // Effectively a conversion from "char *" to "const char *"
    cout << "Size of *chain is " << sizeof(*chain) << " bytes" << endl;  
    cout << "Size of line is " << sizeof(line) << " bytes" << endl;
    cout << "Size of line[0] is " << sizeof(&line[0]) << " bytes" << endl;
    cout << "Content of *chain is now " << (void *) *chain << endl;
    cout << "Content of line is now " << (void *) line << endl;
    
    cout << *chain << endl;

    line[0] = 'h';

    cout << *chain << endl;
}

int main() {
    // smaller concept
    char two_d_arr [10][10];    // an array of array
    char (* ptr_to_char_arr) [10] = nullptr;  // a pointer to an array
    char * arr_of_ptr_to_char [10];  // an array of pointer
    char ** ptr_to_ptr_char = nullptr;  // a pointer to pointer
    // bigger concept

    cout << endl << "--> Try out two_d_arr: " << endl;
    cout << "Size is " << sizeof(two_d_arr) << " bytes" << endl;
    to_two_d_array(two_d_arr);
    to_ptr_to_arr(two_d_arr);  // These two pass the pointer pointing to the first 10 elements
    // to_arr_of_ptr(two_d_arr); // no known conversion from 'char [10][10]' to 'char **'
    // to_ptr_to_ptr(two_d_arr); // no known conversion from 'char [10][10]' to 'char **'
    cout << endl << "But if using type casting: " << endl;
    to_ptr_to_ptr((char **) two_d_arr);
    cout << endl;
    /* 
        Based on the compiler errors given from the last two function callings, we can see 
        both char * [10] and char ** are seen as char ** when being function formal parameters 
     */

    cout << endl << "--> Try out ptr_to_char_arr: " << endl;
    cout << "Size is " << sizeof(ptr_to_char_arr) << " bytes" << endl;
    to_two_d_array(ptr_to_char_arr);
    to_ptr_to_arr(ptr_to_char_arr);
    // to_arr_of_ptr(ptr_to_char_arr);
    // to_ptr_to_ptr(ptr_to_char_arr); // no known conversion from 'char (*)[10]' to 'char **'
    cout << endl;

    cout << endl << "--> Try out arr_of_ptr_to_char: " << endl;
    cout << "Size is " << sizeof(arr_of_ptr_to_char) << " bytes" << endl;
    // to_two_d_array(arr_of_ptr_to_char);  // no known conversion from 'char *[10]' to 'char (*)[10]'
    // to_ptr_to_arr(arr_of_ptr_to_char);  // no known conversion from 'char *[10]' to 'char (*)[10]'
    to_arr_of_ptr(arr_of_ptr_to_char);
    to_ptr_to_ptr(arr_of_ptr_to_char);
    cout << endl;
    /* 
        Both char [10][10] and char (*)[10] are seen as char (*)[10] when being function formal parameters 
     */

    cout << endl << "--> Try out ptr_to_ptr_char: " << endl;
    cout << "Size is " << sizeof(ptr_to_ptr_char) << " bytes" << endl;
    // to_two_d_array(ptr_to_ptr_char);
    // to_ptr_to_arr(ptr_to_ptr_char);
    to_arr_of_ptr(ptr_to_ptr_char);
    to_ptr_to_ptr(ptr_to_ptr_char);
    cout << endl;

    /*
      Conclusion:
        1. When you have a 2d array, a normal one not dynamic, you cannot pass it as char ** cause it 
           is actually a char (*)[], an 1d array. 
        2. If you want to use char ** as formal parameter for a 2d array, the array must be dynamic, 
           which means firstly you should create a char ** double pointer and then allocate memory to it.
        3. Alternative, we can use type casting when calling the function converting a char [][] to 
           char **. However, considering the function users' convenience, this might not be an ideal 
           solution.
     */

    cout << endl << "-->  Try with const for ptr_to_ptr_char: " << endl;
    // to_ptr_to_ptr_to_const(ptr_to_ptr_char);  // no known conversion from 'char **' to 'const char **'
    // to_ptr_to_ptr_to_const(two_d_arr);  // no known conversion from 'char **' to 'const char **'
    cout << "But if you try with type casting: " << endl;
    // However, this is ugly and dangerous according to the following discussion. 
    to_ptr_to_ptr_to_const((const char **) ptr_to_ptr_char);
    to_ptr_to_ptr_to_const((const char **) two_d_arr);
    cout << endl;
    /* 
      The reason why these is no conversion from char ** to const char ** has been discussed in 
      https://isocpp.org/wiki/faq/const-correctness#constptrptr-conversion, under the "Why am I 
      getting an error converting a Foo** → const Foo**?" question. In brief, it is preventing a unintentional
      change of const char due to this conversion. However what is strange is foo() is meanwhile allowed
      in c++
    */

    to_ptr_to_const_ptr(ptr_to_ptr_char);
    // to_ptr_to_const_ptr(two_d_arr); // no known conversion from 'char [10][10]' to 'char *const *'
    cout << "But if you try with type casting: " << endl;
    to_ptr_to_const_ptr((char **) two_d_arr);
    cout << endl;

    to_const_ptr_to_ptr(ptr_to_ptr_char);
    // to_const_ptr_to_ptr(two_d_arr); // no known conversion from 'char [10][10]' to 'char **const'
    cout << "But if you try with type casting: " << endl;
    to_const_ptr_to_ptr((char **) two_d_arr);
    cout << endl;

    // This would be the final solution to having a function that accepts all char **, const char ** and 
    // const char * const *. 
    // 
    // The additional const between the stars assures the compiler that your method will not try to store 
    // a non-const pointer to non-const char (in the array starting with the double pointer) and then use 
    // the point the stored pointer to a const char so that via the stored pointer, the const char can be 
    // changed, since this type (with extra const) declares that the pointer values are also const.
    // Please refer to the link above for more details.
    to_ptr_to_const_ptr_to_const(ptr_to_ptr_char);
    cout << endl;

    // In the end, I think this is not strange at all. What the restriction that "char **" cannot be converted 
    // to "const char **" is trying to prevent, is illegally modifying a "const char". However, in this strange
    // conversion, what has been changed in the end is a "char", which is always allowed. What has been stored
    // (if any) in the memory the *chain pointing to is still intact, though might be lost (memory leak).   
    strange_conversion();
}

