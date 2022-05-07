#include <iostream>
#include "UI.h"
#include "Tests.h"

int main() {
    Tests::TestAll();
    UI ui;
    ui.StartGame();
}
