#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << word1 << "-" << word2 << ": " << msg;
}


bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    int i = 0, j = 0, diff_count = 0;
    
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            ++diff_count;
            if (diff_count > d) return false;
            
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else {
                ++i;
                ++j;
            }
        } else {
            ++i;
            ++j;
        }
    }
    diff_count += (len1 - i) + (len2 - j);
    
    return diff_count <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited.insert(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {};
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) return;

    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    file.close();
}


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    };

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ladder[i];
    }
    cout << "\n";
}


bool verify_word_ladder(const vector<string>& ladder, const set<string>& word_list) {
    if (ladder.empty()) return false;

    string curr;
    for (size_t i = 1; i < ladder.size(); ++i) {
        curr = ladder[i];
        if (!is_adjacent(ladder[i - 1], curr) || word_list.find(curr) == word_list.end()) return false;
    }
    return true;
}
