#include "array_operations.hh"
#include <iostream>

int suurin_v1(int *alkio_ptr, int koko)
{
    int suurin = *alkio_ptr;
    int* taulukko_ptr = alkio_ptr;

    while (taulukko_ptr < alkio_ptr + koko) {
        if (*taulukko_ptr > suurin) {
            suurin = *taulukko_ptr;
        }
        ++taulukko_ptr;
    }
    return suurin;
}

int suurin_v2(int *alkio_ptr, int *loppu_ptr)
{
    int suurin = *alkio_ptr;
    int* taulukko_ptr = alkio_ptr;

    while (taulukko_ptr != loppu_ptr) {
        if (*taulukko_ptr > suurin) {
            suurin = *taulukko_ptr;
        }
        ++taulukko_ptr;
    }
    return suurin;
}

void kopioi(int *alkio_ptr, int *loppu_ptr, int *kohde_ptr)
{
    int* taulukko_ptr = alkio_ptr;

    while (taulukko_ptr != loppu_ptr) {
        *kohde_ptr = *taulukko_ptr;
        ++taulukko_ptr;
        ++kohde_ptr;
    }
}

void kaanna_takaperin(int *vasen_ptr, int *oikea_ptr)
{
    int* vasen = vasen_ptr;
    int* oikea = oikea_ptr - 1;

    while (vasen < oikea) {
        int vaihto = *vasen;
        *vasen++ = *oikea;
        *oikea-- = vaihto;
    }
}
