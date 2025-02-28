#include <iostream>
#include <bitset>
#include <iomanip>
#include <vector>

// Hàm ExtractBit: Trích xuất bit tại vị trí index từ chuỗi ký tự
bool ExtractBit(const char* str, unsigned int index) {
    unsigned int byteIndex = index / 8;
    unsigned int bitIndex = 7 - (index % 8); // Bit trong byte (từ trái sang phải)
    return (str[byteIndex] >> bitIndex) & 1;
}

// Hàm Replace: Thay đổi bit tại vị trí index trong chuỗi ký tự
void Replace(char* str, unsigned int index, bool val) {
    unsigned int byteIndex = index / 8;
    unsigned int bitIndex = 7 - (index % 8); // Bit trong byte (từ trái sang phải)
    if (val) {
        str[byteIndex] |= (1 << bitIndex); // Set bit thành 1
    }
    else {
        str[byteIndex] &= ~(1 << bitIndex); // Set bit thành 0
    }
}

// Bảng hoán vị PC-1 (64 bits -> 56 bits)
const int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Bảng hoán vị PC-2 (56 bits -> 48 bits)
const int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Lịch trình dịch vòng trái (số bit dịch cho mỗi vòng)
const int shiftSchedule[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

// Hàm dịch vòng trái (left shift)
void RotateLeft(char* data, int size, int shift) {
    for (int i = 0; i < shift; i++) {
        bool firstBit = ExtractBit(data, 0); // Lấy bit đầu tiên
        for (int j = 0; j < size - 1; j++) {
            bool nextBit = ExtractBit(data, j + 1); // Lấy bit tiếp theo
            Replace(data, j, nextBit); // Dịch bit sang trái
        }
        Replace(data, size - 1, firstBit); // Đưa bit đầu tiên vào cuối
    }
}

// Hàm tạo 16 subkeys
void GenerateSubKeys(const char* key64, char subkeys[16][6]) {
    // Bước 1: Áp dụng PC-1 để chọn 56 bit từ key 64-bit
    char key56[8] = { 0 }; // 56 bits (7 bytes)
    for (int i = 0; i < 56; i++) {
        bool bit = ExtractBit(key64, PC1[i] - 1 - (PC1[i] / 8));
        Replace(key56, i, bit);
    }

    // Bước 2: Chia 56 bit thành C0 và D0 (mỗi nửa 28 bit)
    char C[4] = { 0 }, D[4] = { 0 };
    for (int i = 0; i < 28; i++) {
        Replace(C, i, ExtractBit(key56, i));
        Replace(D, i, ExtractBit(key56, i + 28));
    }

    // Bước 3: Tạo 16 subkeys
    for (int round = 0; round < 16; round++) {
        // Dịch vòng trái C và D
        RotateLeft(C, 28, shiftSchedule[round]);
        RotateLeft(D, 28, shiftSchedule[round]);

        // Kết hợp C và D thành 56 bit
        char CD[7] = { 0 };
        for (int i = 0; i < 28; i++) {
            Replace(CD, i, ExtractBit(C, i));
            Replace(CD, i + 28, ExtractBit(D, i));
        }

        // Áp dụng PC-2 để tạo subkey 48-bit
        for (int i = 0; i < 48; i++) {
            bool bit = ExtractBit(CD, PC2[i] - 1);
            Replace(subkeys[round], i, bit);
        }
    }
}

int main() {
    // Ví dụ key 64-bit (8 ký tự ASCII)
    char key64[9] = "12345678"; // 8 ký tự ASCII (64 bits)
    char subkeys[16][6] = { 0 }; // 16 subkeys, mỗi subkey 48 bits (6 bytes)

    //Tạo 16 subkeys
    GenerateSubKeys(key64, subkeys);

    // In kết quả 16 subkeys dưới dạng hex
    std::cout << "16 Subkeys (48 bits each):" << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "Subkey " << i + 1 << ": ";
        for (int j = 0; j < 6; j++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)subkeys[i][j] << " ";
        }
        std::cout << std::dec << std::endl;
    }

    return 0;
}