# 8-1-Portfolio

# Summarize the project and what problem it was solving.
Project 3 from CS 210:

Daily Sales Data

Three requirements for a given text-based input file that contains a list of purchased items for a single day:
1. Produce a list of all items purchased in a given day along with the number of times each item was purchased.
2. Produce a number representing how many times a specific item was purchased in a given day.
3. Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased.

The main method handling user input and displaying data in done in C++. The C++ program will call methods in a Python program written to analyze the data on the given text file.

# What did you do particularly well?
Both the C++ and Python files are easy to understand. 
All my exception handling is done in the functions, which keeps the try/catch statements together and clear.
My Python functions are small and "do one thing."
Incorporating C++ and Python into one project.

# Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
The C++ functions could be reduced into smaller functions. When breaking them up into smaller functions I should probably collect them into their own class for easier reuse.
Exception handling for the C++ code calls to Python. This will make addition to the code less risky.
Making the Python code a class to better encapsulate the static dictionary.
Write test files for the code. This will enable easier refactoring and addition to the code. This is a habit I mean to get into when writing my code. 

# Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
The most challenging part was handling the transitions between C++ and Python. It was my first time both doing a lot of file processing and writing in two different languages. My solution was to write a Python program that could do all the necessary data analysis and return it in the proper format. I then could focus on writing C++ to call these Python functions and display the returned data. This compartmentalized the number of errors I would get at once. I did have to change the fill_dictionary_with_data() function into a helper function called in each method instead of a onetime function call. Because the main method moved to a different script, the Dictionary needed to be filled each time a function was called, instead of only once.

# What skills from this project will be particularly transferable to other projects or course work?
File handling in Python. 
File creation in Python. 
Data analysis using a dictionary in Python.
Input validation and other exception handling practice in C++.

# How did you make this program maintainable, readable, and adaptable?
The Python script could be reused to analyze text files in the same format.
The Python script could be adapted to analyze text files in similar formats.
The Python script could be adapted to do different analysis using a different data structure.
The input validation could be reused and adapted for many other programs.

# Please note this project is a Visual Studio project using C++ and Python. These are the set up instructions I used: https://www.youtube.com/watch?v=yV5x_Ij_npo

