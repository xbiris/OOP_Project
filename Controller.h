#ifndef OOPPROJECT_CONTROLLER_H
#define OOPPROJECT_CONTROLLER_H
#include <utility>
#include "Repository.h"

class Controller {
public:
    Controller();
    explicit Controller(const InstrumentRepository& repository);
    void AddInstrument(Instrument* instrument);
    void RemoveInstrument(unsigned int index);
    void EditInstrument(unsigned int index, vector<string> newValues);
    void LoadData(const string& fileName);
    void SaveData(const string& fileName);
    void Undo();
    void Redo();
    inline vector<Instrument*> getInstruments() { return this->instrumentRepository.getInstruments(); }
    [[nodiscard]] InstrumentRepository getRepository() const;
private:
    InstrumentRepository instrumentRepository;
};

Controller::Controller() {
    this->instrumentRepository = InstrumentRepository();
}


Controller::Controller(const InstrumentRepository& repository) {
    this->instrumentRepository = repository;
}

void Controller::AddInstrument(Instrument *instrument) {
    this->instrumentRepository.AddInstrument(instrument);
}

void Controller::RemoveInstrument(unsigned int index) {
    this->instrumentRepository.RemoveInstrument(index);
}

void Controller::EditInstrument(unsigned int index, vector<string> newValues) {
    this->instrumentRepository.EditInstrument(index, std::move(newValues));
}

void Controller::LoadData(const string &fileName) {
    this->instrumentRepository.LoadData(fileName);
}

void Controller::SaveData(const string &fileName) {
    this->instrumentRepository.SaveData(fileName);
}

void Controller::Undo() {
    this->instrumentRepository.Undo();
}

void Controller::Redo() {
    this->instrumentRepository.Redo();
}

InstrumentRepository Controller::getRepository() const{
    return this->instrumentRepository;
}

#endif //OOPPROJECT_CONTROLLER_H
