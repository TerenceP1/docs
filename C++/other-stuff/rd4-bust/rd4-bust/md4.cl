// Dynamic stub
// #define padL ((length + 8) / 64 + 1)*64 but it will be just the number instead of this expression
// #define length <dynamic stub>

#define MD_WORD unsigned int
#define size_t unsigned long long


static MD_WORD MD_F(MD_WORD x, MD_WORD y, MD_WORD z) {
	return (x & y) | (~x & z);
}
static MD_WORD MD_G(MD_WORD x, MD_WORD y, MD_WORD z) {
	return (x & y) | (x & z) | (y & z);
}
static MD_WORD MD_H(MD_WORD x, MD_WORD y, MD_WORD z) {
	return x ^ y ^ z;
}

static MD_WORD ROT_WORD(MD_WORD x, int n) {
	return (x << n) | (x >> (32 - n));
}	

#define MD_RD1(a,b,c,d,k,s) a=ROT_WORD(a+MD_F(b,c,d)+X[k],s)
#define MD_RD2(a,b,c,d,k,s) a=ROT_WORD(a+MD_G(b,c,d)+X[k]+0x5A827999,s)
#define MD_RD3(a,b,c,d,k,s) a=ROT_WORD(a+MD_H(b,c,d)+X[k]+0x6ED9EBA1,s)

__kernel void md4(__global unsigned char *output) {
    // Generate input
    
	// Pad
	unsigned char padded_input[padL];
	for (size_t i = 0; i < length; i++) {
		padded_input[i] = input[i];
	}
	for (size_t i=length+1; i < ((length + 8) / 64 + 1) * 64; i++) {
		padded_input[i] = 0;
	}
	padded_input[length] = 0x80;
	((unsigned long long*) & ((padded_input)[((length + 8) / 64 + 1) * 64 - 8]))[0] = length*8L;
	// Init
	MD_WORD a = 0x67452301;
	MD_WORD b = 0xefcdab89;
	MD_WORD c = 0x98badcfe;
	MD_WORD d = 0x10325476;
	// Hash
	unsigned int N = ((length + 8) / 64 + 1) * 16;
	MD_WORD* M = (MD_WORD*)padded_input;
	for (int i = 0; i < N / 16; i++) {
		// Init
		MD_WORD* X = &(M[i * 16]);
		MD_WORD aa = a, bb = b, cc = c, dd = d;
        // Round 1
        MD_RD1(a, b, c, d, 0, 3);
        MD_RD1(d, a, b, c, 1, 7);
        MD_RD1(c, d, a, b, 2, 11);
        MD_RD1(b, c, d, a, 3, 19);

        MD_RD1(a, b, c, d, 4, 3);
        MD_RD1(d, a, b, c, 5, 7);
        MD_RD1(c, d, a, b, 6, 11);
        MD_RD1(b, c, d, a, 7, 19);

        MD_RD1(a, b, c, d, 8, 3);
        MD_RD1(d, a, b, c, 9, 7);
        MD_RD1(c, d, a, b, 10, 11);
        MD_RD1(b, c, d, a, 11, 19);

        MD_RD1(a, b, c, d, 12, 3);
        MD_RD1(d, a, b, c, 13, 7);
        MD_RD1(c, d, a, b, 14, 11);
        MD_RD1(b, c, d, a, 15, 19);

        // Round 2
        MD_RD2(a, b, c, d, 0, 3);
        MD_RD2(d, a, b, c, 4, 5);
        MD_RD2(c, d, a, b, 8, 9);
        MD_RD2(b, c, d, a, 12, 13);

        MD_RD2(a, b, c, d, 1, 3);
        MD_RD2(d, a, b, c, 5, 5);
        MD_RD2(c, d, a, b, 9, 9);
        MD_RD2(b, c, d, a, 13, 13);

        MD_RD2(a, b, c, d, 2, 3);
        MD_RD2(d, a, b, c, 6, 5);
        MD_RD2(c, d, a, b, 10, 9);
        MD_RD2(b, c, d, a, 14, 13);

        MD_RD2(a, b, c, d, 3, 3);
        MD_RD2(d, a, b, c, 7, 5);
        MD_RD2(c, d, a, b, 11, 9);
        MD_RD2(b, c, d, a, 15, 13);

        // Round 3
        MD_RD3(a, b, c, d, 0, 3);
        MD_RD3(d, a, b, c, 8, 9);
        MD_RD3(c, d, a, b, 4, 11);
        MD_RD3(b, c, d, a, 12, 15);

        MD_RD3(a, b, c, d, 2, 3);
        MD_RD3(d, a, b, c, 10, 9);
        MD_RD3(c, d, a, b, 6, 11);
        MD_RD3(b, c, d, a, 14, 15);

        MD_RD3(a, b, c, d, 1, 3);
        MD_RD3(d, a, b, c, 9, 9);
        MD_RD3(c, d, a, b, 5, 11);
        MD_RD3(b, c, d, a, 13, 15);

        MD_RD3(a, b, c, d, 3, 3);
        MD_RD3(d, a, b, c, 11, 9);
        MD_RD3(c, d, a, b, 7, 11);
        MD_RD3(b, c, d, a, 15, 15);
		// Final
		a += aa;
		b += bb;
		c += cc;
		d += dd;
	}
	// Output
	MD_WORD* out = (MD_WORD*)output;
	out[0] = a;
	out[1] = b;
	out[2] = c;
	out[3] = d;
}