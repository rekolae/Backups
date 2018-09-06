#include <iostream>
#include <string>

const int MAX_ARVAUSKERTOJA = 10;

// Tulostaa tyhjiä rivejä ohjelman suorituksen alussa
void puhdista_naytto();

// Tarkastaa, ovatko kaikki kirjaimet arvattujen kirjainten listalla
bool onko_sana_jo_arvattu(std::string sala, std::string arvatut);

// Tulostaa merkkijonon käyttäen _-merkkiä arvaamattoman kirjaimen kohdalla
void tulosta_pelitilanne(std::string sala, std::string arvatut);


int main()
{
    std::string salainen_sana = "";
    std::cout << "Syota arvattava sana: ";
    getline(std::cin, salainen_sana);

    puhdista_naytto();

    std::string arvatut_kirjaimet = "";
    int arvauskertoja_kaytetty = 0;

    while (not onko_sana_jo_arvattu(salainen_sana, arvatut_kirjaimet)
              and arvauskertoja_kaytetty < MAX_ARVAUSKERTOJA)
    {

        std::cout << std::endl
             << "Pelitilanne: ";
        tulosta_pelitilanne(salainen_sana, arvatut_kirjaimet);

        if (arvatut_kirjaimet.size() > 0)
        {
            std::cout << "Olet kayttanyt " << arvauskertoja_kaytetty
                 << " arvausta!"
                 << std::endl
                 << "Olet arvannut kirjaimia: " << arvatut_kirjaimet
                 << std::endl;
        }

        std::string arvaus = "";
        std::cout << "Arvaa kirjain: ";
        getline(std::cin, arvaus);

        if (arvaus.size() != 1)
        {
            std::cout << "Mokasit: syota tasmalleen yksi kirjain!"
                 << std::endl;
            continue;
        }
        else if (arvatut_kirjaimet.find(arvaus) != std::string::npos)
        {

            std::cout << "Mokasit: olit jo arvannut merkin " << arvaus << "!"
                 << std::endl;
            continue;
        }

        arvatut_kirjaimet += arvaus;

        if (salainen_sana.find(arvaus) == std::string::npos)
        {
            std::cout << "Arvattu kirjain ei ole sanassa!" << std::endl;
        }

        ++arvauskertoja_kaytetty;
    }

    if (not onko_sana_jo_arvattu(salainen_sana, arvatut_kirjaimet))
    {
        std::cout << std::endl
             << "Arvauskerrat loppuivat kesken!"
             << std::endl;
    }
    else
    {
        std::cout << std::endl
             << "Arvasit oikein. Kaytit " << arvauskertoja_kaytetty
             << " arvausta!"
             << std::endl;
    }
}

void puhdista_naytto()
{
    // Puhdistetaan näyttö tulostamalla 100 tyhjää riviä.
    for (int i = 0; i < 100; ++i)
    {
        std::cout << std::endl;
    }
}


bool onko_sana_jo_arvattu(std::string sala, std::string arvatut)
{
    // Käydään läpi kaikki sala-merkkijonon merkit.
    for (std::string::size_type indeksi = 0; indeksi < sala.size(); ++indeksi)
    {
        // Jos vastaan tulee sala-merkkijonon merkki, joka ei ole
        // arvatuissa merkeissä, voidaan välittömästi päätellä,
        // että koko salaista sanaa ei ole vielä arvattu.
        if (arvatut.find(sala.at(indeksi)) == std::string::npos)
        {
            return false;
        }
    }

    // Kun koko salainen merkkijono on käyty läpi, ja joka ikinen
    // merkki löytyi merkkijonosta arvatut, täytyy olla niin,
    // että koko salainen sana on arvattu.
    return true;
}


void tulosta_pelitilanne(std::string sala, std::string arvatut)
{
    // Merkkijonon merkit voidaan käydä läpi myös for-silmukan
    // versiolla, joka muistuttaa Pythonin "for x in y"-rakennetta.
    // Tämä on vaihtoehto edellisessä funktiossa käytetylle
    // indeksi-muuttujan avulla tehdylle toteutukselle.
    for (char salamerkki: sala)
    {
        if (arvatut.find(salamerkki) == std::string::npos)
        {
            std::cout << "_";
        }
        else
        {
            std::cout << salamerkki;
        }
    }

    std::cout << std::endl;
}
