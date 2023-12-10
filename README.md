Project Description:

This search engine project is designed as a console application, providing a versatile and configurable solution that can run on any server or computer. Configuration settings are managed through JSON files, allowing for easy adaptation and integration into web-based search engines.

Key Principles:
1. **File Configuration:** Users can specify file names in the configuration file before launching the application, determining which files the search engine will analyze.

2. **Automatic Crawling and Indexing:** The search engine autonomously crawls through specified files, indexing them to facilitate efficient and relevant document retrieval.

3. **User Queries via JSON:** Users set search queries through a JSON file named requests.json, defining a set of words to locate relevant documents.

4. **Query Transformation:** The engine transforms the user's query into a list of words for processing.

5. **Index-Based Search:** Utilizing the index, the engine searches for documents containing all specified words in the query.

6. **Ranking and Sorting:** Search results are ranked, sorted, and presented to the user. The maximum number of documents in the response is configurable through the settings.

7. **Results Output:** The program generates an answers.json file, capturing the search results and providing an organized output for easy reference.

This search engine project aims to offer a flexible and user-friendly experience for information retrieval, with a focus on simplicity, configurability, and effective document ranking.
