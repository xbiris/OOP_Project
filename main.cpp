#include <iostream>
#include "Repository.h"

int main() {
    InstrumentRepository repository;
    repository.LoadData();
    auto v = new Violin(1,2,false,4,5);
    auto v2 = new Violin(1,2,false,4,5);
    repository.AddInstrument(v);
    repository.AddInstrument(v2);
    std::cout<<repository;
    repository.Undo();
    std::cout<<"UNDO: ";
    std::cout<<repository;
    repository.Undo();
    std::cout<<"UNDO: ";
    std::cout<<repository;

    repository.Redo();
    std::cout<<"REDO: ";
    std::cout<<repository;
    repository.Redo();
    std::cout<<"REDO: ";
    std::cout<<repository;

    repository.Undo();
    std::cout<<"UNDO: ";
    std::cout<<repository;

    repository.RemoveInstrument(repository.getInstruments().size()-1);
    std::cout<<"REMOVE: ";
    std::cout<<repository;

    repository.Undo();
    std::cout<<"UNDO: ";
    std::cout<<repository;

    repository.Redo();
    std::cout<<"REDO: ";
    std::cout<<repository;
}
