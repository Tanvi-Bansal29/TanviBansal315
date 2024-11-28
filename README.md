# Longest Compounded Word Finder 

The solution identifies the longest compound word and the second longest compound word in a dataset. A compound word is formed by concatenating smaller words from the same dataset. This implementation uses a Trie for efficient prefix matching and a queue-based approach to process potential compound words.

---

# Approach  
 1. Data Structure Used 
- Trie (Prefix Tree)  
  A hierarchical data structure used to store words efficiently. It allows fast prefix matching to check if a word or part of a word exists in the dataset.

- Queue:  
  Stores pairs of words and their suffixes that need further processing to determine if they are compound words.

---

# 2. Build Phase
- The program reads the dataset (a file containing words, one word per line).  
- Each word is inserted into the Trie. While inserting:
  - Prefixes that match existing words in the Trie are identified.  
  - For each valid prefix, the remaining part of the word (suffix) is added to the queue.  
- This phase prepares the Trie for fast lookups and initializes the queue for processing compound words.

---

# 3. Processing the Queue  
- The queue is processed iteratively. For each word-suffix pair:
  - If the suffix exists in the Trie as a complete word, the current word is a valid compound word.  
  - If the word is longer than the previously identified longest or second-longest compound word, it updates these values.  
  - If the suffix is not a complete word, its prefixes are checked, and new suffixes are added to the queue for further examination.

---

# 4. Output  
- After processing all queue entries, the program outputs:  
  - The longest compound word.  
  - The second-longest compound word.  
  - The time taken to process the dataset.  

This approach ensures efficient handling of large datasets by combining the Trie’s fast lookups with the queue’s systematic exploration of potential compound words.
