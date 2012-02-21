
#include <stdlib.h>
#include <iostream>
#include <set>
#include "Timeline.h"
#include "LinearTweenForm.h"
#include "PathTweenForm.h"

using namespace std;

typedef LinearTweenForm<int  ,1> LinearIntForm;
typedef LinearTweenForm<float,1> LinearFloatForm;

Timeline::Timeline() : tickers() {
}

Timeline::~Timeline() {
    for (set<ITicker*>::iterator it = tickers.begin(); it != tickers.end(); it++)
        (*it)->stop();
}

void Timeline::register_ticker(ITicker *ticker) {
    tickers.insert(ticker);
}

void Timeline::unregister_ticker(ITicker *ticker) {
    tickers.erase(ticker);
}

void Timeline::tick(Uint32 now) {
    for (set<ITicker*>::iterator it = tickers.begin(); it != tickers.end(); it++)
        (*it)->tick(now);
}

Tween *Timeline::build_int_tween(IProxy<int,1> *proxy, ICompleter *completer,
                                 int duration, int from, int to, int ease_type,
                                 CycleControl *control) {
    Vector1i from_v = { {from} };                 
    Vector1i to_v   = { {to} };                 
    LinearIntForm *form = new LinearIntForm(proxy, from_v, to_v);
    return new Tween(this, completer, form, duration, ease_type, control);
}

Tween *Timeline::build_float_tween(IProxy<float,1> *proxy, ICompleter *completer,
                                   int duration, float from, float to, int ease_type,
                                   CycleControl *control) {
    Vector1f from_v = { {from} };                 
    Vector1f to_v   = { {to} };                 
    LinearFloatForm *form = new LinearFloatForm(proxy, from_v, to_v);
    return new Tween(this, completer, form, duration, ease_type, control);
}

Tween *Timeline::build_path_tween(IProxy<int,2> *proxy, ICompleter *completer,
                                  int duration, IPath *path, int ease_type,
                                  CycleControl *control) {
    PathTweenForm *form = new PathTweenForm(proxy, path);
    return new Tween(this, completer, form, duration, ease_type, control);
}
