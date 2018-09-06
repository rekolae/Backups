#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>
#include <memory>

class Cards {

    public:
      // Dynaamisella rakenteella on oltava rakentaja,
      // joka alustaa paallimmainen-osoittimen nullptr:ksi.
      Cards();

      // Lisää uuden kortin annetulla id:llä pinon päällimmäiseksi.
      void add(int id);

      // Tulostaa tietorakenteen sisällön järjestysnumeroituna
      // parametrina annettuun tietovirtaan aloittaen ensimmäisestä alkiosta.
      void print(std::ostream& s);

      // Poistaa pinon päällimmäisen kortin ja palauttaa
      // sen viiteparametrissa luku. Paluuarvo true
      // jos onnistuu, false jos pino oli tyhjä.
      bool remove(int& id);

      // Kääntää tietorakenteen sisällön päinvastaiseksi.
      void reverse();

    private:
      struct Card_data {
        int data;
        std::shared_ptr<Card_data> next;
      };

      std::shared_ptr<Card_data> top_;
};

#endif // CARDS_HH
