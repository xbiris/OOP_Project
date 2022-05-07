#ifndef OOPPROJECT_TESTS_H
#define OOPPROJECT_TESTS_H
#include "Repository.h"
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
};


#endif //OOPPROJECT_TESTS_H
