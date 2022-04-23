#ifndef OOPPROJECT_REPOSITORY_H
#define OOPPROJECT_REPOSITORY_H
#include "Domain.h"
#include <vector>
using std::vector;
using std::ostream;

class InstrumentRepository {
public:
    void AddInstrument(Instrument* instrument);
    void RemoveInstrument(unsigned int index);
    void EditInstrument(unsigned int index);
    inline vector<Instrument*> getInstruments() {return this->instruments; }
    friend ostream& operator<<(ostream& o, const InstrumentRepository& instrumentRepository);
private:
    vector<Instrument*> instruments;
};


#endif //OOPPROJECT_REPOSITORY_H
