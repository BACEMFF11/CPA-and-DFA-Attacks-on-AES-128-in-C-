#include "aes.h"
#include <string.h>

const uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
/*define the consatnts SBoxTable and SBoxTableInv*/

const uint8_t sboxtab [256] =   {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

const uint8_t invsbox[256] =    { 
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0; // Product
    uint8_t hi_bit_set;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        // If the least significant bit of b is set, XOR p with a
        if ((b & 1) == 1) {
            p ^= a;
        }

        // Check if the highest bit of a is set
        hi_bit_set = (a & 0x80);

        // Left shift a and discard the high bit
        a <<= 1;

        // If the high bit was set, XOR a with 0x1b (irreducible polynomial)
        if (hi_bit_set==0x80) {
            a ^= 0x1b;
        }

        // Right shift b and discard the low bit
        b >>= 1;
    }

    return p;
}
void SubBytes ( uint8_t state [ STATE_ROW_SIZE ][ STATE_COL_SIZE ]){//used to generate a new state using the S table 
    for (int i = 0; i < STATE_ROW_SIZE; i++)
    {
        for (int j = 0; j < STATE_COL_SIZE; j++)
        {   //for each byte in the state
            state[i][j]=sboxtab[state[i][j]];//replace each byte in the state with the corresponding byte from the SBoxTable
        }
        
    }
}
void MCMatrixColumnProduct ( uint8_t colonne [ STATE_COL_SIZE ]) {
    uint8_t temp[STATE_COL_SIZE];  // Temporary storage for the original column
    for (int i = 0; i < STATE_COL_SIZE; i++) {
        temp[i] = colonne[i];  // Copy the column values
    }

    // Perform the MixColumns transformation using the fixed matrix
    colonne[0] = gmul(temp[0], 2) ^ gmul(temp[1], 3) ^ temp[2] ^ temp[3];
    colonne[1] = temp[0] ^ gmul(temp[1], 2) ^ gmul(temp[2], 3) ^ temp[3];
    colonne[2] = temp[0] ^ temp[1] ^ gmul(temp[2], 2) ^ gmul(temp[3], 3);
    colonne[3] = gmul(temp[0], 3) ^ temp[1] ^ temp[2] ^ gmul(temp[3], 2);
}
void KeyGen ( uint8_t roundkeys [ROUND_COUNT+1][ STATE_ROW_SIZE ][ STATE_COL_SIZE ], uint8_t master_key [STATE_ROW_SIZE ][ STATE_COL_SIZE ]) {
    //used to  generate all round keys, store them in an array of size round_count+1, each elemnt is a 4*4 matrix
    memcpy(roundkeys[0],master_key,sizeof(uint8_t) * STATE_ROW_SIZE * STATE_COL_SIZE);//copy the first round key which is the master key
    for (int round = 1; round <= ROUND_COUNT; round++)
    {
        ColumnFill(roundkeys,round);//fill the first column of each round key
        OtherColumnsFill(roundkeys,round);//fill the other 3 columns of each round key
    }
}
void AESEncrypt(uint8_t ciphertext[DATA_SIZE], uint8_t plaintext[DATA_SIZE], uint8_t key[DATA_SIZE]) {
    uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]; // State matrix which is  4x4 bytes
    uint8_t roundkeys[ROUND_COUNT + 1][STATE_ROW_SIZE][STATE_COL_SIZE]; // Round keys, which is a 3D array 
    //because we will have many keys, each key will be in a matrix 4*4
    uint8_t roundkey[STATE_ROW_SIZE][STATE_COL_SIZE];  // Current round key


    // Step 1: Convert plaintext to state matrix and convert key to key matrix
    MessageToState(state, plaintext);
    MessageToState(roundkey, key);


    // Step 2: Generate all round keys from the encryption key
    KeyGen(roundkeys,roundkey);

    // Step 3: Add the initial round key
    AddRoundKey(state, roundkeys[0]);
    
    SubBytes(state);                 // Replace each byte using the S-Box
    ShiftRows(state);                // Shift rows of the state matrix
    MixColumns(state);               // Mix the columns        
    GetRoundKey(roundkey, roundkeys, 1);  // Get the round key for this round
    AddRoundKey(state, roundkey);    // XOR state with the round key

    // Step 4: Perform 9 main rounds
    for (int round = 2; round < ROUND_COUNT; round++) {
        SubBytes(state);                 // Replace each byte using the S-Box
        ShiftRows(state);                // Shift rows of the state matrix
        MixColumns(state);               // Mix the columns
        GetRoundKey(roundkey, roundkeys, round);  // Get the round key for this round
        AddRoundKey(state, roundkey);    // XOR state with the round key
    }

    // Step 5: Perform the final round (no MixColumns)
    SubBytes(state);
    ShiftRows(state);
    GetRoundKey(roundkey, roundkeys, ROUND_COUNT);  // Get the final round key
    AddRoundKey(state, roundkey);

    // Step 6: Convert state matrix back to ciphertext
    StateToMessage(ciphertext, state);
}

void AddRoundKey ( uint8_t state [ STATE_ROW_SIZE ][ STATE_COL_SIZE ], uint8_t roundkey [STATE_ROW_SIZE ][ STATE_COL_SIZE ]) {

    for (int i = 0; i < STATE_ROW_SIZE; i++)
    {
        for (int j = 0; j < STATE_COL_SIZE; j++)
        {   //for each byte in the state
            state[i][j]=state[i][j]^roundkey[i][j];//XOR each byte in the state with the corresponding round key
        }
        
    }
    

}


void ShiftRows ( uint8_t state [ STATE_ROW_SIZE ][ STATE_COL_SIZE ]) {//we shift rows, row0 = no change, row1=1shift to left,row2=2shift to left,row3=3shift to left

    uint8_t aux;

    //shift row 1 by 1 to left
    aux = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = aux;

    //shift row 2 by 2 to left
    aux=state[2][0];
    state[2][0]=state[2][2];
    state[2][2]=aux;
    aux=state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = aux;

    //shift row 3 by 3 to left
    aux = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = aux;
}
void MixColumns(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]) {
    uint8_t column[STATE_ROW_SIZE]; // Temporary array to store a column

    for (int col = 0; col < STATE_COL_SIZE; col++) {
        // Extract the column
        for (int row = 0; row < STATE_ROW_SIZE; row++) {
            column[row] = state[row][col];
        }

        // Apply MixColumns transformation to the column
        MCMatrixColumnProduct(column);

        // Write the transformed column back into the state
        for (int row = 0; row < STATE_ROW_SIZE; row++) {
            state[row][col] = column[row];
        }
    }
}




void ColumnFill ( uint8_t roundkeys [][ STATE_ROW_SIZE ][ STATE_COL_SIZE ] , int round ){

    uint8_t aux[STATE_ROW_SIZE];//will store the current rotated last column of each previous roundkey

    //rotate the column
    aux[0]=roundkeys[round-1][1][STATE_COL_SIZE-1];
    aux[1]=roundkeys[round-1][2][STATE_COL_SIZE-1];
    aux[2]=roundkeys[round-1][3][STATE_COL_SIZE-1];
    aux[3]=roundkeys[round-1][0][STATE_COL_SIZE-1];

    //apply SubBytes, the function is different from the SubBytes we defined before becasue it takes a matrix as an arguemnt , this one will be applied on a single column
    for (int i = 0; i < STATE_ROW_SIZE; i++)
    {
        aux[i]=sboxtab[aux[i]];
    }
    
    //xor the column with the first column of the previous round key and the round constant
    //we need to xor only the first byte with the round constant
    aux[0]=aux[0]^rcon[round-1];
    for (int i = 0; i < STATE_ROW_SIZE; i++)
    {
                roundkeys[round][i][0] = roundkeys[round - 1][i][0] ^ aux[i];

    }
}

void OtherColumnsFill ( uint8_t roundkeys [][ STATE_ROW_SIZE ][ STATE_COL_SIZE ], int round ){

    for (int col = 1; col < STATE_COL_SIZE; col++)//for each column except the first one , since we already filled it with ColumnFill
    {
        for (int row = 0; row < STATE_ROW_SIZE; row++)//for each element of this col
        {
            roundkeys[round][row][col]=roundkeys[round][row][col-1]^roundkeys[round-1][row][col];
        }
    }
}

void GetRoundKey(uint8_t roundkey[STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t roundkeys[][STATE_ROW_SIZE][STATE_COL_SIZE], int round) {
    // Copy the specific round key into the output roundkey matrix
    memcpy(roundkey, roundkeys[round], sizeof(uint8_t) * STATE_ROW_SIZE * STATE_COL_SIZE);
}

void MessageToState(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t message[DATA_SIZE]) {
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COL_SIZE; j++) {
            state[i][j] = message[i + 4 * j]; // Rearrange bytes into a column-major order
        }
    }
}
void StateToMessage(uint8_t message[DATA_SIZE], uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]) {
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COL_SIZE; j++) {
            message[i + 4 * j] = state[i][j];
        }
    }
}