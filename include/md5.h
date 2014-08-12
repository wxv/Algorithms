#ifndef MD5_H
#define MD5_H

#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <math.h>

/* Direct translation of OpenSSL's implementation. */

typedef unsigned int ui;

typedef union uwb
{
    ui w;
    unsigned char b[4];
} WBunion;

typedef ui Digest[4];


inline ui f0(ui abcd[])
{
    return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}
inline ui f1(ui abcd[])
{
    return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}
inline ui f2(ui abcd[])
{
    return  abcd[1] ^ abcd[2] ^ abcd[3];
}
inline ui f3(ui abcd[])
{
    return abcd[2] ^ (abcd[1] |~ abcd[3]);
}

typedef ui (*DgstFctn)(ui a[]);

inline ui *calcKs(ui *k)
{
    double s, pwr;
    int i;

    pwr = pow(2, 32);
    for (i=0; i<64; i++)
    {
        s = fabs(sin(1+i));
        k[i] = (ui)(s * pwr);
    }
    return k;
}

// Rotate v left
inline ui rol(ui v, int amt)
{
    ui msk1 = (1 << amt) - 1;
    return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

ui *md5(const char *msg, int mlen)
{
    static Digest h0 = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    static DgstFctn ff[] = {&f0, &f1, &f2, &f3};
    static int M[] = {1, 5, 3, 7};
    static int O[] = {0, 1, 5, 0};
    static int rot0[] = {7,12,17,22};
    static int rot1[] = {5, 9,14,20};
    static int rot2[] = {4,11,16,23};
    static int rot3[] = {6,10,15,21};
    static int *rots[] = {rot0, rot1, rot2, rot3};
    static ui kspace[64];
    static ui *k;

    static Digest h;
    Digest abcd;
    DgstFctn fctn;
    int m, o, g;
    ui f;
    int *rotn;
    union
    {
        ui       w[16];
        char     b[64];
    }mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k==NULL) k = calcKs(kspace);

    for (q=0; q<4; q++) h[q] = h0[q]; // Initialize
    {
        grps = 1 + (mlen+8)/64;
        msg2 = (unsigned char*)malloc(64*grps);
        memcpy(msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;
        q = mlen + 1;
        while (q < 64*grps){msg2[q] = 0; q++;}
        {
//            unsigned char t;
            WBunion u;
            u.w = 8*mlen;
//            t = u.b[0]; u.b[0] = u.b[3]; u.b[3] = t;
//            t = u.b[1]; u.b[1] = u.b[2]; u.b[2] = t;
            q -= 8;
            memcpy(msg2+q, &u.w, 4);
        }
    }

    for (grp=0; grp<grps; grp++)
    {
        memcpy(mm.b, msg2+os, 64);
        for(q=0;q<4;q++) abcd[q] = h[q];
        for (p = 0; p<4; p++)
        {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o= O[p];
            for (q=0; q<16; q++) {
                g = (m*q + o) % 16;
                f = abcd[1] + rol( abcd[0]+ fctn(abcd) + k[q+16*p] + mm.w[g], rotn[q%4]);

                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p=0; p<4; p++) h[p] += abcd[p];
        os += 64;
    }

    if(msg2)
        free(msg2);

    return h;
}

#endif // MD5_H

