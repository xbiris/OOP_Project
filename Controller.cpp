#include "Controller.h"

Controller::Controller(const InstrumentRepository& repository) {
    this->instrumentRepository = repository;
}

void Controller::AddInstrument(Instrument *instrument, unsigned int index) {
    undoStack.push("REMOVE-" + to_string(index));
    this->instrumentRepository.AddInstrument(instrument, index);
}

void Controller::RemoveInstrument(unsigned int index) {
    undoStack.push(to_string(index) + "-" + this->instrumentRepository.getInstruments()[index]->getAllInfo());
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

/***
 * Undoes the previous operation
 * If an element has been removed, adds it back
 * If an element has been added, removes it
 */
void Controller::Undo() {
    if(undoStack.empty() || undoStack.top().empty())
        return;
    string top;
    unsigned int index;
    while(undoStack.top().at(0) != '-'){
        top += undoStack.top().at(0);
        undoStack.top().erase(undoStack.top().begin());
    }
    undoStack.top().erase(undoStack.top().begin());

    if(top == "REMOVE" && !this->instrumentRepository.getInstruments().empty()){

        index = stoi(undoStack.top());
        redoStack.push(to_string(index) + "-" + this->instrumentRepository.getInstruments().at(index)->getAllInfo());
        RemoveInstrument(index);
    }
    else{
        index = stoi(top);
        redoStack.push("REMOVE-" + to_string(index));
        auto i = InstrumentRepository::StringToInstrument(undoStack.top());
        if(i != nullptr) {
            AddInstrument(i, index);
        }
    }
    undoStack.pop();
}

/***
 * Cancels the last Undo operation
 */
void Controller::Redo() {
    if(redoStack.empty() || redoStack.top().empty())
        return;

    string top;
    unsigned int index;
    while(redoStack.top().at(0) != '-'){
        top += redoStack.top().at(0);
        redoStack.top().erase(redoStack.top().begin());
    }
    redoStack.top().erase(redoStack.top().begin());

    if(top == "REMOVE" && !this->instrumentRepository.getInstruments().empty()){

        index = stoi(redoStack.top());
        RemoveInstrument(index);
    }
    else {
        auto i = InstrumentRepository::StringToInstrument(redoStack.top());
        if(i != nullptr) {
            index = stoi(top);
            AddInstrument(i, index);
        }
    }
}

/***
 * Filter instruments by a given type
 * Returns a repository of instruments of the same type
 */
InstrumentRepository Controller::FilterByType(InstrumentsEnum type) {
    InstrumentRepository repository;

    for(auto elem : this->instrumentRepository.getInstruments()){
        if(elem->getType() == type){
            repository.AddInstrument(elem, repository.getInstruments().size());
        }
    }

    return repository;
}

InstrumentRepository Controller::getRepository() const{
    return this->instrumentRepository;
}
