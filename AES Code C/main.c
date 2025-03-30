#include <stdio.h>
#include <stdint.h>
#include "aes.h" // Include aes.h to access AESEncrypt

void printArray(uint8_t array[DATA_SIZE]) {
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("%02X ", array[i]);
    }
    printf("\n");
}

int main() {
    // Define the plaintext
    uint8_t plaintext[DATA_SIZE] = {
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xAA, 0xBB,
        0xCC, 0xDD, 0xEE, 0xFF
    };

    // Define the encryption key
    uint8_t key[DATA_SIZE] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0F
    };

    // Define an array to store the ciphertext
    uint8_t ciphertext[DATA_SIZE];

    // Encrypt the plaintext using AESEncrypt
    AESEncrypt(ciphertext, plaintext, key);

    // Print the ciphertext
    printf("Ciphertext:\n");
    printArray(ciphertext);

    return 0;
}
