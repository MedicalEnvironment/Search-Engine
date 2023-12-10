#include <vector>
#include <string>
#include <thread>
#include <sstream>
#include "../include/InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    std::vector<int> threads_packs;
    int required_threads = input_docs.size();
    docs.resize(required_threads);
    int one_time_threads_max = std::thread::hardware_concurrency();
    while (required_threads > 0) {
        threads_packs.push_back((required_threads / one_time_threads_max > 0) ? one_time_threads_max : required_threads);
        required_threads -= one_time_threads_max;
    }

    std::mutex mtx_docs, mtx_freq_dictionary;
    auto DOCS_BASE_UPDATE = [&](const size_t& doc_id) {
        std::stringstream TEXT_DOC(input_docs[doc_id]);
        std::string word, text = "";

        while (TEXT_DOC >> word) {
            {
                std::lock_guard<std::mutex> lock(mtx_freq_dictionary);
                freq_dictionary[word];
            }
            text += word + " ";
        }

        std::lock_guard<std::mutex> lock(mtx_docs);
        docs[doc_id] = text;
    };

    std::vector<std::thread> threads;
    size_t doc_id = 0;
    for (auto threads_pack : threads_packs)
        while (threads_pack-- != 0)
            threads.push_back(std::thread(DOCS_BASE_UPDATE, doc_id++));
    for (int i = 0; i < threads.size(); ++i)
        threads[i].join();

    Entry entry;
    for (auto key_it = begin(freq_dictionary); key_it != end(freq_dictionary); ++key_it) {
        std::string key_word = key_it->first;

        for (entry.doc_id = 0; entry.doc_id < docs.size(); ++entry.doc_id) {
            std::stringstream DATA(docs[entry.doc_id]);
            std::string word;
            entry.count = 0;

            while (DATA >> word)
                if (word == key_word) ++entry.count;

            if (entry.count != 0)
                key_it->second.push_back(entry);
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> vec;
    auto key_it = freq_dictionary.find(word);
    return (key_it != end(freq_dictionary)) ? key_it->second : vec;
}