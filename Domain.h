#ifndef OOPPROJECT_DOMAIN_H
#define OOPPROJECT_DOMAIN_H
#include <iostream>
using std::string;
using std::to_string;

class Instrument {
public:
    Instrument(int i, float p, bool a);

    inline int getId() const { return this->id; }
    inline float getPrice() const { return this->price; }
    inline bool getAcoustic() const { return this->acoustic; }

    virtual string toString();
private:
    int id;
    float price;
    bool acoustic; //true for acoustic, false for electric instrument
};

class Guitar : public Instrument {
public:
    Guitar(int i, float p, bool a, int nrS, bool steelStr);

    inline int getNrStrings() const { return this->nrStrings; }
    inline bool getSteelStrings() const { return this->steelStrings; }

private:
    int nrStrings;
    bool steelStrings; //true for steel strings, false for nylon strings
};

class Violin : public Instrument {
public:
    Violin(int i, float p, bool a, int nrS, int s);

    inline int getNrStrings() const { return this->nrStrings; }
    inline bool getSize() const { return this->size; }

private:
    int nrStrings;
    int size;
};

class DrumKit : public Instrument {
    DrumKit(int i, float p, bool a, int nrPie, bool dou);

    inline int getNrPieces() const { return this->nrPiecesKit; }
    inline bool getDoubleBass() const { return this->doubleBass; }
private:
    int nrPiecesKit;
    bool doubleBass; //true for double bass, false for single bass
};

class Flute : public Instrument {
    Flute(int i, float p, bool a, string mat);

    inline string getMaterial() const { return this->material; }
private:
    string material;
};

#endif //OOPPROJECT_DOMAIN_H
