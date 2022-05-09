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

/***
 * Constructor
 * Initializes the vector of instruments as empty
 */
InstrumentRepository::InstrumentRepository() {
    this->instruments = vector<Instrument*>();
}

/***
 * Destructor
 */
 /*
InstrumentRepository::~InstrumentRepository() {
    for(auto & instrument : instruments){
        delete instrument;
    }
}
  */

/***
 * Overload for insertion operator
 * Uses function getAllInfo from domain
 */
ostream &operator<<(ostream &o, const InstrumentRepository& instrumentRepository) {
    for(auto & instrument : instrumentRepository.instruments)
    {
        o<<instrument->getAllInfo()<<"\n";
    }
    return o;
}

/***
 * Adds an instrument to the repository
 * Also adds "R" to the undo stack (remove symbol)
 * @param instrument - given instrument
 */
void InstrumentRepository::AddInstrument(Instrument *instrument, unsigned int index) {
    if(index < 0 || index > this->instruments.size())
    {
        //std::cout<<instrument->getAllInfo()<<index<<"\n\n";
        delete instrument;
        throw std::exception();
    }
    else if(index == this->instruments.size())
        this->instruments.push_back(instrument);
    else
         this->instruments.insert(this->instruments.begin() + index, instrument);
}

/***
 * Removes instrument at index from repository
 * Also adds the instrument to the undo stack so we can add it back if we undo
 * Throws exception if index out of range
 * @param index - given index
 */
void InstrumentRepository::RemoveInstrument(unsigned int index) {
    if(index < 0 || index >= this->instruments.size())
        throw std::exception();
    auto x = this->instruments[index];
    this->instruments.erase(this->instruments.begin() + index);
    delete x;
}

/***
 * Edit instrument at index and replace old values with new ones from the vector given as parameter
 * @param index - given index
 * @param newValues - vector of new values to replace
 */
void InstrumentRepository::EditInstrument(unsigned int index, vector<string> newValues) {
    if(index < 0 || index >= this->instruments.size())
        throw std::exception();

    this->instruments[index]->editAllInfo(std::move(newValues));
}

/***
 * Loads a data from a file with a given name and adds every instrument to the repository
 * @param fileName - given file name
 */
void InstrumentRepository::LoadData(const string& fileName) {
    std::ifstream csvFile;
    csvFile.open(current_path().parent_path().string() + "/Saves/" + fileName + ".csv");
    string line;
    while (csvFile >> line) {
        auto i = StringToInstrument(line);
        if(i != nullptr) {
            AddInstrument(i, this->instruments.size());
        }
    }
}

/***
 * Save data to a file with a given name so we can load it back later
 * @param fileName - given file name
 */
void InstrumentRepository::SaveData(const string& fileName) {
    std::ofstream csvFile;
    csvFile.open(current_path().parent_path().string() + "/Saves/" + fileName + ".csv" ,std::fstream::out);

    for(auto instrument : instruments){
        csvFile<<instrument->getAllInfo();
    }
}

/***
 * Transforms a string with the same format as the lines in a save file to an instrument
 * @param line - given string
 * @return - an instrument generated from the given string
 */
Instrument *InstrumentRepository::StringToInstrument(const string &line) {
    InstrumentsEnum instrumentsEnum;
    vector<string> row = StringToVector(line, instrumentsEnum);
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

/***
 * Transforms a string with values separated by comma with a vector of strings
 */
vector<string> InstrumentRepository::StringToVector(const string &line, InstrumentsEnum &instrumentsEnum) {
    vector<string> row;
    string word;
    stringstream s(line);
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
    return row;
}
