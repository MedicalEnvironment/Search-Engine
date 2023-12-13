#include <vector>
#include <sstream>
#include "../include/SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string>& queries_input, int responses_limit)
{
    std::vector<std::vector<RelativeIndex>> Search_Result;
    Search_Result.resize(queries_input.size());
    int query_id = 0;

    for (auto query : queries_input) {

        std::stringstream DATA(query);
        std::string word;

        std::map<std::string, std::vector<Entry>> map_sort_by_word;
        while (DATA >> word)
            map_sort_by_word[word];

        for (auto& [word, docs_info] : map_sort_by_word)
            docs_info = _index.GetWordCount(word);

        std::map<int, int> map_resort_by_doc_id;
        for (auto& [word, docs_info] : map_sort_by_word)
            for (auto doc_info : docs_info)
                map_resort_by_doc_id[doc_info.doc_id] += doc_info.count;

        if (!map_resort_by_doc_id.empty()) {

            std::multimap<int, int> map_resost_by_count;
            auto it_2 = rbegin(map_resort_by_doc_id);
            for ( ; it_2 != rend(map_resort_by_doc_id); ++it_2)
                map_resost_by_count.emplace(it_2->second, it_2->first);

            auto it_3 = rbegin(map_resost_by_count);
            int max_count = it_3->first;
            RelativeIndex index;
            for ( ; it_3 != rend(map_resost_by_count); ++it_3) {
                index.doc_id = it_3->second;
                index.rank = (it_3->first == max_count) ? 1.f : (float)(it_3->first) / max_count;
                Search_Result[query_id].push_back(index);
                if (--responses_limit == 0) break;
            }
        }

        ++query_id;
    }

    return Search_Result;
}