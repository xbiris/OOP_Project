#include "Repository.h"

void InstrumentRepository::AddInstrument(Instrument *instrument) {
     this->instruments.push_back(instrument);
}

ostream &operator<<(ostream &o, const InstrumentRepository& instrumentRepository) {
    for(auto & instrument : instrumentRepository.instruments)
    {
        o<<instrument->toString()<<"\n";
    }
    return o;
}

void InstrumentRepository::RemoveInstrument(unsigned int index) {

}

void InstrumentRepository::EditInstrument(unsigned int index) {
}
