# 2d_array_passing_research
A small trying out about the restriction that "char **" cannot be converted to "const char **" in C++. 

For example, 

If we have a double pointer pointing to a dynamic two dimensional array:
  char ** two_d_array;
and then we want to pass it to a function:
  foo(const char ** arr);
 where the "const" is trying to indicate the funciton is not going to change the element in the array. 
 
 However, the compiler would then give an error that "no known conversion from 'char **' to 'const char **'", and the code cannot be compied, which is due to C++ is banning such a conversion out of safe consideration. 
