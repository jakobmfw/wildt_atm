// Author : Jakob Wildt
// Project: Bankomat Boost
// File   : automaton.h
#pragma once
#include "boost/sml.hpp"
#include <iostream>

using namespace std;
namespace sml = boost::sml;

class Automaton {

public:
  auto operator()() {
    using namespace sml;
    return make_transition_table(
     *"automat_bereit"_s + event<karte_eingef> [ guard ] / action = "erwarte_pin"_s,
      "erwarte_pin"_s + event<pin> [ guard ] / action = "aktion_auswahlen"_s,
      "erwarte_pin"_s + event<abbruch> [ guard ] / action = "automat_bereit"_s,
      "erwarte_pin"_s + event<falscher_pin> [ guard ] / action = "falscher_pin1"_s,
      "falscher_pin1"_s + event<falscher_pin> [ guard ] / action = "falscher_pin2"_s,
      "falscher_pin2"_s + event<falscher_pin> [ guard ] / action = "automat_bereit"_s,
      "aktion_auswahlen"_s + event<geld_abheben> [ guard ] / action = "geld_abheben"_s,
      "aktion_auswahlen"_s + event<kontostand> [ guard ] / action = "kontostand"_s,
      "aktion_auswahlen"_s + event<abbruch> [ guard ] / action = "automat_bereit"_s,
      "geld_abheben"_s + event<x_euro> [ guard ] / action = "karte_ausgegeben"_s,
      "geld_abheben"_s + event<abbruch> [ guard ] / action = "automat_bereit"_s,
      "karte_ausgegeben"_s + event<x_euro> [ guard ] / action = "automat_bereit"_s,
      "kontostand"_s + event<weitere_aktion> [ guard ] / action = "aktion_auswahlen"_s,
      "kontostand"_s + event<abbruch> [ guard ] / action = "automat_bereit"_s
    );
  }


};

//states
struct automat_bereit{};

struct erwarte_pin{};

struct falscher_pin1{};

struct falscher_pin2{};

struct aktion_auswahlen{};

struct geld_abheben{};

struct karte_ausgegeben{};

struct kontostand{};

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
struct geld_abheben{
    bool geld = true;
};
struct kontostand{
    bool kontostand = true;
};
struct x_euro{
    int euro = 0;
};
struct weitere_aktion{
    bool action = true;
};