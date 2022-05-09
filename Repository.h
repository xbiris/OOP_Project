#ifndef OOPPROJECT_REPOSITORY_H
#define OOPPROJECT_REPOSITORY_H
#include "Domain.h"
#include <vector>
#include <stack>
using std::vector;
using std::stack;
using std::ostream;

class InstrumentRepository {
public:
    InstrumentRepository();
    //~InstrumentRepository();
    void AddInstrument(Instrument* instrument, unsigned int index);
    void RemoveInstrument(unsigned int index);
    void EditInstrument(unsigned int index, vector<string> newValues);
    void LoadData(const string& fileName);
    void SaveData(const string& fileName);
    static vector<string> StringToVector(const string &line, InstrumentsEnum &instrumentsEnum);
    static Instrument* StringToInstrument(const string &line);
    inline vector<Instrument*> getInstruments() {return this->instruments; }
    friend ostream& operator<<(ostream& o, const InstrumentRepository& instrumentRepository);
private:
    vector<Instrument*> instruments;
};

#endif //OOPPROJECT_REPOSITORY_H
