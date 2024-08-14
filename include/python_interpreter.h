#ifndef PYTHON_INTERPRETER_H
#define PYTHON_INTERPRETER_H

#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <thread>
#include <mutex>
#include <string>

namespace bp = boost::process;

class python_interpreter
{
    public:
        python_interpreter(std::string console_name, std::string python_command = "python");
        ~python_interpreter();

        std::string get_console_name();
        void execute_file(std::string file_path);

        bool running();

        python_interpreter& operator<<(const std::string& command);
        python_interpreter& operator>>(std::string& output);


    protected:
        std::string console_name;

    private:

        bp::ipstream pipe_out;
        bp::opstream pipe_in;
        bp::child interpreter;

        std::mutex interpreterMutex;
};

#endif // PYTHON_INTERPRETER_H
