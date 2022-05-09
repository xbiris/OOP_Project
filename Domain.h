#ifndef OOPPROJECT_DOMAIN_H
#define OOPPROJECT_DOMAIN_H
#include <iostream>
#include <vector>
using std::string;
using std::vector;
using std::to_string;

enum InstrumentsEnum{
    Guitar_ = 0,
    Violin_ = 1,
    DrumKit_ = 2,
    Flute_ = 3
};

static const char *enum_str[] = {
        "Guitar",
        "Violin",
        "DrumKit",
        "Flute"
};

class Instrument {
public:
    Instrument(int i, float p, bool a);

    inline int getId() const { return this->id; }
    inline float getPrice() const { return this->price; }
    inline bool getAcoustic() const { return this->acoustic; }

    virtual InstrumentsEnum getType() = 0;
    virtual void editAllInfo(vector<string> newInfo) = 0;
    virtual string getAllInfo() = 0;
private:
    int id;
    float price;
    bool acoustic; //true for acoustic, false for electric instrument
};

class Guitar : public Instrument {
public:
    Guitar(int i, float p, bool a, int nrS, bool steelStr);
    Guitar(const Guitar &guitar);

    inline int getNrStrings() const { return this->nrStrings; }
    inline bool getSteelStrings() const { return this->steelStrings; }

    inline InstrumentsEnum getType() override { return Guitar_; };
    void editAllInfo(vector<string> newInfo) override;
    string getAllInfo() override;
private:
    int nrStrings;
    bool steelStrings; //true for steel strings, false for nylon strings
};

class Violin : public Instrument {
public:
    Violin(int i, float p, bool a, int nrS, int s);
    Violin(const Violin &violin);

    inline int getNrStrings() const { return this->nrStrings; }
    inline int getSize() const { return this->size; }

    inline InstrumentsEnum getType() override { return Violin_; };
    void editAllInfo(vector<string> newInfo) override;
    string getAllInfo() override;

private:
    int nrStrings;
    int size;
};

class DrumKit : public Instrument {
public:
    DrumKit(int i, float p, bool a, int nrPie, bool dou);
    DrumKit(const DrumKit &drumKit);

    inline int getNrPieces() const { return this->nrPiecesKit; }
    inline bool getDoubleBass() const { return this->doubleBass; }

    inline InstrumentsEnum getType() override { return DrumKit_; };
    void editAllInfo(vector<string> newInfo) override;
    string getAllInfo() override;

private:
    int nrPiecesKit;
    bool doubleBass; //true for double bass, false for single bass
};

class Flute : public Instrument {
public:
    Flute(int i, float p, bool a, string mat);
    Flute(const Flute &flute);

    inline string getMaterial() const{ return this->material; }

    inline InstrumentsEnum getType() override { return Flute_; };
    void editAllInfo(vector<string> newInfo) override;
    string getAllInfo() override;
private:
    string material;
};

#endif //OOPPROJECT_DOMAIN_H
