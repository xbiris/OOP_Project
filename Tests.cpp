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
    TestFilter();
    TestStringToInstrument();

    TestGuitar();
    TestViolin();
    TestDrumKit();
    TestFlute();
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
        repository.AddInstrument(v, 0);
        repository.AddInstrument(v2, 1);
        repository.AddInstrument(g, 2);
        repository.AddInstrument(g1, 3);
        repository.AddInstrument(g2, 4);
        assert(repository.getInstruments().at(1)->getPrice() == 2);
    }
    catch (...){
        assert(false);
    }
    for(auto instrument : repository.getInstruments()){
        delete instrument;
    }
}

void Tests::TestRepoRemove() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto g1 = new Violin(2,2,false,3,1);
    auto g2 = new DrumKit(5,1,false,5,true);
    auto v = new Flute(1,2,true, "wood");
    auto v2 = new Violin(1,2,false,4,5);
    repository.AddInstrument(v, 0);
    repository.AddInstrument(v2, 1);
    repository.AddInstrument(g, 2);
    repository.AddInstrument(g1, 3);
    repository.AddInstrument(g2, 4);
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
    for(auto instrument : repository.getInstruments()){
        delete instrument;
    }
}

void Tests::TestRepoEdit() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    repository.AddInstrument(g, 0);
    repository.AddInstrument(v, 1);
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
    for(auto instrument : repository.getInstruments()){
        delete instrument;
    }
}

void Tests::TestRepoSaveLoad() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,false,1,false);
    auto g1 = new Guitar(2,2,false,3,true);
    auto g2 = new DrumKit(5,1,false,5,true);
    auto v = new Violin(1,2,false,4,5);
    auto v2 = new Flute(1,2,false,"wood");
    repository.AddInstrument(v, 0);
    repository.AddInstrument(v2, 1);
    repository.AddInstrument(g, 2);
    repository.AddInstrument(g1, 3);
    repository.AddInstrument(g2, 4);
    repository.SaveData("test");
    InstrumentRepository repository1;
    repository1.LoadData("test");

    assert(repository1.getInstruments().at(1)->getAllInfo() == v2->getAllInfo());
    assert(repository1.getInstruments().at(3)->getAllInfo() == g1->getAllInfo());
    assert(repository1.getInstruments().at(4)->getAllInfo() == g2->getAllInfo());

    for(auto instrument : repository.getInstruments()){
        delete instrument;
    }
    for(auto instrument : repository1.getInstruments()){
        delete instrument;
    }
}

void Tests::TestRepoUndoRedo() {
    InstrumentRepository repository;
    Controller c(repository);
    c.Undo();
    c.Redo();
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    auto d = new DrumKit(3,1,false,5,true);
    auto f = new Flute(4,2,true, "wood");
    c.AddInstrument(g, 0);
    c.AddInstrument(v, 1);
    c.AddInstrument(d, 2);
    c.AddInstrument(f, 3);
    assert(c.getInstruments().size() == 4);
    c.Undo();
    assert(c.getInstruments().size() == 3);
    (c.getInstruments().at(2)->getId() == 3);
    c.Redo();
    assert(c.getInstruments().size() == 4);
    assert(c.getInstruments().at(3)->getId() == 4);
    c.RemoveInstrument(3);
    c.Undo();
    assert(c.getInstruments().size() == 4);
    assert(c.getInstruments().at(3)->getId() == 4);
    c.Redo();
    assert(c.getInstruments().size() == 3);
    assert(c.getInstruments().at(2)->getId() == 3);
    for(auto instrument : c.getInstruments()){
        delete instrument;
    }
}

void Tests::TestRepoGet() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    auto d = new DrumKit(3,1,false,5,true);
    auto f = new Flute(4,2,true, "wood");
    repository.AddInstrument(g,0);
    repository.AddInstrument(v,1);
    repository.AddInstrument(d,2);
    repository.AddInstrument(f,3);
    assert(repository.getInstruments().at(0)->getId() == 1);
    assert(repository.getInstruments().at(1)->getId() == 2);
    assert(repository.getInstruments().at(2)->getId() == 3);
    assert(repository.getInstruments().at(3)->getId() == 4);
    for(auto instrument : repository.getInstruments()){
        delete instrument;
    }
}

void Tests::TestOut() {
    InstrumentRepository repository;
    auto g = new Guitar(1,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    repository.AddInstrument(g,0);
    repository.AddInstrument(v,1);
    std::cout<<repository;
    for(auto instrument : repository.getInstruments()){
        delete instrument;
    }
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

void Tests::TestFilter() {
    InstrumentRepository repository;
    Controller c(repository);
    auto g = new Guitar(1,1,true,1,true);
    auto g1 = new Guitar(22,1,true,1,true);
    auto v = new Violin(2,2,false,3,1);
    auto d = new DrumKit(3,1,false,5,true);
    auto f = new Flute(4,2,true, "wood");
    c.AddInstrument(g,0);
    c.AddInstrument(g1,1);
    c.AddInstrument(v,2);
    c.AddInstrument(d,3);
    c.AddInstrument(f,4);

    auto x = c.FilterByType(Guitar_);
    assert(x.getInstruments().size() == 2);
    assert(x.getInstruments().at(1)->getId() == 22);

    auto y = c.FilterByType(Violin_);
    assert(y.getInstruments().size() == 1);

    auto z = c.FilterByType(DrumKit_);
    assert(z.getInstruments().size() == 1);

    auto t = c.FilterByType(Flute_);
    assert(t.getInstruments().size() == 1);

    for(auto instrument : c.getInstruments()){
        delete instrument;
    }
}

void Tests::TestGuitar() {
    Guitar g(1,1,1,1,1);
    Guitar g1(g);
    assert(g.getAllInfo() == g1.getAllInfo());
}

void Tests::TestViolin() {
    Violin v(1,1,1,1,1);
    Violin v1(v);
    assert(v.getAllInfo() == v1.getAllInfo());

    vector<string> ve = { "2", "2", "2", "2", "2"};
    v.editAllInfo(ve);
    assert(v.getId() == 2);
}

void Tests::TestDrumKit() {
    DrumKit d(1,1,1,1,1);
    DrumKit d1(d);
    assert(d.getAllInfo() == d1.getAllInfo());

    vector<string> ve = { "2", "2", "2", "2", "2"};
    d.editAllInfo(ve);
    assert(d.getId() == 2);
}

void Tests::TestFlute() {
    Flute f(1,1,1,"wood");
    Flute f1(f);
    assert(f.getAllInfo() == f1.getAllInfo());

    vector<string> ve = { "2", "2", "2", "metal"};
    f.editAllInfo(ve);
    assert(f.getMaterial() == "metal");
}
