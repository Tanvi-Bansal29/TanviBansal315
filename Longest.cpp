#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <chrono>

class Trie
{
public:
  struct TrieNode
  {
    std::unordered_map<char, TrieNode *> children;
    bool isEndOfWord = false;
  };

  TrieNode *root;

  Trie()
  {
    root = new TrieNode();
  }

  void insert(const std::string &word)
  {
    TrieNode *node = root;
    for (char c : word)
    {
      if (!node->children.count(c))
      {
        node->children[c] = new TrieNode();
      }
      node = node->children[c];
    }
    node->isEndOfWord = true;
  }

  std::vector<std::string> getPrefixes(const std::string &word)
  {
    std::vector<std::string> prefixes;
    TrieNode *node = root;
    std::string prefix;
    for (char c : word)
    {
      if (!node->children.count(c))
        break;
      node = node->children[c];
      prefix += c;
      if (node->isEndOfWord)
      {
        prefixes.push_back(prefix);
      }
    }
    return prefixes;
  }

  bool contains(const std::string &word)
  {
    TrieNode *node = root;
    for (char c : word)
    {
      if (!node->children.count(c))
        return false;
      node = node->children[c];
    }
    return node->isEndOfWord;
  }
};

class Solution
{
public:
  Trie trie;
  std::deque<std::pair<std::string, std::string>> queue;

  void buildTrie(const std::string &filePath)
  {
    std::ifstream file(filePath);
    if (!file.is_open())
    {
      std::cerr << "Error: Cannot open the file!" << std::endl;
      exit(1);
    }

    std::string line;
    while (std::getline(file, line))
    {
      std::string word = line;
      std::vector<std::string> prefixes = trie.getPrefixes(word);
      for (const std::string &prefix : prefixes)
      {
        queue.push_back(std::make_pair(word, word.substr(prefix.length())));
      }
      trie.insert(word);
    }
    file.close();
  }

  std::pair<std::string, std::string> findLongestCompoundWords()
  {
    std::string longestWord = "";
    int longestLength = 0;
    std::string secondLongest = "";

    while (!queue.empty())
    {
      std::pair<std::string, std::string> front = queue.front();
      queue.pop_front();

      std::string word = front.first;
      std::string suffix = front.second;

      if (trie.contains(suffix) && word.length() > longestLength)
      {
        secondLongest = longestWord;
        longestWord = word;
        longestLength = word.length();
      }
      else
      {
        std::vector<std::string> prefixes = trie.getPrefixes(suffix);
        for (const std::string &prefix : prefixes)
        {
          queue.push_back(std::make_pair(word, suffix.substr(prefix.length())));
        }
      }
    }

    return std::make_pair(longestWord, secondLongest);
  }
};

int main()
{
  Solution sol;
  auto start = std::chrono::high_resolution_clock::now();
  // sol.buildTrie("Input_01.txt");                              //{if you want to run this comment the other and then run}
  sol.buildTrie("Input_02.txt");
  std::pair<std::string, std::string> result = sol.findLongestCompoundWords();
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "Longest Compound Word: " << result.first << std::endl;
  std::cout << "Second Longest Compound Word: " << result.second << std::endl;
  std::cout << "Time taken: "
            << std::chrono::duration<double>(end - start).count()
            << " seconds" << std::endl;

  return 0;
}
