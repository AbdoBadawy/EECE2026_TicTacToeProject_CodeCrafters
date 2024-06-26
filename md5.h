#ifndef MD5_H
#define MD5_H

typedef union {
    unsigned w;
    unsigned char b[4];
} MD5union;

typedef unsigned DigestArray[4];

unsigned func0(unsigned abcd[]);
unsigned func1(unsigned abcd[]);
unsigned func2(unsigned abcd[]);
unsigned func3(unsigned abcd[]);

typedef unsigned(*DgstFctn)(unsigned a[]);

unsigned *calctable(unsigned *k);
unsigned rol(unsigned r, short N);
unsigned* Algorithms_Hash_MD5(const char *msg, int mlen);
const char* GetMD5String(const char *msg, int mlen);

#endif // MD5_H

