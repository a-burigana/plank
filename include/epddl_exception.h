#ifndef EPDDL_EPDDL_EXCEPTION_H
#define EPDDL_EPDDL_EXCEPTION_H

#include <exception>
#include <string>

namespace epddl {
    class EPDDLException : public std::exception {
    public:
        EPDDLException(const std::string &file, const unsigned long row, const unsigned long col,
                       const std::string &error) :
                m_message{std::string{"In file: "} + file + ": " + std::to_string(row) + ":" + std::to_string(col) + ": " + error} {}

        char *what() {
            return const_cast<char *>(m_message.data());
        }

    private:
        const std::string m_message;
    };
}

#endif //EPDDL_EPDDL_EXCEPTION_H
