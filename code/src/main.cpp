// Author : Jakob Wildt
// Project: Bankomat Boost
// File   : main.cpp

#include "boost/include/sml.hpp"
#include <iostream>
#include "automaton.h"
#include <map>

using namespace std;

namespace sml = boost::sml;

int main(){

  using namespace sml;

  sm<Automaton> sm{pin_inp, karte_pin};

  while(true){

    sm.process_event(karte_eingef{});

    sm.process_event(pin{});

    if(aktion == 1){
      sm.process_event(geld_abheben_e{});
      sm.process_event(x_euro{});
      sm.process_event(x_euro{});
    }
    else{
      sm.process_event(kontostand_e{});
      sm.process_event(weitere_aktion{});
    }
  }

}












/*int main(){

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

    float kontostand1{69420};
    float kontostand2{187};
    float kontostand3{99.90};

    bool run{true};

    

    sm<Automaton> sm{karte_inp, pin_inp};

    while(run){

        cout << "Karte bitte!" << endl;
        cin >> karte;
        cout << endl << endl;

        if(cards.find(karte) == cards.end()){
          cout << "Falsche Karte!" << endl;

          sm.process_event(abbruch{true});
          continue;
        }
        else{

          sm.process_event(karte_eingef{karte});

          karte_inp.pin = cards.at(karte);

          cout << "PIN eingeben!" << endl;
          cin >> pin_;
          cout << endl << endl;

          try{

            //if(cards.at(karte) == pin_){

            pin_inp.value = pin_;

            sm.process_event(pin{pin_});

            cout << "Aktion auswählen! 1. Geld abheben oder 2. Kontostand anzeigen" << endl;
            cin >> aktion;

            if (aktion == 1){
                sm.process_event(geld_abheben_e{true});

                cout << "Wie viel wollen Sie abheben?" << endl;
                cin >> geldmenge;

                if(karte == "karte1"){
                if(kontostand1 - geldmenge < 0){
                    cout << "Nicht genügend Geld am Konto!" << endl;
                    continue;
                }
                else{

                    kontostand1 -= geldmenge;

                    sm.process_event(x_euro{geldmenge});
                    cout << "Karte wird ausgegeben!" << endl;

                    sm.process_event(x_euro{geldmenge});
                    cout << "Ausgabe: " << geldmenge << endl;

                    sm.process_event(abbruch{true});
                    continue;
                }
                }
                else if(karte == "karte2"){
                if(kontostand2 - geldmenge < 0){
                    cout << "Nicht genügend Geld am Konto!" << endl;
                    continue;
                }
                else{

                    kontostand2 -= geldmenge;

                    sm.process_event(x_euro{geldmenge});
                    cout << "Karte wird ausgegeben!" << endl;

                    sm.process_event(x_euro{geldmenge});
                    cout << "Ausgabe: " << geldmenge << endl;

                    sm.process_event(abbruch{true});
                    continue;
                }
                }
                else if(karte == "karte3"){
                if(kontostand3 - geldmenge < 0){
                    cout << "Nicht genügend Geld am Konto!" << endl;
                    continue;
                }
                else{

                    kontostand3 -= geldmenge;

                    sm.process_event(x_euro{geldmenge});
                    cout << "Karte wird ausgegeben!" << endl;

                    sm.process_event(x_euro{geldmenge});
                    cout << "Ausgabe: " << geldmenge << endl;

                    sm.process_event(abbruch{true});
                    continue;
                }
                }

            }
            else if(aktion == 2){

                sm.process_event(kontostand_e{true});

                if(karte == "karte1"){
                cout << kontostand1 << "€" << endl;
                }
                else if(karte == "karte2"){
                cout << kontostand2 << "€" << endl;
                }
                else if(karte == "karte3"){
                cout << kontostand3 << "€" << endl;
                }

                sm.process_event(abbruch{true});
                continue;
            }

            }
            else{
              sm.process_event(falscher_pin{});
              
            }

        }
        catch(const std::exception& e){
            cerr << "Unerwarteter Fehler aufgetreten!" << endl;
        }
        
        }
    }
}

void check_card(string karte){

    if(karte != "karte1" && karte != "karte2" && karte != "karte3"){

        cout << "Karte bitte!" << endl;
        cin >> karte;

        check_card(karte);
    }
    else{
        return;
    }



}*/