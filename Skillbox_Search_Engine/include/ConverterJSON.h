#pragma once

#include <vector>
#include "../include/SearchServer.h"

class ConfigFileEmpty_Exception : public std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Config file is empty.";
    }
};
class ConfigFileMissing_Exception : std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Config file is missing.";
    }
};
class ConfigFileVersionEmpty_Exception : public std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Config file version is empty.";
    }
};
class ConfigFileVersionIncorrect_Exception : public std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Config file has incorrect file version.";
    }
};
class RequestsFileEmpty_Exception : public std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Requests file is empty.";
    }
};
class RequestsFileMissing_Exception : std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Requests file is missing.";
    }
};
class MoreThen1000WordsText_Ecxeption : public std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Text file contains more than 1.000 words.";
    }
};
class MoreThen100CharsWord_Exception : std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Word from text file contains more than 100 chars.";
    }
};
class MoreThen1000Requests_Ecxeption : public std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Requests file contains more than 1.000 requests.";
    }
};
class MoreThen10WordsRequests_Exception : std::exception {
public:
    const char* what() const noexcept override {
            return "Fail. Request from requests file contains more than 10 words.";
    }
};

class ConverterJSON {
public:

    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void PutAnswers(std::vector<std::vector<struct RelativeIndex>> answers);
};