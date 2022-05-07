#include "Tests.h"

void Tests::TestAll() {
    TestRepoConstructor();
    TestRepoAdd();
    TestRepoRemove();
    TestRepoEdit();
    TestRepoSaveLoad();
    TestRepoUndoRedo();
    TestRepoGet();
    //TestOut();
    TestStringToInstrument();
}

void Tests::TestRepoConstructor() {
    InstrumentRepository repository;

    assert(repository.getInstruments().empty());
    try{
        auto a = repository.getInstruments().at(0);
        assert(false);
        a->getId();
    }
    catch (...){
        assert(true);
    }
}

void Tests::TestRepoAdd() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto g1 = new Violin(2,2,false,3,1);
    auto g2 = new DrumKit(5,1,false,5,true);
    auto v = new Flute(1,2,true, "wood");
    auto v2 = new Violin(1,2,false,4,5);
    try{
        repository.AddInstrument(v);
        repository.AddInstrument(v2);
        repository.AddInstrument(g);
        repository.AddInstrument(g1);
        repository.AddInstrument(g2);
        assert(repository.getInstruments().at(1)->getPrice() == 2);
    }
    catch (...){
        assert(false);
    }
}

void Tests::TestRepoRemove() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto g1 = new Violin(2,2,false,3,1);
    auto g2 = new DrumKit(5,1,false,5,true);
    auto v = new Flute(1,2,true, "wood");
    auto v2 = new Violin(1,2,false,4,5);
    repository.AddInstrument(v);
    repository.AddInstrument(v2);
    repository.AddInstrument(g);
    repository.AddInstrument(g1);
    repository.AddInstrument(g2);
    repository.RemoveInstrument(1);
    assert(repository.getInstruments().at(1)->getPrice() == 1);
    try{
        repository.RemoveInstrument(-1);
        repository.RemoveInstrument(50);
        assert(false);
    }
    catch (...){
        assert(true);
    }
}

void Tests::TestRepoEdit() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    repository.AddInstrument(g);
    repository.AddInstrument(v);
    vector<string> vector1 = {
            "2",
            "2",
            "0",
            "2",
            "1"
    };
    repository.EditInstrument(0, vector1);
    assert(repository.getInstruments().at(0)->getAcoustic() == false);
    assert(repository.getInstruments().at(0)->getPrice() == 2);
    assert(repository.getInstruments().at(0)->getId() == 2);

    try{
        repository.EditInstrument(2, vector1);
        repository.EditInstrument(-1, vector1);
        assert(false);
    }
    catch (...){
        assert(true);
    }
}

void Tests::TestRepoSaveLoad() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,false,1,false);
    auto g1 = new Guitar(2,2,false,3,true);
    auto g2 = new DrumKit(5,1,false,5,true);
    auto v = new Violin(1,2,false,4,5);
    auto v2 = new Flute(1,2,false,"wood");
    repository.AddInstrument(v);
    repository.AddInstrument(v2);
    repository.AddInstrument(g);
    repository.AddInstrument(g1);
    repository.AddInstrument(g2);
    repository.SaveData("test");
    InstrumentRepository repository1;
    repository1.LoadData("test");

    assert(repository1.getInstruments().at(1)->getAllInfo() == v2->getAllInfo());
    assert(repository1.getInstruments().at(3)->getAllInfo() == g1->getAllInfo());
    assert(repository1.getInstruments().at(4)->getAllInfo() == g2->getAllInfo());
}

void Tests::TestRepoUndoRedo() {
    InstrumentRepository repository;
    repository.Undo();
    repository.Redo();
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    auto d = new DrumKit(3,1,false,5,true);
    auto f = new Flute(4,2,true, "wood");
    repository.AddInstrument(g);
    repository.AddInstrument(v);
    repository.AddInstrument(d);
    repository.AddInstrument(f);
    assert(repository.getInstruments().size() == 4);
    repository.Undo();
    assert(repository.getInstruments().size() == 3);
    assert(repository.getInstruments().at(2)->getId() == 3);
    repository.Redo();
    assert(repository.getInstruments().size() == 4);
    assert(repository.getInstruments().at(3)->getId() == 4);
    repository.RemoveInstrument(3);
    repository.Undo();
    assert(repository.getInstruments().size() == 4);
    assert(repository.getInstruments().at(3)->getId() == 4);
    repository.Redo();
    assert(repository.getInstruments().size() == 3);
    assert(repository.getInstruments().at(2)->getId() == 3);
}

void Tests::TestRepoGet() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    auto d = new DrumKit(3,1,false,5,true);
    auto f = new Flute(4,2,true, "wood");
    repository.AddInstrument(g);
    repository.AddInstrument(v);
    repository.AddInstrument(d);
    repository.AddInstrument(f);
    assert(repository.getInstruments().at(0)->getId() == 1);
    assert(repository.getInstruments().at(1)->getId() == 2);
    assert(repository.getInstruments().at(2)->getId() == 3);
    assert(repository.getInstruments().at(3)->getId() == 4);

}

void Tests::TestOut() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    repository.AddInstrument(g);
    repository.AddInstrument(v);
    std::cout<<repository;
}

void Tests::TestStringToInstrument() {
    auto g = Guitar(1,1,true,1,true);
    auto v = Violin(2,2,false,3,1);
    auto d = DrumKit(3,1,false,5,true);

    auto g1= InstrumentRepository::StringToInstrument(g.getAllInfo());
    auto v1 = InstrumentRepository::StringToInstrument(v.getAllInfo());
    auto d1 = InstrumentRepository::StringToInstrument(d.getAllInfo());

    assert(g.getAllInfo() == g1->getAllInfo());
    assert(v.getAllInfo() == v1->getAllInfo());
    assert(d.getAllInfo() == d1->getAllInfo());

    delete g1;
    delete v1;
    delete d1;
}
