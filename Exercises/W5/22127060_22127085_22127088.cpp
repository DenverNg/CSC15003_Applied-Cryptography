#include <iostream>
#include <cstring>

using namespace std;

// Hàm mã hóa Vigenere
char* encryptMessage(char* ps, char* key) {
    int psLength = strlen(ps);
    int keyLength = strlen(key);
    char* encryptedMessage = new char[psLength + 1];

    int keyIndex = 0; // Chỉ số của key, chỉ tăng nếu gặp ký tự chữ
    for (int i = 0; i < psLength; i++) {
        if (ps[i] >= 'a' && ps[i] <= 'z') {
            int shift = key[keyIndex % keyLength] - 'a';
            encryptedMessage[i] = 'a' + (ps[i] - 'a' + shift) % 26;
            keyIndex++; // Chỉ tăng khi xử lý chữ cái
        }
        else {
            encryptedMessage[i] = ps[i]; // Giữ nguyên khoảng trắng và ký tự khác
        }
    }
    encryptedMessage[psLength] = '\0';
    return encryptedMessage;
}

// Hàm giải mã Vigenere
char* decryptMessage(char* cs, char* key) {
    int csLength = strlen(cs);
    int keyLength = strlen(key);
    char* decryptedMessage = new char[csLength + 1];

    int keyIndex = 0; // Chỉ số của key, chỉ tăng nếu gặp ký tự chữ
    for (int i = 0; i < csLength; i++) {
        if (cs[i] >= 'a' && cs[i] <= 'z') {
            int shift = key[keyIndex % keyLength] - 'a';
            decryptedMessage[i] = 'a' + (cs[i] - 'a' - shift + 26) % 26;
            keyIndex++; // Chỉ tăng khi xử lý chữ cái
        }
        else {
            decryptedMessage[i] = cs[i]; // Giữ nguyên khoảng trắng và ký tự khác
        }
    }
    decryptedMessage[csLength] = '\0';
    return decryptedMessage;
}

int main() {
    char ps[] = "truong dai hoc khoa hoc tu nhien tphcm";
    char key[] = "crypto";

    // Mã hóa
    char* cs = encryptMessage(ps, key);
    cout << "Encrypted message: " << cs << endl;

    // Giải mã
    char* decryptedMessage = decryptMessage(cs, key);
    cout << "Decrypted message: " << decryptedMessage << endl;

    // Giải phóng bộ nhớ
    delete[] cs;
    delete[] decryptedMessage;

    return 0;
}
