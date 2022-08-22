/*
Nicholas Porbansky 
Final Project CS210
Functional

*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int userInput;
string thread;
string lineFile;

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


void DisplayMenu() // menu to display user input options
{
	cout << "----------------- User Menu -----------------\n";
	cout << "1: Produce a list of all items purchased with quantities \n";
	cout << "2: Display how many times a specific item was sold \n";
	cout << "3: Produce a histogram of sales data \n";
	cout << "4: Exit \n\n";
	cout << "Enter your selection as a number: 1, 2, 3, or 4. \n";
	cout << "---------------------------------------------\n\n";
	
	cin >> userInput;

	if (userInput == 1)
	{
		cout << "\n\nDisplaying tems and quantities sold today: \n\n";
		CallProcedure("ItemCounter");  // call to python ItemCounter
		cout << "\n\n";
	}
	else if (userInput == 2)
	{
		cout << "\n\nPlease enter the item name: \n\n";
		cin >> thread;
		cout << endl;
		cout << endl;
		cout << "Printing the sales for " << thread << ":\n\n";
		cout << thread << ": " << callIntFunc("NumItemCounter", thread) << "\n\n";  // call to python NumItemCounter
	}
	else if (userInput == 3)
	{
		cout << "\n\nWriting items and quantities sold today to a file: \n\n";
		CallProcedure("ItemWriter");  // call to python ItemWriter
		cout << endl;
		cout << endl;

		ifstream frequencyFile("frequency.dat");
		string item;
		int count;

		while (getline(frequencyFile, lineFile)) // parse file line by line
		{
			istringstream iss(lineFile); 
			if (!(iss >> item >> count)) { break; } // break the loop
			cout << item << " " << string(count, '*') << endl; // print out histogram
		}
		cout << "\n\n";
	}
	else if (userInput == 4) {
		cout << "\n\nExiting program . . .  \n" << endl;
		exit(EXIT_SUCCESS);
	}
	else {    // input validation
		cout << "\n\nPlease enter a valid input . . . \n\n";
		exit(EXIT_SUCCESS);
	}
}


void main()
{
	while (true)
	{
		DisplayMenu();
	}
}