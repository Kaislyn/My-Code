// 单词接龙 dfs版

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> words(26);
vector<vector<bool>> sign(26);
vector<int> ans;
int word_length = 0;
int word_num = 0;

void dfs(char start) {
    int idx = start - 'a';
    bool found = false;
    for (int i = 0; i < sign[idx].size(); i++) {
        // 判断是否还有单词可以继续参与接龙
        if (!sign[idx][i]) found = true;
    }
    if (!found) {
        ans.push_back(word_length - word_num + 1);
        return;
    }
    for (int i = 0; i < words[idx].size(); i++) {
        if (!sign[idx][i]) {
            word_length += words[idx][i].size();
            word_num++;
            sign[idx][i] = 1;
            dfs(words[idx][i].back());
            word_length -= words[idx][i].size();
            word_num--;
            sign[idx][i] = 0;
        }
    }
}

int main() {
    int num;
    cin >> num;
    string word;
    char start;
    while (num--) {
        cin >> word;
        // 每个单词可以出现两次
        int idx = word.front() - 'a';
        words[idx].push_back(word);
        words[idx].push_back(word);
        sign[idx].push_back(0);
        sign[idx].push_back(0);
    }
    cin >> start;
    if (sign[start - 'a'].empty()) {
        cout << 0 << endl;
        return 0;
    }

    dfs(start);

    int max_ = 0;
    for (auto& i : ans) max_ = max(max_, i);
    cout << max_ << endl;
    return 0;
}