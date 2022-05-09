#ifndef OOPPROJECT_TESTS_H
#define OOPPROJECT_TESTS_H
#include "Repository.h"
#include "Controller.h"
#include "cassert"

class Tests {
public:
    static void TestAll();

    static void TestRepoConstructor();
    static void TestRepoAdd();
    static void TestRepoRemove();
    static void TestRepoEdit();
    static void TestRepoSaveLoad();
    static void TestRepoUndoRedo();
    static void TestRepoGet();
    static void TestOut();
    static void TestStringToInstrument();
    static void TestFilter();

    static void TestGuitar();
    static void TestViolin();
    static void TestDrumKit();
    static void TestFlute();
};


#endif //OOPPROJECT_TESTS_H
