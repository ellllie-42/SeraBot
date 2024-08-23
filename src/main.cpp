#include <iostream>
#include <fstream>

#include "SeraBot.h"
#include "python_interpreter.h"

int main()
{
    SeraBot discord_test_01(token_from_file(std::ifstream("../Tokens/serabot.txt")));

    std::cout<<"Testing the integrated python interpreter."<<std::endl;
    python_interpreter py_int;
    std::string out_001, out_002;
    py_int << "print(\"Hello World!\")"; //literally all you have to do the interpreter class will do the rest
    std::getline(py_int, out_001);
    std::cout << "Python Console 001: " << out_001 << std::endl;
    py_int << "x = 2";
    py_int << "y = 3";
    py_int << "print('x + y =' + str(x+y))";
    py_int << "print('Henlo Wormld')";
    py_int << "print('i like trains')";
    std::getline(py_int, out_002);
    std::cout << "Python Console 001: " << out_002 << std::endl;
    while(std::getline(py_int, out_001))
    {
        std::cout << "Python Console 001: " << out_001 << std::endl;
    }

    if(py_int.running() == true)
    //if(true != true)
    {
        discord_test_01.start(dpp::st_wait);
    }
    else
    {
        std::cout<<"Interpreter not started. Shutting down."<<std::endl;
    }
    return 0;
}
