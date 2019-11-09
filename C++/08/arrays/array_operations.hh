#ifndef ARRAY_OPERATIONS_HH
#define ARRAY_OPERATIONS_HH
/*
 * Palauttaa taulukon suurimman alkion.
 * int* alkioptr: pointteri ensimmäiseen tutkittavaan taulukon alkioon
 * int koko: tutkittavien alkioiden lukumäärä
 * paluuarvo: taulukon suurin alkio
 */
int suurin_v1(int* alkio_ptr, int koko);

/*
 * Palauttaa taulukon suurimman alkion.
 * int* alkioptr: pointteri ensimmäiseen tutkittavaan taulukon alkioon
 * int* loppuptr: pointteri taulukon viimeistä seuraavaan muistiosoitteeseen
 * paluuarvo: taulukon suurin alkio
 */
int suurin_v2(int* alkio_ptr, int* loppu_ptr);

/* Kopioi taulukon sisältö toiseen taulukkoon
 * int* alkioptr: pointteri ensimmäiseen kopioitavaan taulukon alkioon
 * int* loppuptr: pointteri kopioitavan taulukon viimeistä seuraavaan muistiosoitteeseen
 * int* kohdeptr: pointteri taulukon alkuun johon kopio tehdään
 */
void kopioi(int* alkio_ptr, int* loppu_ptr, int* kohde_ptr);


/* Kääntää taulukon osan alkiot takaperin
 * int* vasenptr: pointteri käännettävän osan ensimmäiseen alkioon
 * int* oikeaptr: pointteri käännettävän osan viimeistä seuraavaan muistiosoitteeseen
 */
void kaanna_takaperin(int* vasen_ptr, int* oikea_ptr);

#endif
