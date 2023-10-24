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

    class EPDDLLexerException : public EPDDLException {
    public:
        EPDDLLexerException(const std::string &file, const unsigned long row, const unsigned long col,
                            const std::string &error) :
                EPDDLException(file, row, col, error) {}
    };

    class EPDDLParserException : public EPDDLException {
    public:
        EPDDLParserException(const std::string &file, const unsigned long row, const unsigned long col,
                             const std::string &error) :
                EPDDLException(file, row, col, error) {}
    };

    class EPDDLBadChoicePointException : public EPDDLParserException {
    public:
        EPDDLBadChoicePointException(const std::string &file, const unsigned long row, const unsigned long col,
                                     const std::string &error) :
                EPDDLParserException(file, row, col, error) {}
    };
}

#endif //EPDDL_EPDDL_EXCEPTION_H
