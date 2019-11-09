#include "laskut.hh"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string LOPPUTERVEHDYS = "Kiitos ja näkemiin!";

// Apufunktio, joka jakaa merkkijonon osiksi erotinmerkkien kohdalta.
vector< string > split (const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// stringToDouble on apufunktio, jonka avulla merkkijonossa olevan
// reaaliluvun saa muutettua double-tyyppiseksi arvoksi
// laskutoimituksia varten. Funktion paluuarvo on true, jos parametri
// mjono oli esitti reaalilukua. Paluuarvo on false, jos mjono oli
// jollain tavoin virheellinen. Varsinainen muunnettu reaaliluku
// sijoitetaan viiteparametriin tulos. Funktion toteutuksessa on
// käytetty esimerkin vuoksi stringstreameja.
bool stringToDouble (const string& mjono, double& tulos);
string stringToUpper(string command);


struct Komento
{
    string merkkijono;
    vector<string>::size_type parametrien_lkm;
    bool lopetus;
    double (*toiminto) (double, double);
};

const vector<Komento> KOMENNOT = {
    {"+", 2, false, yhteen},
    {"-", 2, false, vahennys},
    {"*", 2, false, kerto},
    {"/", 2, false, jako},
    {"PLUS", 2, false, yhteen},
    {"MIINUS", 2, false, vahennys},
    {"KERTAA", 2, false, kerto},
    {"JAETTUNA", 2, false, jako},
    {"YHTEEN", 2, false, yhteen},
    {"VAHENNYS", 2, false, vahennys},
    {"KERTO", 2, false, kerto},
    {"JAKO", 2, false, jako},
    {"SUMMA", 2, false, yhteen},
    {"EROTUS", 2, false, vahennys},
    {"TULO", 2, false, kerto},
    {"OSAMAARA", 2, false, jako},
    {"SUMMAA", 2, false, yhteen},
    {"PLUSSAA", 2, false, yhteen},
    {"VAHENNA", 2, false, vahennys},
    {"MIINUSTA", 2, false, vahennys},
    {"KERRO", 2, false, kerto},
    {"JAA", 2, false, jako},
    {"LOPETA", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr},
    {"^", 2, false, potenssi},
    {"POTENSSI", 2, false, potenssi},
    {"EXP", 2, false, potenssi}
};


int main()
{

    // Määritellään tulostuksen tarkkuus kahteen desimaaliin
    cout.precision(2);
    cout << fixed;

    while (true) {
        cout << "laskin> ";

        string rivi = "";
        getline (cin, rivi);

        if (rivi.empty()) {
            // Tyhjän rivin syöttäminen keskeyttää käyttöliittymäsilmukan,
            // minkä seurauksena ohjelman suoritus tulee päättymään.
            cout << LOPPUTERVEHDYS << endl;
            break;
        }

        vector<string> palat = split (rivi, ' ', true);

        if (palat.size() == 0){
            continue;
        }

        string command = palat.at(0);
        command = stringToUpper(command);
        double left;
        double right;
        bool found = false;


        for (auto komento : KOMENNOT) {
            if (command == komento.merkkijono) {
                found = true;

                if (palat.size() != komento.parametrien_lkm + 1) {
                    cout << "Virhe: väärä määrä parametreja." << endl;
                }

                else if (komento.toiminto == nullptr) {
                    cout << LOPPUTERVEHDYS << endl;
                    exit(EXIT_SUCCESS);
                }

                else if ((not stringToDouble(palat.at(1), left)) || (not stringToDouble(palat.at(2), right))) {
                    cout << "Virhe: kaikki operandit eivät ole lukuja." << endl;
                }

                else {
                    cout << komento.toiminto(left, right) << endl;
                }
            }
        }

        if (not found) {
            cout << "Virhe: tuntematon komento." << endl;
        }
    }
}


string stringToUpper(string command)
{
    transform (command.begin(), command.end(), command.begin(), ::toupper);
    return command;
}

// Tämä funktio on esimerkki istringstreamin käytöstä.
// Periaatteessa merkkojonoja voi muuttaa doubleiksi myös
// string-kirjaston stod-funktiolla. Tässä vaiheessa koulutusta
// kaikkien virhetilanteiden havaitseminen stod-funktiota köytettäessä
// on kuitenkin monimutkaisempaa, kuin tässä funktiossa toteutettu
// bool-tyyppinen paluuarvo, jota voi tutkia funktion kutsukohdassa.
bool stringToDouble(const string& mjono, double& tulos)
{
    // Alustetaan istringstream-tyyppinen syötevirta merkkijonolla,
    // joka halutaan lukea läpi >>- tai getline-operaatioilla.
    istringstream syotevirta (mjono);

    double apu;

    // Luetaan syotevirrasta arvo muuttujaan normaalisti >>-operaattorilla.
    // istringstream-tyyppisiä virtoja voi käsitellä täsmälleen samoilla
    // operaatioilla kuin ciniä ja ifstream-tyyppisiä (tiedostot) virtoja.
    syotevirta >> apu;

    if (not syotevirta) {
        return false;
    }

    // ws on erikoisoperaatio, joka hyppää yli kaikki sanaerotinmerkit
    // (välilyönnit jne.) kunnes vastaan tulee jotain muuta.
    syotevirta >> ws;

    // Jos mjono-parametri oli oikein mutoiltu reaalilukua esittävä
    // merkkijono, sen perässä ei saa olla muuta kuin välilyönteja.
    // Eli koska edeltävä ">> ws"-operaatio heitti välilyönnit menemään,
    // tässä kohdassa syotevirrassa ei saa olla jäljellä mitään,
    // tai jos on, mjono oli virheellinen.  Yritetään lukea syötevirrasta
    // merkki. Jos lukeminen epäonnistuu siksi, että virrassa ei enää
    // ole mitään jäljellä, kaikki on kunnossa. Jos merkin lukeminen
    // onnistuu, se tarkoittaa, että mjonon perässä oli jotain ylimääräistä.

    syotevirta.get();

    if (syotevirta) {
        return false;
    } else {
        tulos = apu;
        return true;
    }
}

// Vanha tuttu split-funktion malliratkaisu.
vector< string > split(const string& s, const char delimiter, bool ignore_empty)
{
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string sana = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and sana.empty()))
        {
            result.push_back(sana);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
