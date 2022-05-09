#ifndef OOPPROJECT_CONTROLLER_H
#define OOPPROJECT_CONTROLLER_H
#include <utility>
#include "Repository.h"

class Controller {
public:
    Controller(const InstrumentRepository& repository = InstrumentRepository());
    void AddInstrument(Instrument* instrument, unsigned int index);
    void RemoveInstrument(unsigned int index);
    void EditInstrument(unsigned int index, vector<string> newValues);
    void LoadData(const string& fileName);
    void SaveData(const string& fileName);
    void Undo();
    void Redo();
    InstrumentRepository FilterByType(InstrumentsEnum type);
    inline vector<Instrument*> getInstruments() { return this->instrumentRepository.getInstruments(); }
    [[nodiscard]] InstrumentRepository getRepository() const;
private:
    InstrumentRepository instrumentRepository;
    stack<string> undoStack;
    stack<string> redoStack;
};



#endif //OOPPROJECT_CONTROLLER_H
