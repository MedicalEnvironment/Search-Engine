#include "Skillbox_Search_Engine.h"

int main()
{
    try
    {
        ConverterJSON data;
        InvertedIndex index;
        index.UpdateDocumentBase(data.GetTextDocuments());

        SearchServer search(index);
        data.PutAnswers(search.Search(data.GetRequests(), data.GetResponsesLimit()));
    }
    catch (const ConfigFileEmpty_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const ConfigFileMissing_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const ConfigFileVersionEmpty_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const ConfigFileVersionIncorrect_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const RequestsFileEmpty_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const RequestsFileMissing_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const MoreThen1000WordsText_Ecxeption& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const MoreThen100CharsWord_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const MoreThen1000Requests_Ecxeption& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const MoreThen10WordsRequests_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}