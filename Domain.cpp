#include "Domain.h"
#include <utility>
#include <fstream>
using std::stringstream;

/***
 * Constructor for the base class
 * @param i id
 * @param p price
 * @param a acoustic
 */
Instrument::Instrument(int i, float p, bool a) {
    this->id = i;
    this->price = p;
    this->acoustic = a;
}

/***
 * Returns the string representation of an instrument - can be overloaded
 */
string Instrument::getAllInfo() {
    string s;
    s += to_string(this->getId()) + "," + to_string(this->getPrice()) + "," + to_string(this->getAcoustic()) + ",";
    return s;
}

/***
 * Constructor for guitar
 */
Guitar::Guitar(int i, float p, bool a, int nrS, bool steelStr) : Instrument{i, p, a} {
    this->nrStrings = nrS;
    this->steelStrings = steelStr;
}

/***
 * Copy constructor for guitar
 */
Guitar::Guitar(const Guitar &guitar) : Instrument(guitar.getId(), guitar.getPrice(), guitar.getAcoustic()) {
    this->nrStrings = guitar.nrStrings;
    this->steelStrings = guitar.steelStrings;
}

/***
 * String representation of a guitar
 */
string Guitar::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[Guitar_] + ",";
    s += to_string(this->getNrStrings()) + "," + to_string(this->getSteelStrings()) + "\n";
    return s;
}

/***
 * Updates the attributes of a guitar with new values
 * @param newInfo - given vector of new values
 */
void Guitar::editAllInfo(vector<string> newInfo) {
    try{
        *this = Guitar(stoi(newInfo.at(0)),
                                  stof(newInfo.at(1)),
                                  stoi(newInfo.at(2)),
                                  stoi(newInfo.at(3)),
                                  stoi(newInfo.at(4)));
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

/***
 * Constructor for violin
 */
Violin::Violin(int i, float p, bool a, int nrS, int s) : Instrument{i, p, a} {
    this->nrStrings = nrS;
    this->size = s;
}

/***
 * Copy constructor for violin
 */
Violin::Violin(const Violin &violin) : Instrument(violin.getId(), violin.getPrice(), violin.getAcoustic()) {
    this->nrStrings = violin.nrStrings;
    this->size = violin.size;
}

/***
 * String representation of a violin
 */
string Violin::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[Violin_] + ",";
    s += to_string(this->getNrStrings()) + "," + to_string(this->getSize()) + "\n";
    return s;
}

/***
 * Updates the attributes of a violin with new values
 * @param newInfo - given vector of new values
 */
void Violin::editAllInfo(vector<string> newInfo) {
    try{
        *this = Violin(stoi(newInfo.at(0)),
                                  stof(newInfo.at(1)),
                                  stoi(newInfo.at(2)),
                                  stoi(newInfo.at(3)),
                                  stoi(newInfo.at(4)));
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

/***
 * Constructor for drum kit
 */
DrumKit::DrumKit(int i, float p, bool a, int nrPie, bool dou) : Instrument{i, p, a} {
    this->nrPiecesKit = nrPie;
    this->doubleBass = dou;
}

/***
 * Copy constructor for drum kit
 */
DrumKit::DrumKit(const DrumKit &drumKit) : Instrument(drumKit.getId(), drumKit.getPrice(), drumKit.getAcoustic()) {
    this->doubleBass = drumKit.doubleBass;
    this->nrPiecesKit = drumKit.nrPiecesKit;
}


/***
 * String representation of a drum kit
 */
string DrumKit::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[DrumKit_] + ",";
    s += to_string(this->getNrPieces()) + "," + to_string(this->getDoubleBass()) + "\n";
    return s;
}

/***
 * Updates the attributes of a drum kit with new values
 * @param newInfo - given vector of new values
 */
void DrumKit::editAllInfo(vector<string> newInfo) {
    try{
        *this = DrumKit(stoi(newInfo.at(0)),
                                    stof(newInfo.at(1)),
                                    stoi(newInfo.at(2)),
                                    stoi(newInfo.at(3)),
                                    stoi(newInfo.at(4)));
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}

/***
 * Constructor for flute
 */
Flute::Flute(int i, float p, bool a, string mat) : Instrument{i, p, a} {
    this->material = std::move(mat);
}

/***
 * Copy constructor for flute
 */
Flute::Flute(const Flute &flute) : Instrument(flute.getId(), flute.getPrice(), flute.getAcoustic()) {
    this->material = flute.material;
}

/***
 * String representation of a flute
 */
string Flute::getAllInfo() {
    string s = Instrument::getAllInfo() + enum_str[Flute_] + ",";
    s += this->getMaterial() + "\n";
    return s;
}

/***
 * Updates the attributes of a flute with new values
 * @param newInfo - given vector of new values
 */
void Flute::editAllInfo(vector<string> newInfo) {
    try{
        *this = Flute(stoi(newInfo.at(0)),
                                stof(newInfo.at(1)),
                                stoi(newInfo.at(2)),
                                newInfo.at(3));
    }
    catch(...) {
        std::cout<<"An exception occurred";
    }
}



