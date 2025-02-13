#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

string subtitution(char c, char table[6][6], string title) {
    string res = "";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (c == table[i][j]) {
                res += title[i];
                res += title[j];
                return res;
            }
        }
    }
}

string encryptXXXXXX(string plaintext, char table[6][6], string title, string keyword) {
    cout << "-----------ENCRYPT-----------" << endl;
    string sub = "";
    for (int i = 0; i < plaintext.size(); i++) {
        if (plaintext[i] == ' ') continue;
        sub += subtitution(plaintext[i], table, title);
    }
    vector<vector<char>> toMatrix;

    int row = 0;
    int i = 0;

    while (i < sub.size()) {
        vector<char> temp;
        for (int j = 0; j < keyword.size(); j++) {
            temp.push_back(sub[i]);
            i++;
            if (i >= sub.size()) break;
         }
        toMatrix.push_back(temp);
    }

    string copyKey = keyword;
    sort(copyKey.begin(), copyKey.end());
    string encrypted = "";

    for (int j = 0; j < keyword.size(); j++) {
        for (int k = 0; k < keyword.size(); k++) {
            if (keyword[k] == copyKey[j]) {
                for (int u = 0; u < toMatrix.size(); u++) {
                    encrypted += toMatrix[u][k];
                }
            }
        }
    }

    return encrypted;
}

string decryptXXXXXX(string ciphertext, char table[6][6], string title, string keyword) {
    cout << "-----------DECRYPT-----------" << endl;
    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < keyword.size(); i++) {
        keyOrder.push_back(make_pair(keyword[i], i));
    }
    sort(keyOrder.begin(), keyOrder.end());

    int colLength = ciphertext.size() / keyword.size();
    vector<string> columns(keyword.size());
    int index = 0;
    for (int i = 0; i < keyOrder.size(); i++) {
        columns[keyOrder[i].second] = ciphertext.substr(index, colLength);
        index += colLength;
    }

    string intermediateCiphertext = "";
    for (int i = 0; i < colLength; i++) {
        for (int j = 0; j < keyword.size(); j++) {
            intermediateCiphertext += columns[j][i];
        }
    }

    string plaintext = "";
    for (int i = 0; i < intermediateCiphertext.size(); i += 2) {
        char rowChar = intermediateCiphertext[i];
        char colChar = intermediateCiphertext[i + 1];
        int row = title.find(rowChar);
        int col = title.find(colChar);
        if (row != string::npos && col != string::npos) {
            plaintext += table[row][col];
        }
    }

    return plaintext;
}

int main() {
    string keyword = "MARK", title = "HCMUNS";
    char table[6][6] = {
        {'8', 'p', '3', 'd', '1', 'n'},
        {'l', 't', '4', 'o', 'a', 'h'},
        {'7', 'k', 'b', 'c', '5', 'z'},
        {'j', 'u', '6', 'w', 'g', 'm'},
        {'x', 's', 'v', 'i', 'r', '2'},
        {'9', 'e', 'y', '0', 'f', 'q'}
    };
    string plaintext = "attack at 10 pm";
    string ciphertext = encryptXXXXXX(plaintext, table, title, keyword);
    cout << "Results: " << ciphertext << endl;
    string decryptedtext = decryptXXXXXX(ciphertext, table, title, keyword);
    cout << "Results: " << decryptedtext << endl;
	return 0;
}