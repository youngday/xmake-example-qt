#include "main.h"
#include "sqlite_orm/sqlite_orm.h"

#include <cassert>
using namespace sqlite_orm;

using std::cout;
using std::endl;

struct RapArtist {
    int id;
    std::string name;
};

using namespace std;

int database_create(void);
int sqlite_orm_app(void);

int sqlite_orm_app()
{

  LOG_S(INFO) << "sqlite orm  start ."<< "\n";
 database_create();
  return 0;
}

int database_create() {

    auto storage = make_storage(":memory:",
                                make_table("rap_artists",
                                           make_column("id", &RapArtist::id, primary_key()),
                                           make_column("name", &RapArtist::name)));
    cout << "in memory db opened" << endl;
    storage.sync_schema();

    assert(!storage.count<RapArtist>());

    storage.insert(RapArtist{-1, "The Weeknd"});

    storage.transaction([&] {
        storage.insert(RapArtist{-1, "Drake"});
        return true;
    });

    cout << "rap artists count = " << storage.count<RapArtist>() << endl;

    //  transaction also work in memory..
    storage.transaction([&] {
        storage.insert(RapArtist{-1, "Kanye West"});
        return false;
    });

    cout << "rap artists count = " << storage.count<RapArtist>() << " (no Kanye)" << endl;

    return 0;
}

