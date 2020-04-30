// Author : Jakob Wildt
// Project: Bankomat Boost
// File   : main.cpp

#include "boost/include/sml.hpp"
#include <iostream>
#include "automaton.h"
#include <map>


namespace sml = boost::sml;

int main(){

  using namespace sml;

  std::map<string, int> cards = {
    { "karte1", 1234 },
    { "karte2", 6969 },
    { "karte3", 0420 }
};

  string karte{};
  int pin_{};
  int aktion{};
  int geldmenge{};

  sm<Automaton> sm;

  while(true){
    cout << "Karte bitte!" << endl;
    cin >> karte;

    if(cards.find(karte) == cards.end()){
      cout << "Falsche Karte!" << endl;

      sm.process_event(abbruch{true});
      continue;
    }
    else{

      sm.process_event(karte_eingef{karte});


      cout << "PIN eingeben!" << endl;
      cin >> pin_;

      try{
        if(cards.at(karte) == pin_){

          sm.process_event(pin{pin_});

          cout << "Aktion auswählen! 1. Geld abheben oder 2. Kontostand anzeigen" << endl;
          cin >> aktion;

          if (aktion == 1){
            sm.process_event(geld_abheben_e{true});

            cout << "Wie viel wollen Sie abheben?" << endl;
            cin >> geldmenge;

            sm.process_event(x_euro{geldmenge});
            cout << "Karte wird ausgegeben!" << endl;

            sm.process_event(x_euro{geldmenge});
            cout << "Ausgabe: " << geldmenge << endl;

            sm.process_event(abbruch{true});
            continue;

          }
          else if(aktion == 2){
            sm.process_event(kontostand_e{true});
            cout << "Kontostand: 69 Euronen!" << endl;

            sm.process_event(abbruch{true});
            continue;
          }

        }

      }
      catch(const std::exception& e){
        cerr << "Unerwarteter Fehler aufgetreten!" << endl;
      }
      
    }
  }
}

