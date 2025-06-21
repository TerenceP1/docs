
typedef unsigned int ULL, *PULL; // Quickly modified to fit 32 bit

#define stack_l 10
#define tl 1024
// stack_l is appended dynamically before compilation

typedef struct
{
    ULL root, length, offset, jSz;
    int state = 0;
} stack_elem;

void NTT(PULL arr, ULL length, ULL prm, ULL root)
{
    // Do NTT of arr
    // Prime is chosen to avoid overflow
    int stackL = 1;
    stack_elem stack[stack_l];
    stack[0].root = root;
    stack[0].length = length;
    stack[0].offset = 0;
    stack[0].jSz = 1;
    ULL tmp[tl];
    // Recursion not allowed on GPU so manual stack
    while (stackL > 0)
    {
        stack_elem current = stack[stackL - 1];
        switch (current.state)
        {
        case 0:
            // Odds recursive call
            stack[stackL - 1].state++;
            if (current.length == 2)
                break;
            stack[stackL].root = ((unsigned long long)current.root * (unsigned long long)current.root) % (unsigned long long)prm;
            stack[stackL].length = current.length >> 1;
            stack[stackL].jSz = current.jSz << 1;
            stack[stackL].offset = current.offset;
            stackL++;
            break;
        case 1:
            // Evens recursive call
            stack[stackL - 1].state++;
            if (current.length == 2)
                break;
            stack[stackL].root = ((unsigned long long)current.root * (unsigned long long)current.root) % (unsigned long long)prm;
            stack[stackL].length = current.length >> 1;
            stack[stackL].jSz = current.jSz << 1;
            stack[stackL].offset = current.offset + current.jSz;
            stackL++;
            break;
        case 2:
            // Put odds and evens together
            // current.state = 0;
            ULL twiddle = 1;
            int eTerm = current.offset + current.jSz * current.length;
            ULL djSz = current.jSz << 1; // jSz * 2
            int ind = 0;
            for (int i = current.offset; i < eTerm; i += djSz)
            {
                arr[i + current.jSz] = ((unsigned long long)arr[i + current.jSz] * (unsigned long long)twiddle) % (unsigned long long)prm;
                tmp[ind] = ((unsigned long long)arr[i] + (unsigned long long)arr[i + current.jSz]) % (unsigned long long)prm;
                ind++;
                twiddle = ((unsigned long long)twiddle * (unsigned long long)current.root) % (unsigned long long)prm;
            }
            for (int i = current.offset; i < eTerm; i += djSz)
            {
                tmp[ind] = ((unsigned long long)arr[i] + (unsigned long long)prm - (unsigned long long)arr[i + current.jSz]) % (unsigned long long)prm;
                ind++;
            }
            ind = 0;
            for (int i = current.offset; i < eTerm; i += current.jSz)
            {
                arr[i] = tmp[ind];
                ind++;
            }
            stackL--;
            stack[stackL].state = 0;
        }
    }
}