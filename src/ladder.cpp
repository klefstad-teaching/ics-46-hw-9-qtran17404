#include "ladder.h"

using namespace std;


void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int len1 = str1.size(), len2 = str2.size();
    if(abs(len1-len2) > 1) return false;

    int i = 0, j = 0, diff = 0;

    while(i < len1 && j < len2)
    {
        if(str1[i] != str2[j])
        {
            ++diff;
      
        if(diff > d) return false;
        if(len1 > len2) ++i;
        else if(len1 < len2) ++j;
        else { ++i; ++j;}
        }
        else
        {
            ++i; ++j;
        }
    }
    return true;
}


bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word)
    {
        error(begin_word,end_word, "Start and end words gotta be different");
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for(const string& word : word_list)
        {
            if(is_adjacent(last_word,word) && !visited.count(word))
            {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == end_word) return new_ladder;
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
    if(!file)
    {
        cerr << "Error: Couldn't open " << file_name << endl;
    }
    string word;
    while(file >> word)
    {
        word_list.insert(word);
    }
}


void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }

    for(size_t i = 0; i < ladder.size(); ++i)
    {
        cout << "Word ladder found: " << ladder[i];
        if(i < ladder.size() -1) cout << " ";
    }
    cout << endl;
}

void verify_word_ladder()
{
    vector<string> ladder;
    cout << "Enter a word ladder";
    string word;
    while(cin>> word)
    {
        ladder.push_back(word);
    }

    if(ladder.size() < 2)
    {
        cout << "Invalid word ladder. Must be at least 2 words." << endl;
        return;
    }


    for(size_t i = 1; i < ladder.size(); ++i)
    {
        if(!is_adjacent(ladder[i-1], ladder[i]))
        {
            cout << ladder[i - 1] << " → " << ladder[i] << " is not a valid step." << endl;
            return;
        }
    }
    cout << "Valid word ladder!" << endl;
}