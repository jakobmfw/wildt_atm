// Author : Jakob Wildt
// Project: Bankomat Boost
// File   : automaton.h
#pragma once
#include "boost/include/sml.hpp"
#include <iostream>
#include <map>
#include <string>

namespace sml = boost::sml;

namespace{

std::map<std::string, int> cards = {
    { "karte1", 1234 },
    { "karte2", 6969 },
    { "karte3", 0420 }
};

std::string karte;
int pin_;
int aktion;
int geldmenge;

float kontostand1{69420};
float kontostand2{187};
float kontostand3{99.90};

//events
struct karte_eingef{
    //std::string karte = "";
};
struct pin{
    //int pin = 0;
};
struct abbruch{
    //bool value = true;
};

struct geld_abheben_e{
    //bool geld = true;
};
struct kontostand_e{
   //bool kontostand = true;
};
struct x_euro{
    //int euro = 0;
};
struct weitere_aktion{
    //bool action = true;
};

//guards

struct Karte{
    int pin;
};

struct PIN {
    int value;
};

const auto right_PIN = [](PIN& pin, Karte& karte){
    std::cout << "PIN VALUE: " << pin.value << std::endl;
    return pin.value == karte.pin;
};

/*const auto abbruch_pin = [](PIN& pin){
    if(pin.value == 'X'){
        return true;
    }
    else{return false;}
    
};*/

PIN pin_inp{};
Karte karte_pin{};

struct Automaton {

public:
  auto operator()() {
    using namespace sml;
    return make_transition_table(
     *"automat_bereit"_s + event<karte_eingef> / [] {std::cout << std::endl << "Neuer State: erwarte PIN" << std::endl << std::endl;} = "erwarte_pin"_s,
      "automat_bereit"_s + on_exit<_> / [] {
          std::cout << "Karte bitte!" << std::endl;
          std::cin >> karte;

          bool check_card{true};

          while(check_card){
        
            if(cards.find(karte) == cards.end()){
                std::cout << "Ungülitge Karte. Karte bitte!" << std::endl;
                std::cin >> karte;
            }
            else{
                karte_pin.pin = cards.at(karte);
                check_card=false;
            }
          }
        
      },
      "erwarte_pin"_s + event<pin> [right_PIN] / [] {std::cout << std::endl << "Neuer State: Aktion auswählen" << std::endl << std::endl;} = "aktion_auswahlen"_s,
      "erwarte_pin"_s + event<abbruch> / [] {std::cout << std::endl << "Neuer State: Automat bereit" << std::endl << std::endl;} = "automat_bereit"_s,
      "erwarte_pin"_s + event<pin> [!right_PIN] / [] {std::cout << std::endl << "Neuer State: Falscher PIN 1" << std::endl << std::endl;} = "falscher_pin1"_s,
      "erwarte_pin"_s + on_entry<_> / [] {
          std::cout << "PIN eingeben!" << std::endl; 
          std::cin >> pin_;
          pin_inp.value = pin_;
        
      },
      "falscher_pin1"_s + event<pin> [!right_PIN] / [] {std::cout << std::endl << "Neuer State: Falscher PIN 2" << std::endl << std::endl;} = "falscher_pin2"_s,
      "falscher_pin1"_s + event<pin> [right_PIN] / [] {std::cout << std::endl << "Neuer State: Aktion auswählen" << std::endl << std::endl;} = "aktion_auswahlen"_s,
      "falscher_pin1"_s + on_entry<_> / [] {
          std::cout << "Fehler 1! PIN erneut eingeben!" << std::endl;
          std::cin >> pin_;
          pin_inp.value = pin_;
      },
      "falscher_pin2"_s + event<pin> [!right_PIN] / [] {
          std::cout << std::endl << "Karte eingezogen!" << std::endl;
          cards.erase(karte);
          std::cout << std::endl << "Neuer State: Automat bereit" << std::endl << std::endl;
          } = "automat_bereit"_s,
      "falscher_pin2"_s + event<pin> [right_PIN] / [] {std::cout << std::endl << "Neuer State: Aktion auswählen" << std::endl << std::endl;} = "aktion_auswahlen"_s,
      "falscher_pin2"_s + on_entry<_> / [] {
          std::cout << "Fehler 2! PIN erneut eingeben!" << std::endl;
          std::cin >> pin_;
          pin_inp.value = pin_;
      },
      "aktion_auswahlen"_s + event<geld_abheben_e> / [] {std::cout << std::endl << "Neuer State: Geld abheben" << std::endl << std::endl;} = "geld_abheben"_s,
      "aktion_auswahlen"_s + event<kontostand_e> / [] {std::cout << std::endl << "Neuer State: Kontostand" << std::endl << std::endl;} = "kontostand"_s,
      "aktion_auswahlen"_s + event<abbruch> / [] {std::cout << std::endl << "Neuer State: Automat bereit" << std::endl << std::endl;} = "automat_bereit"_s,
      "aktion_auswahlen"_s + on_entry<_> / [] {
          std::cout << "Aktion auswählen! 1. Geld abheben, 2. Kontostand anzeigen oder 3. Abbrechen!" << std::endl;
          std::cin >> aktion;
      },
      "geld_abheben"_s + event<x_euro> / [] {std::cout << std::endl << "Neuer State: Karte ausgegeben" << std::endl << std::endl;} = "karte_ausgegeben"_s,
      "geld_abheben"_s + event<abbruch> / [] {std::cout << std::endl << "Neuer State: Automat bereit" << std::endl << std::endl;} = "automat_bereit"_s,
      "geld_abheben"_s + on_entry<_> / [] {

          std::cout << "Wie viel wollen Sie abheben? (in Euro)" << std::endl;
          std::cout << "Abheben: €";
          std::cin >> geldmenge;

          while(geldmenge > 400){
              std::cout << "Sie können nicht mehr als 400 Euro abheben." << std::endl;
              std::cout << "Wie viel wollen Sie abheben? (in Euro)" << std::endl;
              std::cout << "Abheben: €";
              std::cin >> geldmenge;
          }

          if(karte == "karte1"){
                if(kontostand1 - geldmenge < 0){
                    std::cout << "Nicht genügend Geld am Konto!" << std::endl;
                    
                }
                else{

                    kontostand1 -= geldmenge;

                    std::cout << "Karte wird ausgegeben!" << std::endl;

                    std::cout << "Ausgabe: " << geldmenge << "€" << std::endl;

                }
            }
            else if(karte == "karte2"){
                if(kontostand2 - geldmenge < 0){
                    std::cout << "Nicht genügend Geld am Konto!" << std::endl;
                    
                }
                else{

                    kontostand2 -= geldmenge;

                    std::cout << "Karte wird ausgegeben!" << std::endl;

                    std::cout << "Ausgabe: " << geldmenge << "€" << std::endl;


                }
            }
            else if(karte == "karte3"){
                if(kontostand3 - geldmenge < 0){

                    std::cout << "Nicht genügend Geld am Konto!" << std::endl;
                        
                }
                else{

                    kontostand3 -= geldmenge;

                    std::cout << "Karte wird ausgegeben!" << std::endl;

                    std::cout << "Ausgabe: " << geldmenge << "€" << std::endl;

                }
            }
        },
      "karte_ausgegeben"_s + event<x_euro> / [] {std::cout << "Neuer State: Automat bereit" << std::endl << std::endl;} = "automat_bereit"_s,
      "kontostand"_s + event<weitere_aktion> / [] {std::cout << "Neuer State: Aktion auswählen" << std::endl << std::endl;} = "aktion_auswahlen"_s,
      "kontostand"_s + event<abbruch> / [] {std::cout << "Neuer State: Automat bereit" << std::endl << std::endl;} = "automat_bereit"_s,
      "kontostand"_s + on_entry<_> / [] {
        if(karte == "karte1"){
            std::cout << kontostand1 << "€" << std::endl;
        }
        else if(karte == "karte2"){
            std::cout << kontostand2 << "€" << std::endl;
        }
        else if(karte == "karte3"){
            std::cout << kontostand3 << "€" << std::endl;
        }
      }
    );
  }


};
}

