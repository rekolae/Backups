// Huomaa, ei tarvetta using namespace std:lle, koska tässä
// tiedostossa ei käytetä mitään C++:n valmiskirjastoja.

double yhteen (double vasen, double oikea) {
    return vasen + oikea;
}


double vahennys (double vasen, double oikea) {
    return vasen - oikea;
}


double kerto (double vasen, double oikea) {
    return vasen * oikea;
}


double jako (double vasen, double oikea) {
    return vasen / oikea;
}

double potenssi (double vasen, double oikea) {
    double exp = 1.0;
    for (int i = 1; i <= oikea; i++) {
        exp *= vasen;
    }
    return exp;
}
