#include "python_interpreter.h"
#include <boost/process.hpp>
#include <boost/process/windows.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <string>
#include <fstream>
#include <iostream>
#include <format>

struct new_window : ::boost::process::detail::handler_base {
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const {
        e.creation_flags = ::boost::winapi::CREATE_NEW_CONSOLE_;
    }
};

python_interpreter::python_interpreter(std::string console_name, std::string python_command) {
    auto env = ::boost::this_process::environment();
    interpreter = bp::child(python_command, env, new_window{}, bp::std_in < pipe_in, bp::std_out > pipe_out);

    std::string const test_str = "initialized";
    bool started = false;
    while (this->interpreter.running() && !started) {
        // Send a command to the Python interpreter
        *this << std::format("print('{}')", test_str);

        // Read output from the Python interpreter
        std::string out_001;
        *this >> out_001;

        // Check if the output matches the expected test string
        started = (out_001.find(test_str) != std::string::npos);
    }

}

python_interpreter::~python_interpreter() {
    if (this->interpreter.running()) {
        *this << "exit()\n";
        this->interpreter.wait();
    }
    pipe_in.close();
    pipe_out.close();
}

void python_interpreter::execute_file(std::string file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + file_path);
    }

    std::string line;
    while (std::getline(file, line)) {
        *this << line << "\n";
    }
}

python_interpreter& python_interpreter::operator<<(const std::string& command) {
    pipe_in << command << std::endl;  // Flush after sending command
    pipe_in.flush();
    return *this;
}

python_interpreter& python_interpreter::operator>>(std::string& output) {
    std::getline(pipe_out, output);
    return *this;
}

bool python_interpreter::running() {
    return this->interpreter.running();
}
