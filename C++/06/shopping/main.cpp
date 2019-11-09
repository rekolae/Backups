// TIE-02200 opersk
// Emil Rekola 252822
// Projekti2: Shopping

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>
#include <set>


//Osa tietorakennetta, johon tuotteen nimi ja hinta tallennetaan. Jos tuote
//on out-of-stock asetetaan hinta = 0.0.
struct Product
{
    std::string name;
    double price;
};


//Järjestää struct tyyppiset muuttujat nimen mukaan ja palauttaa
//ne järjestyksessä.
bool compareByName(const Product& lhs, const Product& rhs)
{
    return lhs.name < rhs.name;
}


//Järjestää struct tyyppiset muuttujat hinnan mukaan ja palauttaa
//ne järjestyksessä.
bool compareByPrice(const Product& lhs, const Product& rhs)
{
    return lhs.price < rhs.price;
}


//Funktio saa parametrina string tyyppisen rivin, jonka funktio "pilkkoo",
//syöttää palat vectoriin. Paluuarvona on kyseinen vector.
std::vector< std::string > splitCommand(std::string line)
{
    std::string part = "";
    std::vector<std::string> parts;

    if (not line.find(" ")) {
        parts.push_back(line);
    }

    else {
        while (line.find(" ") != std::string::npos) {
            part = line.substr(0, line.find(" "));
            parts.push_back(part);
            line.erase(0, line.find(" ") + 1);
        }
        parts.push_back(line);
    }
    return parts;
}


//Funktio saa parametrina string tyyppisen rivin, joka on luettu tiedostosta
//jossa on tuotteiden tiedot. Tiedot "paloitellaa" tunnetun merkin kohdalta.
//Jos jokin paloista on tyhjä tai koostuu vain välilyönneistä, funktio tulostaa
//error viestin ja lopettaa ohjelman paluuarvoon exit_failure. Jos rivi on
//halutunlainen, tallennetaan palaset vectoriinja annetaan paluuarvona
//kyseinen vector.
std::vector< std::string > splitFile(std::string line)
{
    std::string part = "";
    std::vector< std::string > parts;

    while (line.find(";") != std::string::npos) {
        part = line.substr(0, line.find(";"));
        if (part == " " || part == "") {
            std::cout << "Error: the file has an erroneous line" << std::endl;
            exit(EXIT_FAILURE);
        }

        else {
            parts.push_back(part);
            line.erase(0, line.find(";") + 1);
        }
    }

    if ((line == " " || line == "")) {
        std::cout << "Error: the file has an erroneous line" << std::endl;
        exit(EXIT_FAILURE);
    }

    parts.push_back(line);
    return parts;
}


//Rakentaa tietokannan annetusta tiedostosta, funktio saa parametreina luetun
//tiedoston ja tietorakenteen mihin tiedot tallennetaan.
void buildDatabase(std::ifstream &readFile, std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase)
{
    std::string line = "";
    std::vector< std::string > parts;

    //Käy luetun tiedoston läpi rivi kerrallaan ja kutsuu funktiota splitFile
    //joka paloittelee rivin osiin.
    while (getline(readFile, line)) {
        parts = splitFile(line);

        //Tarkistaa että rivistä löytyi kaikki tarvittavat osat (ketju, kauppa,
        //nimi ja hinta). Jos ei löydy, tulostetaan errorviesti ja lopetetaan
        //ohjelman suoritus.
        if (parts.size() != 4) {
            std::cout << "Error: the file has an erroneous line" << std::endl;
            exit(EXIT_FAILURE);
        }

        Product product;

        //Annetaan eri osille nimet koodin helpompaa ymmärrystä varten.
        std::string chain = parts.at(0);
        std::string store = parts.at(1);
        std::string productName = parts.at(2);

        //Tuotteen ollessa out-of-stock asetetaan hinnaksi 0.0.
        if(parts.at(3) == "out-of-stock") {
            product = {productName, 0.0};
        }

        //Tarkistetaan että luetun rivin hinta-kentässä ei ole ole muita
        //arvoja kuin double.
        else {
            try {
                double value = std::stod(parts.at(3));
                product = {productName, value};
            }

            //Jos kentässä ollut arvo oli jotain muuta kuin double, heittää
            //ohjelma errorin kun sitä käännetään luvuksi. Tulostetaan error
            //viesti ja lopetetaan ohjelman suoritus.
            catch(std::exception) {
                std::cout << "Error: the file has an erroneous line" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        //Jos kauppaketjua ei löydy tietorakenteesta niin lisätään kauppaketju,
        //kaupan nimi ja tuote tietorakenteeseen.
        if(productDatabase.find(chain) != productDatabase.end()) {

            //Jos kauppaa ei löydy tietorakenteesta niin lisätään kaupan nimi
            //ja tuote tietorakenteeseen.
            if(productDatabase.at(chain).find(store) != productDatabase.at(chain).end()) {
                bool productFound = false;

                //Käydää loopilla kaupan kaikki tuotteet läpi.
                for(unsigned int x = 0; x < productDatabase.at(chain).at(store).size(); x++) {

                    //Jos kaupassa oleva tuote on jo lisätty tietokantaan,
                    //päivitetään vain sen hinta viimeisimpään arvoon.
                    if(productDatabase.at(chain).at(store).at(0).name == productName) {

                        if(parts.at(3) == "out-of-stock") {
                            productDatabase.at(chain).at(store).at(0).price = 0.0;
                        }

                        else {
                            productDatabase.at(chain).at(store).at(0).price = std::stod(parts.at(3));
                        }

                        productFound = true;
                    }
                }

                //Jos tuotetta ei löytynyt kaupasta, lisätään se tietokantaan.
                if(not productFound) {
                    productDatabase.at(chain).at(store).push_back(product);
                }
             }

            else {
                std::vector< Product > items;
                items.push_back(product);
                productDatabase.at(chain).insert({store, items});
            }
        }

        else {
            std::map< std::string, std::vector< Product > > storeName;
            std::vector< Product > items;
            items.push_back(product);
            storeName.insert({store, items});
            productDatabase.insert({chain, storeName});
        }
    }
}


//Funktio saa parametrina tietokannan. Tulostaa kaikki tunnetut kauppaketjut.
void chains(std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase)
{
    for (auto chainIterator = productDatabase.begin(); chainIterator != productDatabase.end(); chainIterator++) {
        std::cout << chainIterator->first << std::endl;
    }
}


//Funktio saa parametreina tietokannan ja halutun kauppaketjun nimen.
//Tulostaa kaikki tunnetut kauppaketjun kaupat.
void stores(std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase, std::string chain)
{
    if (productDatabase.find(chain) != productDatabase.end()) {
        for (auto storeIterator = productDatabase.at(chain).begin(); storeIterator != productDatabase.at(chain).end(); storeIterator++) {
            std::cout << storeIterator->first << std::endl;
        }
    }

    else {
        std::cout << "Error: an unknown chain" << std::endl;
    }
}


//Funktio saa parametreina tietokannan, kauppaketjun nimen ja kaupan nimen.
//Tulostaa kaikki tunnetut kaupan tuotteet ja niiden hinnat. Jos annetun
//kauppaketjun tai kaupan nimi on tuntematon, tulostetaan tilanteen mukaan
//oikea error viesti ja poistutaan funktiosta.
void selection(std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase, std::string chain, std::string store)
{
    if (productDatabase.find(chain) != productDatabase.end()) {
        if (productDatabase.at(chain).find(store) != productDatabase.at(chain).end()) {
            std::sort(productDatabase.at(chain).at(store).begin(), productDatabase.at(chain).at(store).end(), compareByName);

            for (auto selectionIterator = productDatabase.at(chain).at(store).begin(); selectionIterator != productDatabase.at(chain).at(store).end(); selectionIterator++) {
                if (selectionIterator->price == 0) {
                    std::cout << selectionIterator->name << " out of stock" << std::endl;
                }

                else {
                    std::cout << selectionIterator->name << " " << std::setprecision(2) << std::fixed << selectionIterator->price << std::endl;
                }
           }
        }

        else {
            std::cout << "Error: unknown store" << std::endl;
        }
    }

    else {
        std::cout << "Error: unknown chain" << std::endl;
    }
}


//Funktio saa parametreina tietokannan ja tuotteen nimen. Tulostaa halvimman
//hinnan ja kaupat joista tuotteen löytää kyseiseen hintaan.
void cheapest(std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase, std::string productName)
{
    std::vector< double > cheapestVector;
    std::set< std::string > cheapestSet;

    //Käy läpi kaikki kaupat ja tallentaa halutun tuotteen hinnat vectoriin.
    for (auto chainIterator = productDatabase.begin(); chainIterator != productDatabase.end(); chainIterator++) {
         std::string chain = chainIterator->first;

         for (auto storeIterator = productDatabase.at(chain).begin(); storeIterator != productDatabase.at(chain).end(); storeIterator++) {
             std::string store = storeIterator->first;
             std::sort(productDatabase.at(chain).at(store).begin(), productDatabase.at(chain).at(store).end(), compareByPrice);

             for (auto selectionIterator = productDatabase.at(chain).at(store).begin(); selectionIterator != productDatabase.at(chain).at(store).end(); selectionIterator++) {

                 if (selectionIterator->name == productName) {
                     cheapestVector.push_back(selectionIterator->price);
                }
            }
        }
    }

    //Jos yksikään tietokannassa oleva tuote ei täsmännyt kysyttyyn tuotteseen
    //tulostetaan siitä tieto.
    if (cheapestVector.size() == 0) {
        std::cout << "Product is not part of product selection." << std::endl;
    }

    //Jos vectoriin tallentui vain nollia, tulostetaan viesti jossa ilmoitetaan
    //tuotteen olevan kaikkialla out of stock.
    else if ((cheapestVector.at(0) == 0) && (std::equal(cheapestVector.begin() + 1, cheapestVector.end(), cheapestVector.begin()))) {
        std::cout << "The product is temporarily out of stock everywhere." << std::endl;
    }

    else {
        //Poistetaan vectorista kaikki nollat, laitetaan hinnat järjestykseen
        //ja tallennetaan muuttujaan 'cheapestPrice' halvin löydetty
        //kysytyn tuotteen hinta.
        cheapestVector.erase(std::remove(cheapestVector.begin(),cheapestVector.end(), 0), cheapestVector.end());
        std::sort(cheapestVector.begin(), cheapestVector.end());
        double cheapestPrice = cheapestVector.at(0);
        std::cout << std::setprecision(2) << std::fixed << cheapestPrice << " euros" << std::endl;

        //Käydää uudelleen kaikki tuotteet läpi ja tallennetaan set tyyppiseen
        //listaan kaikki kaupat, joista halvimpaan hintaan kysytty tuote.
        for (auto chainIterator = productDatabase.begin(); chainIterator != productDatabase.end(); chainIterator++) {
            std::string chain = chainIterator->first;

             for (auto storeIterator = productDatabase.at(chain).begin(); storeIterator != productDatabase.at(chain).end(); storeIterator++) {
                 std::string store = storeIterator->first;

                 for (auto selectionIterator = productDatabase.at(chain).at(store).begin(); selectionIterator != productDatabase.at(chain).at(store).end(); selectionIterator++) {

                     if ((selectionIterator->price == cheapestPrice) && (selectionIterator->name == productName)) {
                         std::string cheapestPlace = chain + " " + store;
                         cheapestSet.insert(cheapestPlace);
                    }
                }
            }
        }
    }
    for (auto i : cheapestSet) {
        std::cout << i << std::endl;
    }
}


//Funktio saa parametrina tietokannan. Tulostaa kaikki tietokannassa olevat
//tuotteet aakkosjärjestyksessä.
void products(std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase)
{
    std::set< std::string > productList;

    for (auto chainIterator = productDatabase.begin(); chainIterator != productDatabase.end(); chainIterator++) {
         std::string chain = chainIterator->first;

         for (auto storeIterator = productDatabase.at(chain).begin(); storeIterator != productDatabase.at(chain).end(); storeIterator++) {
             std::string store = storeIterator->first;

             for (auto selectionIterator = productDatabase.at(chain).at(store).begin(); selectionIterator != productDatabase.at(chain).at(store).end(); selectionIterator++) {
                 productList.insert(selectionIterator->name);
            }
        }
    }

    for(auto i : productList) {
         std::cout << i << std::endl;
    }
}


//Funktio saa parametrina tietokannan. Funktio otaa vastaan käyttäjältä komennon
//ja mahdollisesti komentoon liittyvät parametrit ja kutsuu oikeaa funktiota,
//joka toteuttaa käskyn. Funktio jatkaa käskyn vastaanottamista niin kauan
//kunnes annetaan komento 'quit'.
void command(std::map< std::string, std::map< std::string, std::vector< Product >>> &productDatabase)
{
    while (true) {
        std::cout << "> ";
        std::string line;
        getline(std::cin, line);

        //Kutsuu splitCommand funktiota joka paloittelee käskyn ja palauttaa
        //osat vectoriin. Ennen käskyn suorittavan funktion kutsumista
        //tarkistetaan että käskylle annettujen parametrien määrä on oikea,
        //muuten tulostetaan error viesti. Jos käskyä ei ole olemassa,
        //tulostetaan siitäkin asiaan kuuluva error viesti.
        std::vector<std::string> parts = splitCommand(line);
        std::string command = parts.at(0);

        if (command == "chains"|| command == "CHAINS") {
            if (parts.size() == 1) {
                chains(productDatabase);
            }

            else {
                std::cout << "Error: error in command " << command << std::endl;
            }
        }

        else if (command == "cheapest" || command == "CHEAPEST") {
            if (parts.size() == 2) {
                cheapest(productDatabase, parts.at(1));
            }

            else {
                std::cout << "Error: error in command " << command << std::endl;
            }
        }

        else if (command == "products" || command == "PRODUCTS") {
            if (parts.size() == 1) {
                products(productDatabase);
            }

            else {
                std::cout << "Error: error in command " << command << std::endl;
            }
        }

        else if (command == "selection" || command == "SELECTION") {
            if (parts.size() == 3) {
                selection(productDatabase, parts.at(1), parts.at(2));
            }

            else {
                std::cout << "Error: error in command " << command << std::endl;
            }
        }

        else if (command == "stores" || command == "STORES") {
            if (parts.size() == 2) {
                stores(productDatabase, parts.at(1));
            }

            else {
                std::cout << "Error: error in command " << command << std::endl;
            }
        }

        else if (command == "quit" || command == "QUIT") {
            exit(EXIT_SUCCESS);
        }

        else {
            std::cout << "Error: unknown command" << std::endl;
        }
    }
}


//Kysyy käyttäjältä tiedostoa josta tuotteiden tiedot luetaan, jos tiedostoa ei
//saada auki tulostetaan error viesti. Jos tiedosto saadaan auki, kutsutaan
//funktioita 'buildDatabase' ja 'command'.
int main()
{
    //Projektiin valittu tietorakenne.
    std::map< std::string, std::map< std::string, std::vector< Product >>> productDatabase;

    std::string inputFile;
    std::cout << "Input file: ";
    std::cin >> inputFile;
    std::ifstream readFile(inputFile);

    if (readFile) {
        buildDatabase(readFile, productDatabase);
    }

    else {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cin.ignore();
    command(productDatabase);
}
