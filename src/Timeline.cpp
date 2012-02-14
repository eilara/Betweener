
#include <stdlib.h>
#include <iostream>
#include <set>
#include "Timeline.h"
#include "LinearTweenForm.h"

using namespace std;

typedef LinearTweenForm<int,1> LinearIntForm;
typedef LinearTweenForm<float,1> LinearFloatForm;

Timeline::Timeline() : tickers() {
    for (set<ITicker*>::iterator it = tickers.begin(); it != tickers.end(); it++)
        (*it)->stop();
}

Timeline::~Timeline() {
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

// build 1D int tween
Tween *Timeline::tween_int(IProxy<int,1> *proxy, ICompleter *completer,
                 int duration, int from, int to) {
    Vector1i from_v = { {from} };                 
    Vector1i to_v   = { {to} };                 
    LinearIntForm *form = new LinearIntForm(proxy, from_v, to_v);
    return new Tween(this, completer, form, duration);
}
