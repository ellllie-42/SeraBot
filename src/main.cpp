#include <iostream>

#include "SeraBot.h"
#include "python_interpreter.h"

std::string bot_token = "";

int main()
{
    SeraBot discord_test_01(bot_token);

    std::cout<<"Testing the integrated python interpreter."<<std::endl;
    python_interpreter py_int("Test_001", "python -u -i");
    std::string out_001;
    py_int << "print(\"Hello World!\")";
    py_int >> out_001;
    std::cout << "Python Console 001: " << out_001 << std::endl;


    std::cout<<py_int.running()<<std::endl;
    if(py_int.running() == true)
    {
        discord_test_01.start(dpp::st_wait);
    }
    else
    {
        std::cout<<"Interpreter not started. Shutting down."<<std::endl;
    }
    return 0;
}
