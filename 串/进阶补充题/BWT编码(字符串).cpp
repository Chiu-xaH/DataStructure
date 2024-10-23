#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//生成原文的循环队列
vector<string> generateCyclicRotations(const string &text) {
    int n = text.size();
    vector<string> rotations;
    for (int i = 0;i < n;i++) {
        // 每次生成的字符串从i开始，循环拼接
        rotations.push_back(text.substr(i) + text.substr(0, i));
    }
    return rotations;
}
//加密
pair<string, int> encrypt(const string &text) {
    vector<string> rotations = generateCyclicRotations(text);
    vector<pair<string, int>> rotationsWithIndex; // 存储循环队列和原始索引

    for (int i = 0; i < rotations.size(); i++) {
        rotationsWithIndex.push_back({rotations[i], i});
    }

    // 排序
    stable_sort(rotationsWithIndex.begin(), rotationsWithIndex.end());

    string ciphertext;
    int originalIndex = 0; // 原文所在的索引
    for (int i = 0; i < rotationsWithIndex.size(); i++) {
        ciphertext += rotationsWithIndex[i].first.back(); // 取最后一个字符
        if (rotationsWithIndex[i].second == 0) {
            originalIndex = i; // 记录原文在排序后的位置
        }
    }

    return {ciphertext, originalIndex};
}
//解密
string decrypt(const string &ciphertext,int index) {
    int n = ciphertext.size();
    vector<string> table(n, string(n, ' '));
    //逐列重建排序表
    for (int i = 0; i < n; i++) {
        //把密文的每个字符加到每个字符串的前面
        for (int j = 0; j < n; j++) {
            table[j] = ciphertext[j] + table[j];
        }
        stable_sort(table.begin(), table.end());
    }
    return table[index]; 
}

int main() {
    string text,mode;
    int index;
    cout << "请输入加密(e)或解密(d)模式: ";
    cin >> mode;

    if (mode == "e") {
        cout << "输入原文: ";
        cin >> text;
        auto [encrypted, index] = encrypt(text);
        cout << "加密后: " << encrypted << " 索引号: " << index << endl;
    } else if (mode == "d") {
        cout << "输入密文: ";
        cin >> text;
        cout << "输入索引号: ";
        cin >> index;
        string decrypted = decrypt(text, index);
        cout << "解密后: " << decrypted << endl;
    } else {
        cout << "无效!" << endl;
    }

    return 0;
}
