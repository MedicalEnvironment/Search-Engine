#pragma once

#include "../include/InvertedIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;
    bool operator == (const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx) { };

    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string>& queries_input, int responses_limit);

private:
    InvertedIndex _index;
};