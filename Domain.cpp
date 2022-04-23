#include "Domain.h"

#include <utility>

Instrument::Instrument(int i, float p, bool a) {
    this->id = i;
    this->price = p;
    this->acoustic = a;
}

string Instrument::toString() {
    string s = "[";
    s += &"Instrument " [ this->id];
    s += acoustic ? "\nAcoustic" : "\nElectric";
    s += "\nPrice: " + to_string(this->price);
    s+= "\n]";

    return s;
}

Guitar::Guitar(int i, float p, bool a, int nrS, bool steelStr) : Instrument{i, p, a} {
    this->nrStrings = nrS;
    this->steelStrings = steelStr;
}

Violin::Violin(int i, float p, bool a, int nrS, int s) : Instrument{i, p, a} {
    this->nrStrings = nrS;
    this->size = s;
}

DrumKit::DrumKit(int i, float p, bool a, int nrPie, bool dou) : Instrument{i, p, a} {
    this->nrPiecesKit = nrPie;
    this->doubleBass = dou;
}

Flute::Flute(int i, float p, bool a, string mat) : Instrument{i, p, a} {
    this->material = std::move(mat);
}

