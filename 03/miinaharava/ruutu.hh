// TIE-02200 opersk
// Emil Rekola 252822
// Projekti 1: Miinaharava

#ifndef RUUTU_HH
#define RUUTU_HH
#include <vector>
#include <iostream>

class Ruutu;
using Lauta = std::vector< std::vector< Ruutu > >;

class Ruutu
{
public:
    Ruutu(int x, int y, bool onkoMiina, Lauta*);

    void laskeViereiset();

    void tulosta(std::ostream&);

    bool onkoValmis();

    bool onkoLippu();

    void poistaLippu();

    int avaa();

    void lisaaLippu();

    bool onkoMiinaa();

    bool onkoAuki();

private:
    int x_;
    int y_;
    bool onkoMiina_;
    Lauta* lauta_;
    bool onkoLippu_;
    int montakoVieressa_;
    bool onkoAuki_;



};

#endif // RUUTU_HH
