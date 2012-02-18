
#ifndef TIMELINE_H
#define TIMELINE_H

#include <stdlib.h>
#include <set>
#include "Types.h"
#include "VectorTypes.h"
#include "IClock.h"
#include "IProxy.h"
#include "ICompleter.h"
#include "Tween.h"

class Timeline : public IClock {

    public:
        Timeline();
        ~Timeline();
        void   register_ticker(ITicker *ticker);
        void unregister_ticker(ITicker *ticker);
        void tick(Uint32 now);

        Tween   *build_int_tween(IProxy<int,1> *proxy, ICompleter *completer,
                                 int duration, int from, int to);
        Tween *build_float_tween(IProxy<float,1> *proxy, ICompleter *completer,
                                 int duration, float from, float to);
    private:
        std::set<ITicker*> tickers;
       

};

#endif
