#include <stdio.h>
#include <string.h>

// Hàm trích xuất bit từ một mảng byte
unsigned char ExtractBit(unsigned char* x, unsigned int idx) {
    int bytePos = (idx - 1) / 8;  // Xác định byte chứa bit
    int bitPos = 7 - ((idx - 1) % 8); // Vị trí bit trong byte
    return (x[bytePos] >> bitPos) & 1;
}

// Hàm thay thế bit trong một mảng byte
void ReplaceBit(unsigned char* output, unsigned int idx, unsigned char bit) {
    int bytePos = idx / 8;  // Xác định byte cần thay đổi
    int bitPos = 7 - (idx % 8); // Xác định vị trí bit trong byte
    if (bit)
        output[bytePos] |= (1 << bitPos); // Đặt bit thành 1
    else
        output[bytePos] &= ~(1 << bitPos); // Đặt bit thành 0
}

// Hàm in ra các bit của mảng byte
void PrintBits(unsigned char* data, int bitLength) {
    for (int i = 0; i < bitLength; i++) {
        int bit = (data[i / 8] >> (7 - (i % 8))) & 1;
        printf("%d", bit);
        if ((i + 1) % 8 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    unsigned char str[4] = "abc";  // Chuỗi "abc" (tự động có ký tự '\0' nếu khai báo 4 byte)
    
    printf("Original:     ");
    PrintBits(str, 24);  // Chuỗi "abc" có 3 byte (24 bit)

    // Thay đổi một số bit
    ReplaceBit(str, 0, 1);   // Đặt bit đầu tiên thành 1

    printf("Modified:     ");
    PrintBits(str, 24);

    return 0;
}
