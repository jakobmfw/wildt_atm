// Author : Jakob Wildt
// Project: Bankomat Boost
// File   : main.cpp

#include "boost/sml.hpp"
#include <iostream>
#include "automaton.h"
#include <map>


namespace sml = boost::sml;

int main(int argc, char* argv[]){

  std::map<string, int> cards = {
    { "karte1", 1234 },
    { "karte2", 6969 },
    { "karte3", 0420 }
};

  string karte{};
  int pin{};
  int aktion{};
  Automaton sm = new Automaton();

  while(true){
    cout << "Karte bitte!" << endl;
    cin >> karte;

    if(cards.find(karte) == cards.end()){
      cout << "Falsche Karte!" << endl;
      continue;
    }
    else{

      sm.process_event(karte_eingef{});


      cout << "PIN eingeben!" << endl;
      cin >> pin;

      try{
        if(cards.at(karte) == pin){

          sm.process_event(pin{});

          cout << "Aktion auswählen! 1. Geld abheben oder 2. Kontostand anzeigen" << endl;
          cin >> aktion;

          if (aktion == 1){
            sm.process_event(geld_abheben);xw
          }
          else if(aktion == 2){
            sm.process_event(kontostand);
          }

        }

      }
      catch(const std::exception& e){
        cerr << "Unerwarteter Fehler aufgetreten!" << endl;
      }
      
    }
  }
}

