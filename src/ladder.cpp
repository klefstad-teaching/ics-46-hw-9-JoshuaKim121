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
            else ++i; ++j;
        } else {
            ++i;
            ++j;
        }
    }
    diff_count += (len1 - i) + (len2 - j);
    
    return diff_count == d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}