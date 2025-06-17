#include <gmp.h>
#include <iostream>
using namespace std;

int main(){
    mpf_t pi,pisq;
    mpf_init2(pi,256);
    mpf_init2(pisq,256);
    mpf_set_str(pi,"3.141592653589793238462643383279",10);
    mpf_mul(pisq,pi,pi);
    gmp_printf("Pi squared: %.Ff\n",pisq);
    mpf_clear(pisq);
    mpf_clear(pi);
    return 0;
}