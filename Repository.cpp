#include <filesystem>
#include <fstream>
#include <utility>
#include "Repository.h"
#include "Domain.h"
#include <sstream>

using std::stringstream;
using std::filesystem::current_path;
using std::stoi;
using std::stof;

InstrumentRepository::InstrumentRepository() {
    this->instruments = vector<Instrument*>();
}

InstrumentRepository::~InstrumentRepository() {
    for(auto & instrument : instruments){
        delete instrument;
    }
}

ostream &operator<<(ostream &o, const InstrumentRepository& instrumentRepository) {
    for(auto & instrument : instrumentRepository.instruments)
    {
        o<<instrument->getAllInfo()<<"\n";
    }
    return o;
}

void InstrumentRepository::AddInstrument(Instrument *instrument) {
     this->instruments.push_back(instrument);
     undoStack.push("R");
}

void InstrumentRepository::RemoveInstrument(unsigned int index) {
    if(index < 0 || index >= this->instruments.size())
        throw std::exception();
    undoStack.push(instruments[index]->getAllInfo());
    auto x = this->instruments[index];
    this->instruments.erase(this->instruments.begin() + index);
    delete x;
}

void InstrumentRepository::EditInstrument(unsigned int index, vector<string> newValues) {
    if(index < 0 || index >= this->instruments.size())
        throw std::exception();

    this->instruments[index]->editAllInfo(std::move(newValues));
}

void InstrumentRepository::LoadData(const string& fileName) {
    std::ifstream csvFile;
    csvFile.open(current_path().parent_path().string() + "/Saves/" + fileName + ".csv");
    string line;
    while (csvFile >> line) {
        auto i = StringToInstrument(line);
        if(i != nullptr) {
            AddInstrument(i);
        }
    }
}

void InstrumentRepository::SaveData(const string& fileName) {
    std::ofstream csvFile;
    csvFile.open(current_path().parent_path().string() + "/Saves/" + fileName + ".csv" ,std::fstream::out);

    for(auto instrument : instruments){
        csvFile<<instrument->getAllInfo();
    }
}

void InstrumentRepository::Undo() {
    if(undoStack.empty())
        return;

    if(undoStack.top() == "R" && !this->instruments.empty()){
        redoStack.push(instruments.back()->getAllInfo());
        auto x = this->instruments.at(this->instruments.size() - 1);
        this->instruments.pop_back();
        delete x;
    }
    else{
        redoStack.push("R");
        auto i = StringToInstrument(undoStack.top());
        if(i != nullptr)
            this->instruments.push_back(i);
    }
    undoStack.pop();
}

void InstrumentRepository::Redo() {
    if(redoStack.empty())
        return;

    if(redoStack.top() == "R" && !this->instruments.empty()){
        auto x = this->instruments.at(this->instruments.size() - 1);
        this->instruments.pop_back();
        delete x;
    }
    else {
        auto i = StringToInstrument(redoStack.top());
        if(i != nullptr)
            this->instruments.push_back(i);
    }
}

Instrument *InstrumentRepository::StringToInstrument(const string &line) {
    vector<string> row;
    string word;
    stringstream s(line);
    InstrumentsEnum instrumentsEnum;
    while (getline(s, word, ',')) {
        if(word == enum_str[Guitar_]){
            instrumentsEnum = Guitar_;
        }
        else if(word == enum_str[Violin_]){
            instrumentsEnum = Violin_;
        }
        else if(word == enum_str[DrumKit_]){
            instrumentsEnum = DrumKit_;
        }
        else if(word == enum_str[Flute_]){
            instrumentsEnum = Flute_;
        }
        else{
            row.push_back(word);
        }
    }

    if(instrumentsEnum == Guitar_){
        return new Guitar(stoi(row[0]),
                          stof(row[1]),
                          stoi(row[2]),
                          stoi(row[3]),
                          stoi(row[4]));
    }
    else if(instrumentsEnum == Violin_){
        return new Violin(stoi(row[0]),
                          stof(row[1]),
                          stoi(row[2]),
                          stoi(row[3]),
                          stoi(row[4]));
    }
    else if(instrumentsEnum == DrumKit_){
        return new DrumKit(stoi(row[0]),
                           stof(row[1]),
                           stoi(row[2]),
                           stoi(row[3]),
                           stoi(row[4]));
    }
    else if(instrumentsEnum == Flute_){
        return new Flute(stoi(row[0]),
                         stof(row[1]),
                         stoi(row[2]),
                         row[3]);
    }
    return nullptr;
}