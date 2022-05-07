#include <iostream>
#include "Repository.h"
#include "Tests.h"

int main() {
    Tests::TestAll();
    InstrumentRepository repository;
    repository.LoadData("data");
}
