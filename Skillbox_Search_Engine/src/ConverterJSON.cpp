#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include "nlohmann/json.hpp"
#include "../include/ConverterJSON.h"
#include "config.h"

namespace version {
    int getVersion() {
        return(PROJECT_VERSION);
    }
}

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::ifstream config_FILE("config.json");
    if (!config_FILE.is_open()) throw ConfigFileMissing_Exception();

    nlohmann::json json_data;
    config_FILE >> json_data;
    config_FILE.close();

    std::cout << "Starting " << json_data["config"]["name"] << std::endl;
    if (json_data["config"].empty()) throw ConfigFileEmpty_Exception();
    if (json_data["config"]["version"].empty()) throw ConfigFileVersionEmpty_Exception();
    {
        std::string parsed_version = "";
        std::string version = json_data["config"]["version"];
        for (auto simbol : version)
            if(simbol != '.') parsed_version += simbol;
        if (parsed_version != std::to_string(version::getVersion())) throw ConfigFileVersionIncorrect_Exception();
    }

    // preparing start packets of threads and text_docs
    std::vector<std::string> text_docs;
    int required_threads = json_data["files"].size();
    text_docs.resize(required_threads);

    std::vector<int> threads_packs;
    int one_time_threads_max = std::thread::hardware_concurrency();
    while (required_threads > 0) {
        threads_packs.push_back((required_threads / one_time_threads_max > 0) ? one_time_threads_max : required_threads);
        required_threads -= one_time_threads_max;
    }

    // FUNCTION - DOCS_BASE_LOAD
    std::mutex mtx_text_docs;
    auto DOCS_BASE_LOAD = [&](const size_t& doc_id) {
        std::string path = json_data["files"][doc_id];
        std::ifstream text_FILE(path);
        std::string word, text = "";

        size_t word_counter = 0;
        while (text_FILE >> word) {
            if (word_counter++ > 1000) throw MoreThen1000WordsText_Ecxeption();
            if (word.length() > 100) throw MoreThen100CharsWord_Exception();
            text += word + " ";
        }

        std::lock_guard<std::mutex> lock(mtx_text_docs);
        text_docs[doc_id] = text;
    };

    // start packets of threads for loading text_docs
    std::vector<std::thread> threads;
    size_t doc_id = 0;
    for (auto threads_pack : threads_packs)
        while (threads_pack-- != 0)
            threads.push_back(std::thread(DOCS_BASE_LOAD, doc_id++));
    for (int i = 0; i < threads.size(); ++i)
        threads[i].join();

    return text_docs;
}

int ConverterJSON::GetResponsesLimit()
{
    std::ifstream config_FILE("config.json");
    nlohmann::json json_data;
    config_FILE >> json_data;
    config_FILE.close();
    return (json_data["config"]["max_responses"].empty()) ? 5 : (int)json_data["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::ifstream requests_FILE("requests.json");
    if (!requests_FILE.is_open()) throw RequestsFileMissing_Exception();

    nlohmann::json json_data;
    requests_FILE >> json_data;
    requests_FILE.close();

    if (json_data["requests"].empty()) throw RequestsFileEmpty_Exception();
    if (json_data["requests"].size() > 1000) throw MoreThen1000Requests_Ecxeption();

    for (std::string request : json_data["requests"]) {
        std::stringstream DATA(request);
        std::string word;
        size_t word_counter = 0;

        while (DATA >> word)
            ++word_counter;

        if (word_counter > 10) throw MoreThen10WordsRequests_Exception();
    }

    return json_data["requests"];
}

void ConverterJSON::PutAnswers(std::vector<std::vector<struct RelativeIndex>> answers)
{
    nlohmann::json json_data;

    for (int answer_number = 0; answer_number < answers.size(); ++answer_number) {

        // building requests' name
        std::string request_name = "request";
        size_t number_lenght = std::to_string(answer_number).length();
        for (size_t zero_counter = 0; zero_counter < (4 - number_lenght); ++zero_counter)
            request_name += '0';
        request_name += std::to_string(answer_number + 1);

        // load answers' result
        if (answers[answer_number].empty())
            json_data["answers"][request_name]["result"] = "false";
        else {
            json_data["answers"][request_name]["result"] = "true";

            if (answers[answer_number].size() == 1)
                json_data["answers"][request_name] = { { "docid", answers[answer_number][0].doc_id }, { "rank", answers[answer_number][0].rank } };
            else
                for (auto element : answers[answer_number])
                    json_data["answers"][request_name]["relevance"].push_back("docid: " + std::to_string(element.doc_id) + ", rank:" + std::to_string(element.rank));
        }
    }

    std::ofstream answers_FILE("answers.json", std::ios::trunc);
    answers_FILE << json_data;
    answers_FILE.close();
}