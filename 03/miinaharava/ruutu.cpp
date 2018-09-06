// TIE-02200 opersk
// Emil Rekola 252822
// Projekti1: Miinaharava

#include "ruutu.hh"
#include <vector>
#include <iostream>

// Alustetaan jokainen ruutu pelin aloitusta varten.
Ruutu::Ruutu(int x, int y, bool onkoMiina, Lauta* lauta):
    x_(x), y_(y), onkoMiina_(onkoMiina), lauta_(lauta)
{
    onkoLippu_ = false;
    onkoAuki_ = false;
    montakoVieressa_ = 0;
}

// Käy for-loopilla läpi halutun ruudun ympärillä olevat ruudut ja tarkistaa löytyykö niistä
// miinoja ja tallentaa miinojen määrän muuttujaan "montakoVieressä_".
void Ruutu::laskeViereiset() {
    for (int y = y_ - 1; y <=  y_ + 1; y++) {
        if (y >= 0 && 5 >= y) {

            for (int x = x_ - 1; x <= x_ + 1; x++) {
                if (x >= 0 && 5 >= x) {

                    if (lauta_->at(y).at(x).onkoMiinaa() && (y != y_ || x != x_)) {
                        montakoVieressa_++;
                    }
                }
            }
        }
    }
}

// Asettaa viitattuun muuttjaan 'virta' kyseiselle ruudulle kuuluvan merkin. "." kun ruutu on kiinni, "*" kun
// ruudussa on miina, "P" kun ruutuun on asetettu lippu tai numeron joka kertoo ympärillä olevien
// miinojen määrän, jos ruudussa ei ole miinaa ja ruutu avataan.
void Ruutu::tulosta(std::ostream& virta) {
    if (onkoLippu_) {
        virta << "P";
    }

    else {
        if (onkoAuki_) {
            if (onkoMiina_) {
                virta << "*";
            }

            else {
                virta << montakoVieressa_;
            }
        }

        else {
            virta << ".";
        }
    }
}

// Käy läpi kentän ja tarkistaa onko jokainen miina liputettu ja onko lippuja muualla kuin miinojen kohdalla.
// Jos lippuja on muualla kuin miinojen kohdalla, peli jatkuu. Samoin myös jos kaikkia miinoja ei ole liputettu.
// Palautaa false, jos peli vielä kesken ja true, jos peli on ohi.
bool Ruutu::onkoValmis() {
    if ((onkoMiina_ && not onkoLippu_) || (not onkoMiina_ && onkoLippu_)) {
        return false;
    }

    else {
        return true;
    }
}

// Tarkastaa halutun ruudun ja palauttaa tiedon onko ruudussa lippua.
bool Ruutu::onkoLippu() {
    if (onkoLippu_) {
        return true;
    }

    else {
        return false;
    }
}

// Poistaa halutusta ruudusta lipun.
void Ruutu::poistaLippu() {
    onkoLippu_ = false;
}

// Avaa halutun ruudun. Metodi tarkistaa ensin onko ruutu jo avattu, jonka jälkeen tarkistaa onko ruudussa miinaa.
// Jos ruudussa ei ole miinaa metodi tarkistaa onko viereisissä ruuduissa miinaa ja jos ei ole, avaa myös viereiset
// ruudut ja jatkaa tätä kunnes vieressä ei ole ruutua, jonka ympäriltä ei löydy miinaa.
int Ruutu::avaa() {
    if (not onkoAuki_) {
        onkoAuki_ = true;

        if (onkoMiina_) {
            return false;
        }
        else {
            if (montakoVieressa_ == 0) {
                for (int y = y_ - 1; y <=  y_ + 1; y++) {
                    if (y >= 0 && 5 >= y) {

                        for (int x = x_ - 1; x <= x_ + 1; x++) {
                            if (x >= 0 && 5 >= x) {

                                if (not lauta_->at(y).at(x).onkoAuki() && ( y != y_ || x != x_)) {
                                    lauta_->at(y).at(x).avaa();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

// Lisää haluttuun ruutuun lipun ja estää avattuun ruutuun lipun asettamisen.
void Ruutu::lisaaLippu() {
    if (onkoAuki_) {
        onkoLippu_ = false;
    }

    else {
        onkoLippu_ = true;
    }
}

// Tarkastaa löytyykö ruudusta miinaa ja palauttaa tiedon.
bool Ruutu::onkoMiinaa() {
    if (onkoMiina_) {
        return true;
    }

    else {
        return false;
    }
}

// Tarkastaa onko ruutu jo auki ja palauttaa tiedon.
bool Ruutu::onkoAuki() {
    if (onkoAuki_) {
        return true;
    }

    else {
        return false;
    }
}
