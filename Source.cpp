#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

// Function Declarations:

void CallProcedure(string pName);

int callIntFunc(string proc, string param);

int callIntFunc(string proc, int param);

int inputValidation(int specialTest = 0);

void printHistogram();

void main()
{
	// Change the system colour because I just learned about it in my reading
	system("Color 02");

	int userInt = 0;
	int functionInt = 0;
	string userItem;

	while (userInt != 4) {
		CallProcedure("printMenu");
		// Run input validation with special test for menu
		userInt = inputValidation(1);
		// New line for whitespace
		std::cout << endl;

		switch (userInt) {
		case 1:
			CallProcedure("print_the_dictionary");
			break;

		case 2:
			std::cout << "Enter the item to search for: " << endl;
			std::cin >> userItem;
			// New line for whitespace
			std::cout << endl;
			std::cout << callIntFunc("num_times_sold", userItem) << " " << userItem << " sold" << endl;
			// New line for whitespace
			std::cout << endl;
			break;

		case 3:
			// Create/update the frequency file
			CallProcedure("write_the_dictionary");
			// Display the frequency file
			printHistogram();
			break;

		case 4:
			break;

		default:
			std::cout << "Something went wrong, your menu choice is invalid" << endl;
		}
	}
}

// Function Definitions:

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Validate user input is an integer. 
// Special test for use in user menu
int inputValidation(int specialTest) {
	string userInput;
	int inputToInt;

	// While loop breaks on return only 
	// Catches in the while loop to be able to use continue
	while (true) {
		try {
			cin >> userInput;
			inputToInt = stoi(userInput);
			// Special test for user menu
			if ((inputToInt < 1 || inputToInt > 4) && specialTest == 1) {
				throw std::runtime_error("Please enter a number between 1 and 4");
			}
			else {
				return inputToInt;
			}
		}
		catch (std::invalid_argument const& excpt) {
			// New line for whitespace
			std::cout << endl;
			std::cout << "Bad input: Please enter a number" << std::endl;
			// New line for whitespace
			std::cout << endl;
			continue;
		}
		catch (std::out_of_range const& excpt) {
			// New line for whitespace
			std::cout << endl;
			std::cout << "Integer overflow: please enter a smaller number" << std::endl;
			// New line for whitespace
			std::cout << endl;
			continue;
		}
		catch (std::runtime_error& excpt) {
			// New line for whitespace
			std::cout << endl;
			std::cout << excpt.what() << endl;
			// New line for whitespace
			std::cout << endl;
			continue;
		}
	}

}

// Produce a text-based histogram listing all items and the number of times each item was purchased (from frequency.dat).
void printHistogram() {
	ifstream inStream;
	string itemName;
	string timesSoldInput;
	int numTimesSoldInt;

	// Open the file
	inStream.open("frequency.dat");

	// If file did not open print error message and end function
	if (!inStream.is_open()) {
		std::cout << "Could not open file frequency.dat" << endl;
		return;
	}

	while (!inStream.fail()) {
		inStream >> itemName;
		inStream >> timesSoldInput;

		// Try to convert the count to ant int
		try {
			numTimesSoldInt = stoi(timesSoldInput);
		}
		catch (std::invalid_argument const& excpt) {
			// New line for whitespace
			std::cout << endl;
			std::cout << "Error in file! String instead of number!" << std::endl;
			// New line for whitespace
			std::cout << endl;
			break;
		}
		catch (std::out_of_range const& excpt) {
			// New line for whitespace
			std::cout << endl;
			std::cout << "Error in file! Integer overflow: number too large" << std::endl;
			// New line for whitespace
			std::cout << endl;
			continue;
		}

		// Print this line's item
		std::cout << itemName << " ";

		// Print a star for each sale
		for (int i = 0; i < numTimesSoldInt; i++) {
			std::cout << "*";
		}

		// Start an new line
		std::cout << endl;
	}

	std::cout << "Closing file" << endl;

	// Close file
	inStream.close();
}