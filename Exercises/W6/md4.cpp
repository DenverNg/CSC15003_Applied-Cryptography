#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

// Khai báo các hằng số ban đầu của MD4
const uint32_t H1_INIT = 0x67452301;
const uint32_t H2_INIT = 0xefcdab89;
const uint32_t H3_INIT = 0x98badcfe;
const uint32_t H4_INIT = 0x10325476;

// Các phép toán hỗ trợ
#define LEFT_ROTATE(x, n) ((x << n) | (x >> (32 - n)))

// Các vòng của thuật toán MD4
#define ROUND1(A, B, C, D, X, S) A += ((B & C) | (~B & D)) + X; A = LEFT_ROTATE(A, S);
#define ROUND2(A, B, C, D, X, S) A += ((B & C) | (B & D) | (C & D)) + X + 0x5a827999; A = LEFT_ROTATE(A, S);
#define ROUND3(A, B, C, D, X, S) A += (B ^ C ^ D) + X + 0x6ed9eba1; A = LEFT_ROTATE(A, S);

// Hàm in dữ liệu dưới dạng thập lục phân
void printHex(const string& label, const vector<uint8_t>& data) {
    cout << label << ": ";
    for (uint8_t byte : data) {
        cout << hex << setw(2) << setfill('0') << (int)byte;
    }
    cout << endl;
}

// Hàm MD4
vector<uint8_t> md4(const string& message) {
    cout << "Original Data: " << message << endl;

    vector<uint8_t> data(message.begin(), message.end());
    printHex("Data in Hex", data);

    uint64_t original_length = data.size() * 8;
    data.push_back(0x80);
    while ((data.size() % 64) != 56) data.push_back(0);

    for (int i = 0; i < 8; i++) data.push_back(original_length >> (i * 8));
    printHex("Data after Padding", data);

    uint32_t A = H1_INIT, B = H2_INIT, C = H3_INIT, D = H4_INIT;

    for (size_t i = 0; i < data.size(); i += 64) {
        uint32_t X[16];
        memcpy(X, &data[i], 64);

        uint32_t AA = A, BB = B, CC = C, DD = D;

        ROUND1(A, B, C, D, X[0], 3);  ROUND1(D, A, B, C, X[1], 7);
        ROUND1(C, D, A, B, X[2], 11); ROUND1(B, C, D, A, X[3], 19);
        ROUND1(A, B, C, D, X[4], 3);  ROUND1(D, A, B, C, X[5], 7);
        ROUND1(C, D, A, B, X[6], 11); ROUND1(B, C, D, A, X[7], 19);
        ROUND1(A, B, C, D, X[8], 3);  ROUND1(D, A, B, C, X[9], 7);
        ROUND1(C, D, A, B, X[10], 11); ROUND1(B, C, D, A, X[11], 19);
        ROUND1(A, B, C, D, X[12], 3); ROUND1(D, A, B, C, X[13], 7);
        ROUND1(C, D, A, B, X[14], 11); ROUND1(B, C, D, A, X[15], 19);

        ROUND2(A, B, C, D, X[0], 3);  ROUND2(D, A, B, C, X[4], 5);
        ROUND2(C, D, A, B, X[8], 9);  ROUND2(B, C, D, A, X[12], 13);
        ROUND2(A, B, C, D, X[1], 3);  ROUND2(D, A, B, C, X[5], 5);
        ROUND2(C, D, A, B, X[9], 9);  ROUND2(B, C, D, A, X[13], 13);
        ROUND2(A, B, C, D, X[2], 3);  ROUND2(D, A, B, C, X[6], 5);
        ROUND2(C, D, A, B, X[10], 9); ROUND2(B, C, D, A, X[14], 13);
        ROUND2(A, B, C, D, X[3], 3);  ROUND2(D, A, B, C, X[7], 5);
        ROUND2(C, D, A, B, X[11], 9); ROUND2(B, C, D, A, X[15], 13);

        ROUND3(A, B, C, D, X[0], 3);  ROUND3(D, A, B, C, X[8], 9);
        ROUND3(C, D, A, B, X[4], 11); ROUND3(B, C, D, A, X[12], 15);
        ROUND3(A, B, C, D, X[2], 3);  ROUND3(D, A, B, C, X[10], 9);
        ROUND3(C, D, A, B, X[6], 11); ROUND3(B, C, D, A, X[14], 15);
        ROUND3(A, B, C, D, X[1], 3);  ROUND3(D, A, B, C, X[9], 9);
        ROUND3(C, D, A, B, X[5], 11); ROUND3(B, C, D, A, X[13], 15);
        ROUND3(A, B, C, D, X[3], 3);  ROUND3(D, A, B, C, X[11], 9);
        ROUND3(C, D, A, B, X[7], 11); ROUND3(B, C, D, A, X[15], 15);

        A += AA; B += BB; C += CC; D += DD;
    }

    vector<uint8_t> hash(16);
    memcpy(&hash[0], &A, 4);
    memcpy(&hash[4], &B, 4);
    memcpy(&hash[8], &C, 4);
    memcpy(&hash[12], &D, 4);

    printHex("Final Hash", hash);
    return hash;
}

int main() {
    string m = "The quick brown fox jumps over the lazy dog";
    vector<uint8_t> hash = md4(m);
    return 0;
}
