**Project Description: Search Engine**

**Overview:**
A console-based text data search engine tailored for local use. Configured through JSON files, this application efficiently indexes text files, processes client queries, and produces search results featuring a prioritized list of document relevance for each specific query.

**ConverterJSON Class:**
The heart of the project is the ConverterJSON class, meticulously designed to handle various JSON interactions. Its key functionalities include:
- Reading configuration data from config.json.
- Converting requests in JSON format.
- Generating responses in the specified JSON format.

**Configuration Files:**
The configuration file (config.json) holds crucial information for the application's functionality, including the search engine's name, version, database update time, and maximum number of responses. The file also specifies the paths to files that need to be searched.

**File Structure and Field Descriptions:**
- **config:** General information, mandatory for application startup.
- **name:** Name of the search engine, displayed during application launch.
- **version:** Search engine version number, checked for compatibility.
- **max_responses:** Maximum number of responses to a single request.
- **files:** Paths to files for searching.

**Requests and Answers Files:**
The requests.json file contains queries to be processed by the search engine, while answers.json records the search results. The latter includes detailed information about the relevance and ranking of documents for each query.

**InvertedIndex Class:**
To optimize the search process, the InvertedIndex class is introduced. It efficiently stores and indexes words found in documents, ensuring a rapid and relevant search experience.

**SearchServer Class:**
The SearchServer class utilizes the InvertedIndex class to process search queries. It employs a sophisticated algorithm that breaks down the query, sorts words by frequency, and ranks documents based on relevance.

**Testing System Integration:**
The project is fortified with a robust testing system using the Google Test library. This ensures the correctness of individual modules, facilitating quick checks for code changes and eliminating potential errors.

**Final Output:**
The culmination of this project is an intelligent search engine that seamlessly interacts with JSON files, efficiently processes user queries, and delivers highly relevant search results.

Explore the project directories for detailed implementations and testing scenarios, ensuring a reliable and accurate search engine experience.
