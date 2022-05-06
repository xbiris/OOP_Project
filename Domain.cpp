#include "Domain.h"
#include <utility>

Instrument::Instrument(int i, float p, bool a) {
    this->id = i;
    this->price = p;
    this->acoustic = a;
}

string Instrument::getAllInfo() {
    string s;
    s += to_string(this->getId()) + "," + to_string(this->getPrice()) + "," + to_string(this->getAcoustic()) + ",";
    return s;
}

Guitar::Guitar(int i, float p, bool a, int nrS, bool steelStr) : Instrument{i, p, a} {
    this->nrStrings = nrS;
    this->steelStrings = steelStr;
}

Guitar::Guitar(const Guitar &guitar) : Instrument(guitar.getId(), guitar.getPrice(), guitar.getAcoustic()) {
    this->nrStrings = guitar.nrStrings;
    this->steelStrings = guitar.steelStrings;
}

string Guitar::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[Guitar_] + ",";
    s += to_string(this->getNrStrings()) + "," + to_string(this->getSteelStrings()) + "\n";
    return s;
}

void Guitar::editAllInfo(vector<string> newInfo) {
    try{
        auto* guitar = new Guitar(stoi(newInfo.at(0)),
                                  stof(newInfo.at(1)),
                                  stoi(newInfo.at(2)),
                                  stoi(newInfo.at(3)),
                                  stoi(newInfo.at(4)));
        *this = *guitar;
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

Violin::Violin(int i, float p, bool a, int nrS, int s) : Instrument{i, p, a} {
    this->nrStrings = nrS;
    this->size = s;
}

string Violin::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[Violin_] + ",";
    s += to_string(this->getNrStrings()) + "," + to_string(this->getSize()) + "\n";
    return s;
}

void Violin::editAllInfo(vector<string> newInfo) {
    try{
        auto* violin = new Violin(stoi(newInfo.at(0)),
                                  stof(newInfo.at(1)),
                                  stoi(newInfo.at(2)),
                                  stoi(newInfo.at(3)),
                                  stoi(newInfo.at(4)));
        *this = *violin;
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

Violin::Violin(const Violin &violin) : Instrument(violin.getId(), violin.getPrice(), violin.getAcoustic()) {
    this->nrStrings = violin.nrStrings;
    this->size = violin.size;
}


DrumKit::DrumKit(int i, float p, bool a, int nrPie, bool dou) : Instrument{i, p, a} {
    this->nrPiecesKit = nrPie;
    this->doubleBass = dou;
}

string DrumKit::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[DrumKit_] + ",";
    s += to_string(this->getNrPieces()) + "," + to_string(this->getDoubleBass()) + "\n";
    return s;
}

void DrumKit::editAllInfo(vector<string> newInfo) {
    try{
        auto* drumKit = new DrumKit(stoi(newInfo.at(0)),
                                    stof(newInfo.at(1)),
                                    stoi(newInfo.at(2)),
                                    stoi(newInfo.at(3)),
                                    stoi(newInfo.at(4)));
        *this = *drumKit;
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

DrumKit::DrumKit(const DrumKit &drumKit) : Instrument(drumKit.getId(), drumKit.getPrice(), drumKit.getAcoustic()) {
    this->doubleBass = drumKit.doubleBass;
    this->nrPiecesKit = drumKit.nrPiecesKit;
}


Flute::Flute(int i, float p, bool a, string mat) : Instrument{i, p, a} {
    this->material = std::move(mat);
}

string Flute::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[Flute_] + ",";
    s += this->getMaterial() + "\n";
    return s;
}

void Flute::editAllInfo(vector<string> newInfo) {
    try{
        auto* flute = new Flute(stoi(newInfo.at(0)),
                                stof(newInfo.at(1)),
                                stoi(newInfo.at(2)),
                                newInfo.at(3));
        *this = *flute;
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

Flute::Flute(const Flute &flute) : Instrument(flute.getId(), flute.getPrice(), flute.getAcoustic()) {
    this->material = flute.material;
}


