#include <vector>
#include <intrin.h>
using namespace std;
extern "C" uint64_t add_carry(uint64_t a, uint64_t b, uint8_t* carry);
extern "C" uint64_t sub_carry(uint64_t a, uint64_t b, uint8_t* carry);

// Uses 2-s complement representation for negative numbers
// Uses NTT for multiplication (to be implemented)
class BigInt {
private:
	int len;
	unsigned int* data;
public:
	BigInt(int size) {
		len = size;
		data = new unsigned int[len];
	}
	
	~BigInt() {
		delete[] data;
	}

	BigInt operator+(BigInt a) {
		BigInt res(len);
		unsigned char carry = 0;
		for (int i = len-1; i >= 0; i--) {
			//res[i]
		}
	}
};