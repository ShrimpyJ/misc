/* COSC 483: AES
 * Alexander Brock */

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <vector>

#define arrlen(arr) sizeof(arr) / sizeof(arr[0])

// For converting upper/lowercase hex ASCII letters to numbers
#define HEX_OFFSET_UPPER 55
#define HEX_OFFSET_LOWER 87

// For determining if a bit is set
#define BIT_SET(n, bit) (n >> bit) & 1

typedef unsigned char Byte;

// Rcon[] is 1-based, so the first entry is just a place holder
unsigned int RCON[] = {
           0x00000000,
           0x01000000, 0x02000000, 0x04000000, 0x08000000,
           0x10000000, 0x20000000, 0x40000000, 0x80000000,
           0x1B000000, 0x36000000, 0x6C000000, 0xD8000000,
           0xAB000000, 0x4D000000, 0x9A000000, 0x2F000000,
           0x5E000000, 0xBC000000, 0x63000000, 0xC6000000,
           0x97000000, 0x35000000, 0x6A000000, 0xD4000000,
           0xB3000000, 0x7D000000, 0xFA000000, 0xEF000000,
           0xC5000000, 0x91000000, 0x39000000, 0x72000000,
           0xE4000000, 0xD3000000, 0xBD000000, 0x61000000,
           0xC2000000, 0x9F000000, 0x25000000, 0x4A000000,
           0x94000000, 0x33000000, 0x66000000, 0xCC000000,
           0x83000000, 0x1D000000, 0x3A000000, 0x74000000,
           0xE8000000, 0xCB000000, 0x8D000000};

Byte SBOX[16][16] = {
    { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 },
    { 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 },
    { 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 },
    { 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 },
    { 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 },
    { 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf },
    { 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 },
    { 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 },
    { 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 },
    { 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb },
    { 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 },
    { 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 },
    { 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a },
    { 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e },
    { 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf },
    { 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }
  };


Byte INVSBOX[16][16] = {
    { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb } ,
    { 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb } ,
    { 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e } ,
    { 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25 } ,
    { 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92 } ,
    { 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84 } ,
    { 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06 } ,
    { 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b } ,
    { 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73 } ,
    { 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e } ,
    { 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b } ,
    { 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4 } ,
    { 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f } ,
    { 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef } ,
    { 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61 } ,
    { 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d }
  };

int hexCharToInt(char c)
{
  // Convert current byte from ASCII to integer
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - HEX_OFFSET_UPPER;
  if (c >= 'a' && c <= 'f') return c - HEX_OFFSET_LOWER;

  fprintf(stderr, "hexCharToInt() error: string has non-hex value '%c'\n", c);
  exit(1);
}

struct Info
{
  int Nb, Nr, Nk;

  Info(int nb, int nk)
  {
    Nb = nb;
    Nk = nk;
    Nr = nk + 6;
  }
};

// ByteString is a 1D array of bytes converted
// from an ASCII string of hex characters
struct ByteString
{
  std::vector<Byte> bytes;

  ByteString(char *str)
  {
    if (strlen(str) % 2 != 0){
      fprintf(stderr, "error: plaintext string '%s' must have length divisible by 2\n", str);
      exit(1);
    }

    for (int i = 0; i < strlen(str); i += 2){
      Byte b;
      b = 0;
      char byte[3];
      
      // Get current byte as ASCII string
      byte[0] = str[i];
      byte[1] = str[i+1];
      byte[2] = '\0';

      // Convert current byte from ASCII to integer
      int hexVal = hexCharToInt(byte[0]);
      if (hexVal == -1){
        fprintf(stderr, "error: plaintext string has non-hex value '%c' at index %d\n", byte[0], i);
        exit(1);
      }
      b += hexVal * 16;

      hexVal = hexCharToInt(byte[1]);
      if (hexVal == -1){
        fprintf(stderr, "error: plaintext string has non-hex value '%c' at index %d\n", byte[1], i);
        exit(1);
      }
      b += hexVal;

      bytes.push_back(b);
    }
  }
};

// State is a 2D array of bytes converted
// from a 1D array of bytes with
// s[r,c] = in[r + 4c]
struct State
{
  std::vector<std::vector<Byte> > bytes;
  int Nb;

  State(std::vector<Byte> in, int size)
  {
    Nb = size;
    for (int r = 0; r < 4; r++){
      std::vector<Byte> vb;
      for (int c = 0; c < size / 4; c++){
        Byte b = in[r + 4*c];
        vb.push_back(b);
      }
      bytes.push_back(vb);
    }
  }
};

// OutputBytes is a 1D array of bytes converted
// from a 2D State array with
// out[r + 4c] = s[r,c]
struct OutputBytes
{
  std::vector<Byte> bytes;

  OutputBytes(std::vector<std::vector<Byte> > s)
  {
    std::vector<Byte> out(4 * s[0].size());

    for (int r = 0; r < 4; r++){
      for (int c = 0; c < s[0].size(); c++){
        out[r + 4*c] = s[r][c];
      }
    }
    bytes = out;
  }
};
// Print a Byte as number with binary representation
std::ostream& operator << (std::ostream& os, Byte b)
{
  os << std::hex << (unsigned int) b;
  return os;
}

// Print a ByteString as series of bytes
std::ostream& operator << (std::ostream& os, ByteString in)
{
  for (int i = 0; i < 16; i++){
    os << in.bytes[i];
  }
  return os;
}

// Print a State as series of bytes
std::ostream& operator << (std::ostream& os, State s)
{
  for (int r = 0; r < 4; r++){
    for (int c = 0; c < s.Nb / 4; c++){
      os << std::setfill('0') << std::setw(2) << s.bytes[c][r];
    }
  }
  return os;
}

// Print a ByteString as series of bytes
std::ostream& operator << (std::ostream& os, OutputBytes out)
{
  for (int i = 0; i < out.bytes.size(); i++){
    os << std::setfill('0') << std::setw(2) << out.bytes[i];
  }
  return os;
}

// Print a vector of bytes as series of bytes
std::ostream& operator << (std::ostream& os, std::vector<Byte> bytes)
{
  for (int i = 0; i < bytes.size(); i++){
    os << std::setfill('0') << std::setw(2) << std::hex << bytes[i];
  }
  return os;
}

Byte ffAdd(Byte b1, Byte b2)
{
  return b1 ^ b2;
}

Byte xtime(Byte b)
{
  if (BIT_SET(b, 7)) return b << 1 ^ 0x1b;
  return b << 1;
}

Byte ffMultiply(Byte b1, Byte b2)
{
  Byte out = 0;
  for (int i = 0; i < 8; i++){
    if (BIT_SET(b2, i)) out = out ^ b1;
    b1 = xtime(b1);
  }
  return out;
}

// Substitute each byte in word with S-Box value
void subWord(std::vector<Byte> &word)
{
  for (int i = 0; i < word.size(); i++){
    // Convert byte to row,col
    int r = 0;
    int n = word[i];
    while (n > 16){
      n = n - 16;
      r++;
    }

    int c = 0;
    while (n > 0){
      n--;
      c++;
    }
    word[i] = SBOX[r][c];
  }
}

// Perform cyclic permutation on input word
void rotWord(std::vector<Byte> &word)
{
  for (int i = 0; i < word.size()-1; i++){
    int tmp = word[i];
    int idx = i - 1;
    if (idx < 0) idx = word.size()-1;
    word[i] = word[idx];
    word[idx] = tmp;
  }
}

// Substitute each byte in word with inverse S-Box value
void invSubWord(std::vector<Byte> &word)
{
  for (int i = 0; i < word.size(); i++){
    // Convert byte to row,col
    int r = 0;
    int n = word[i];
    while (n > 16){
      n = n - 16;
      r++;
    }

    int c = 0;
    while (n > 0){
      n--;
      c++;
    }
    word[i] = INVSBOX[r][c];
  }
}

// Perform reverse cyclic permutation on input word
void invRotWord(std::vector<Byte> &word)
{
  std::vector<Byte> tmp(word.size());
  for (int i = 0; i < word.size(); i++){
    tmp[(i+1) % word.size()] = word[i];
  }
  word = tmp;
}

// Substitute each byte in State with S-Box value
void subBytes(State &s)
{
  for (int r = 0; r < 4; r++){
    std::vector<Byte> row;
    for (int c = 0; c < s.bytes[r].size(); c++){
      row.push_back(s.bytes[r][c]);
    }
    subWord(row);
    s.bytes[r] = row;
  }
}

// Rotate each word in the State i times where i=row
void shiftRows(State &s)
{
  for (int r = 0; r < 4; r++){
    std::vector<Byte> row;
    for (int c = 0; c < s.bytes[r].size(); c++){
      row.push_back(s.bytes[r][c]);
    }
    for (int i = 0; i < r; i++) rotWord(row);
    s.bytes[r] = row;
  }
}

// Operate on each column as a 4-term polynomial,
// multiply each modulo x^4+1 with fixed polynomial a(x)
void mixColumns(State &s)
{
  for (int c = 0; c < s.bytes[0].size(); c++){
    std::vector<Byte> col;
    for (int r = 0; r < 4; r++) col.push_back(s.bytes[r][c]);

    s.bytes[0][c] = ffMultiply(0x02, col[0]) ^ ffMultiply(0x03, col[1]) ^ col[2] ^ col[3];
    s.bytes[1][c] = col[0] ^ ffMultiply(0x02, col[1]) ^ ffMultiply(0x03, col[2]) ^ col[3];
    s.bytes[2][c] = col[0] ^ col[1] ^ ffMultiply(0x02, col[2]) ^ ffMultiply(0x3, col[3]);
    s.bytes[3][c] = ffMultiply(0x03, col[0]) ^ col[1] ^ col[2] ^ ffMultiply(0x02, col[3]);
  }
}

// XOR each column of the State with appropriate word of key schedule
void addRoundKey(State &s, std::vector<std::vector<Byte> > w, int Nb, int round)
{
  int l = round * Nb;
  for (int c = 0; c < s.bytes[0].size(); c++){
    for (int r = 0; r < 4; r++) s.bytes[r][c] = s.bytes[r][c] ^ w[l+c][r];
  }
}

OutputBytes cipher(ByteString in, std::vector<std::vector<Byte> > keySchedule, Info info)
{
  using namespace std;
  State state(in.bytes, in.bytes.size());

  int Nb = info.Nb;
  int Nk = info.Nk;
  int Nr = info.Nr;

  addRoundKey(state, keySchedule, Nb, 0);

  for (int round = 1; round < Nr; round++){
    printf("round[%2d].start     ", round); cout << state << endl;

    subBytes(state);
    printf("round[%2d].s_box     ", round); cout << state << endl;

    shiftRows(state);
    printf("round[%2d].s_row     ", round); cout << state << endl;

    mixColumns(state);
    printf("round[%2d].m_col     ", round); cout << state << endl;

    addRoundKey(state, keySchedule, Nb, round);
    printf("round[%2d].k_sch     ", round);
    int l = round * Nb;
    for (int i = l; i < l+Nb; i++) cout << keySchedule[i];
    cout << endl;
  }

  printf("round[%2d].start     ", Nr); cout << state << endl;

  subBytes(state);
  printf("round[%2d].s_box     ", Nr); cout << state << endl;

  shiftRows(state);
  printf("round[%2d].s_row     ", Nr); cout << state << endl;

  addRoundKey(state, keySchedule, Nb, Nr);
  printf("round[%2d].k_sch     ", Nr);
  int l = Nr * Nb;
  for (int i = l; i < l+Nb; i++) cout << keySchedule[i];
  cout << endl;

  OutputBytes out(state.bytes);
  printf("round[%2d].output    ", Nr); cout << out << endl;

  return out;
}

char intToHexChar(int n)
{
  if (n < 0 || n > 15){
    fprintf(stderr, "intToHexChar() error: integer %d must be value 0-15\n", n);
    exit(1);
  }
  if (n >= 0 && n <= 9){
    return n + '0';
  }
  return n + HEX_OFFSET_LOWER;
}

// Substitute each byte in State with S-Box value
void invSubBytes(State &s)
{
  for (int r = 0; r < 4; r++){
    std::vector<Byte> row;
    for (int c = 0; c < s.bytes[r].size(); c++){
      row.push_back(s.bytes[r][c]);
    }
    invSubWord(row);
    s.bytes[r] = row;
  }
}

// Rotate each word in the State i times where i=row
void invShiftRows(State &s)
{
  for (int r = 0; r < 4; r++){
    std::vector<Byte> row;
    for (int c = 0; c < s.bytes[r].size(); c++){
      row.push_back(s.bytes[r][c]);
    }
    for (int i = 0; i < r; i++) invRotWord(row);
    s.bytes[r] = row;
  }
}

// Operate on each column as a 4-term polynomial,
// multiply each modulo x^4+1 with fixed polynomial a(x)
void invMixColumns(State &s)
{
  for (int c = 0; c < s.bytes[0].size(); c++){
    std::vector<Byte> col;
    for (int r = 0; r < 4; r++) col.push_back(s.bytes[r][c]);

    s.bytes[0][c] = ffMultiply(0x0e, col[0]) ^ ffMultiply(0x0b, col[1]) ^
                    ffMultiply(0x0d, col[2]) ^ ffMultiply(0x09, col[3]);
    s.bytes[1][c] = ffMultiply(0x09, col[0]) ^ ffMultiply(0x0e, col[1]) ^
                    ffMultiply(0x0b, col[2]) ^ ffMultiply(0x0d, col[3]);
    s.bytes[2][c] = ffMultiply(0x0d, col[0]) ^ ffMultiply(0x09, col[1]) ^
                    ffMultiply(0x0e, col[2]) ^ ffMultiply(0x0b, col[3]);
    s.bytes[3][c] = ffMultiply(0x0b, col[0]) ^ ffMultiply(0x0d, col[1]) ^
                    ffMultiply(0x09, col[2]) ^ ffMultiply(0x0e, col[3]);
  }
}

OutputBytes invCipher(ByteString in, std::vector<std::vector<Byte> > keySchedule, Info info)
{
  using namespace std;
  State state(in.bytes, in.bytes.size());

  int Nb = info.Nb;
  int Nk = info.Nk;
  int Nr = info.Nr;

  addRoundKey(state, keySchedule, Nb, Nr);

  int index = 1;
  for (int round = Nr-1; round > 0; round--){
    printf("round[%2d].istart    ", index); cout << state << endl;

    invShiftRows(state);
    printf("round[%2d].is_row    ", index); cout << state << endl;

    invSubBytes(state);
    printf("round[%2d].is_box    ", index); cout << state << endl;

    printf("round[%2d].ik_sch    ", index);
    int l = round * Nb;
    for (int i = l; i < l+Nb; i++) cout << keySchedule[i];
    cout << endl;

    addRoundKey(state, keySchedule, Nb, round);
    printf("round[%2d].ik_add    ", index); cout << state << endl;

    invMixColumns(state);

    index++;
  }

  printf("round[%2d].istart    ", Nr); cout << state << endl;

  invShiftRows(state);
  printf("round[%2d].is_row    ", Nr); cout << state << endl;

  invSubBytes(state);
  printf("round[%2d].is_box    ", Nr); cout << state << endl;

  addRoundKey(state, keySchedule, Nb, 0);
  printf("round[%2d].ik_sch    ", Nr);
  int l = 0 * Nb;
  for (int i = l; i < l+Nb; i++) cout << keySchedule[i];
  cout << endl;

  OutputBytes out(state.bytes);
  printf("round[%2d].ioutput   ", Nr); cout << out;
  printf("\n");

  return out;
}

// Perform XOR on two byte strings
std::vector<Byte> XOR(std::vector<Byte> b1, std::vector<Byte> b2)
{
  std::vector<Byte> out;
  for (int i = 0; i < b1.size(); i++){
    out.push_back(b1[i] ^ b2[i]);
  }
  return out;
}

std::vector<Byte> intToBytes(unsigned int n)
{
  std::vector<Byte> out;
  out.push_back((n = n / 0x01000000));
  out.push_back((n = n / 0x00010000));
  out.push_back((n = n / 0x00000100));
  out.push_back((n = n / 0x00000001));
  return out;
}

std::vector<std::vector<Byte> > expandKey(char key[], int Nb)
{
  int Nk = strlen(key) / 8;
  if (Nk != 4 && Nk != 6 && Nk != 8){
    fprintf(stderr, "error: key length must be 32, 48, or 64 characters (currently %d)\n", strlen(key));
    exit(1);
  }

  int Nr = Nk + 6;

  ByteString keyByte(key);

  std::vector<std::vector<Byte> > words(Nb * (Nr+1));
  char wordArr[Nb * (Nr + 1)][9];

  // Split key into 4-byte words
  for (int i = 0; i < strlen(key); i += 8){
    char wordStr[9];
    memcpy(wordStr, key + i, 8);
    ByteString wordByte(wordStr);
    strcpy(wordArr[i/8], wordStr);
    words[i/8] = wordByte.bytes;
  }

  char keyEx[strlen(key)+2];
  memset(keyEx, 0, strlen(key)+2);

  // The first Nk words are identical to the Cipher Key
  for (int i = 0; i < Nk; i++) strcat(keyEx, wordArr[i]);

  // The remaining words are calculated via XOR and transforms
  for (int i = Nk; i < Nb * (Nr + 1); i++){
    std::vector<Byte> temp = words[i-1];
    if (i % Nk == 0){
      rotWord(temp);
      subWord(temp);
      temp = XOR(temp, intToBytes(RCON[i/Nk]));
    }
    else if (Nk > 6 && i % Nk == 4){
      subWord(temp);
    }
    words[i] = XOR(words[i-Nk], temp);
  }

  return words;
}

void start(char str[], char key[])
{
  printf("%-19s %s\n", "PLAINTEXT:", str);
  printf("%-19s %s\n", "KEY:", key);
  printf("\nCIPHER (ENCRYPT):\n");

  // Get length info
  int Nb = strlen(str) / 8;
  int Nk = strlen(key) / 8;
  int Nr = Nk + 6;
  Info info(Nb, Nk);

  // Convert input string to input array and key string to expanded schedule
  ByteString in(str);
  std::vector<std::vector<Byte> > keySchedule = expandKey(key, Nb);

  // Cipher
  printf("round[ 0].input     %s\n", str);
  printf("round[ 0].k_sch     ");
  for (int i = 0; i < Nb; i++) std::cout << keySchedule[i];
  printf("\n");
  OutputBytes out = cipher(in, keySchedule, info);
  std::stringstream buffer;
  buffer << out;
  char output[buffer.str().length()];
  strcpy(output, buffer.str().c_str());

  // Inverse Cipher
  printf("\nINVERSE CIPHER (DECRYPT):\n");
  printf("round[ 0].iinput    %s\n", output);
  printf("round[ 0].ik_sch    ");
  for (int i = Nr*Nb; i < Nr*Nb + Nb; i++) std::cout << keySchedule[i];
  printf("\n");
  ByteString invIn(output);
  invCipher(invIn, keySchedule, info);
}

int main(int argc, char **argv)
{
}
