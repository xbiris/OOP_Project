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
    ~InstrumentRepository();

    void AddInstrument(Instrument* instrument);
    void RemoveInstrument(unsigned int index);
    void EditInstrument(unsigned int index, vector<string> newValues);
    void LoadData();
    void SaveData();
    static Instrument* StringToInstrument(const string& line);
    void Undo();
    void Redo();
    inline vector<Instrument*> getInstruments() {return this->instruments; }
    friend ostream& operator<<(ostream& o, const InstrumentRepository& instrumentRepository);
private:
    vector<Instrument*> instruments;
    stack<string> undoStack;
    stack<string> redoStack;
};


#endif //OOPPROJECT_REPOSITORY_H
