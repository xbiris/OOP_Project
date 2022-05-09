#ifndef OOPPROJECT_UI_H
#define OOPPROJECT_UI_H
#include "Controller.h"
#include <limits>

using std::cin;
using std::cout;

class UI {
public:
    UI();
    ~UI();
    void StartGame();
    void DisplayMenu();
    bool ReadOption();
    Instrument* ReadInstrument();
    static Instrument* ReadGuitar();
    static Instrument* ReadViolin();
    static Instrument* ReadDrumKit();
    static Instrument* ReadFlute();
private:
    Controller controller;
};


UI::UI() {
    StartGame();
}


UI::~UI() {
    for(auto instrument : this->controller.getRepository().getInstruments()){
        delete instrument;
    }
}


void UI::StartGame() {
    controller = Controller();
    controller.LoadData("data");
    DisplayMenu();
}

void UI::DisplayMenu() {
    bool isOn = true;
    while(isOn) {
        string message = "Welcome!\n";
        message += "1. Add instrument\n";
        message += "2. Remove instrument\n";
        message += "3. Edit instrument\n";
        message += "4. Filter\n";
        message += "5. Undo\n";
        message += "6. Redo\n";
        message += "7. Print repository\n";
        message += "8. Exit\n";

        cout<<message;

        isOn = ReadOption();
    }
    controller.SaveData("data");
}

bool UI::ReadOption() {
    int option;

    if(!(cin>>option)){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout<<"Please input an integer for the option.\n";
        return true;
    }

    unsigned int index;
    switch (option) {
        case 1: {
            auto instrument = ReadInstrument();
            cout<<"Index: ";
            cin>>index;
            if (instrument != nullptr) {
                try{
                    controller.AddInstrument(instrument, index);
                }
                catch (...){
                    cout<<"Something went wrong";
                }
            } else {
                cout << "Invalid input!\n";
            }
            break;
        }
        case 2: {
            cout << "Index:";
            cin >> index;
            try {
                controller.RemoveInstrument(index);
            }
            catch (...) {
                cout << "Wrong index!\n";
            }
            break;
        }
        case 3: {
            cout << "Index:";
            cin >> index;
            auto instrument = ReadInstrument();
            try {
                InstrumentsEnum instrumentsEnum;
                controller.EditInstrument(index,
                                          InstrumentRepository::StringToVector(
                                                  instrument->getAllInfo(),
                                                  instrumentsEnum));
            }
            catch (...) {
                cout<<"Something went wrong";
            }
            delete instrument;
            break;
        }
        case 4: {
            cout << "Choose an instrument\n";
            cout << "G - Guitar\n";
            cout << "V - Violin\n";
            cout << "D - Drum Kit\n";
            cout << "F - Flute\n";

            string opt;
            cin >> opt;

            try{
                if (opt == "G") {
                    cout << controller.FilterByType(Guitar_);
                } else if (opt == "V") {
                    cout << controller.FilterByType(Violin_);
                } else if (opt == "D") {
                    cout << controller.FilterByType(DrumKit_);
                } else if (opt == "F") {
                    cout << controller.FilterByType(Flute_);
                } else {
                    cout << "Wrong input";
                }
            }
            catch (...)
            {
                cout<<"Something went wrong";
            }
            break;
        }
        case 5:
            try{
                controller.Undo();
            }
            catch (...){
                cout<<"Something went wrong";
            }
            break;
        case 6:
            try{
                controller.Redo();
            }
            catch (...){
                cout<<"Something went wrong";
            }
            break;
        case 7:
            try{
                cout<<controller.getRepository();
            }
            catch (...) {
                cout<<"Something went wrong";
            }
            break;
        case 8:
            return false;
        default:
            cout<<"Invalid option.\n";
    }

    return true;
}

Instrument *UI::ReadInstrument() {
    cout<<"Choose an instrument\n";
    cout<<"G - Guitar\n";
    cout<<"V - Violin\n";
    cout<<"D - Drum Kit\n";
    cout<<"F - Flute\n";

    string option;
    cin>>option;

    if(option == "G"){
        return ReadGuitar();
    }
    else if(option == "V"){
        return ReadViolin();
    }
    else if(option == "D"){
        return ReadDrumKit();
    }
    else if(option == "F"){
        return ReadFlute();
    }
    else{
        return nullptr;
    }
}

Instrument *UI::ReadGuitar() {
    int id;
    float price;
    bool acoustic;
    int nrStrings;
    bool steelStrings;
    cout<<"Id:";
    cin>>id;
    cout<<"Price:";
    cin>>price;
    cout<<"Acoustic?:";
    cin>>acoustic;
    cout<<"Nr Strings:";
    cin>>nrStrings;
    cout<<"Steel Strings?:";
    cin>>steelStrings;
    return new Guitar(id, price, acoustic, nrStrings, steelStrings);
}

Instrument *UI::ReadViolin() {
    int id;
    float price;
    bool acoustic;
    int nrStrings;
    int size;
    cout<<"Id:";
    cin>>id;
    cout<<"Price:";
    cin>>price;
    cout<<"Acoustic?:";
    cin>>acoustic;
    cout<<"Nr Strings:";
    cin>>nrStrings;
    cout<<"Size:";
    cin>>size;
    return new Violin(id, price, acoustic, nrStrings, size);
}

Instrument *UI::ReadDrumKit() {
    int id;
    float price;
    bool acoustic;
    int nrPieces;
    bool doubleBass;
    cout<<"Id:";
    cin>>id;
    cout<<"Price:";
    cin>>price;
    cout<<"Acoustic?:";
    cin>>acoustic;
    cout<<"Nr Pieces:";
    cin>>nrPieces;
    cout<<"Double Bass?:";
    cin>>doubleBass;
    return new DrumKit(id, price, acoustic, nrPieces, doubleBass);
}

Instrument *UI::ReadFlute() {
    int id;
    float price;
    bool acoustic;
    string material;
    cout<<"Id:";
    cin>>id;
    cout<<"Price:";
    cin>>price;
    cout<<"Acoustic?:";
    cin>>acoustic;
    cout<<"Material:";
    cin>>material;
    return new Flute(id, price, acoustic, material);
}

#endif //OOPPROJECT_UI_H
