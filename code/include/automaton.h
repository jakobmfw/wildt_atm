// Author : Jakob Wildt
// Project: Bankomat Boost
// File   : automaton.h
#pragma once
#include "boost/include/sml.hpp"
#include <iostream>

using namespace std;
namespace sml = boost::sml;


namespace{
//states
/*
struct automat_bereit{};

struct erwarte_pin{};

struct falscher_pin1{};

struct falscher_pin2{};

struct aktion_auswahlen{};

struct geld_abheben{};

struct karte_ausgegeben{};

struct kontostand{};
*/

//events
struct karte_eingef{
    string karte = "";
};
struct pin{
    int pin = 0;
};
struct abbruch{
    bool value = true;
};
struct falscher_pin{
    int wrong_pin = 0;
};
struct geld_abheben_e{
    bool geld = true;
};
struct kontostand_e{
    bool kontostand = true;
};
struct x_euro{
    int euro = 0;
};
struct weitere_aktion{
    bool action = true;
};

struct Automaton {

public:
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
     *"automat_bereit"_s + event<karte_eingef> = "erwarte_pin"_s,
      "erwarte_pin"_s + event<pin> = "aktion_auswahlen"_s,
      "erwarte_pin"_s + event<abbruch> = "automat_bereit"_s,
      "erwarte_pin"_s + event<falscher_pin> = "falscher_pin1"_s,
      "falscher_pin1"_s + event<falscher_pin> = "falscher_pin2"_s,
      "falscher_pin2"_s + event<falscher_pin>  = "automat_bereit"_s,
      "aktion_auswahlen"_s + event<geld_abheben_e> = "geld_abheben"_s,
      "aktion_auswahlen"_s + event<kontostand_e> = "kontostand"_s,
      "aktion_auswahlen"_s + event<abbruch> = "automat_bereit"_s,
      "geld_abheben"_s + event<x_euro> = "karte_ausgegeben"_s,
      "geld_abheben"_s + event<abbruch> = "automat_bereit"_s,
      "karte_ausgegeben"_s + event<x_euro> = "automat_bereit"_s,
      "kontostand"_s + event<weitere_aktion> = "aktion_auswahlen"_s,
      "kontostand"_s + event<abbruch> = "automat_bereit"_s
    );
  }


};
}