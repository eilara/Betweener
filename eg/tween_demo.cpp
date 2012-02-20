
#include <iostream>
#include "Types.h"
#include "Vector.h"
#include "VectorTypes.h"
#include "easing.h"
#include "CycleControl.h"
#include "IProxy.h"
#include "ICompleter.h"
#include "Ticker.h"
#include "IClock.h"
#include "Timeline.h"
#include "Ticker.h"
#include "LinearTweenForm.h"
#include "Tween.h"
#include "tap_lib.h"

using namespace std;

typedef LinearTweenForm<int,2> LinearTweenForm2i;

// -----------------------------------------------------------------------------

void test_Vector() { // 9 tests
    diag("Vector");
    Vector<int,3> foo_1 = { { 1, 3, 5 } };
    Vector<int,3> foo_2 = { { 1, 3, 5 } };
    Vector<int,3> bar_1 = { { 2, 4, 6 } };

    ok(foo_1.size() == 3, "foo_1.size");
    ok(foo_1[1] == 3, "foo_1[1]");
    ok(foo_1 == foo_2, "foo_1 == foo_2");
    ok(foo_1 != bar_1, "foo_1 != bar_1");
    ok(!(foo_1 == bar_1), "!(foo_1 == bar_1)");
    ok(!(foo_1 != foo_2), "!(foo_1 != foo_2)");

    foo_1[0] = 2;
    foo_1[1] = 4;
    foo_1[2] = 6;
    ok(foo_1 == bar_1, "after changing foo_1: foo_1 == bar_1");
    ok(foo_1 != foo_2, "after changing foo_1: foo_1 != foo_2");

    Vector<int,3> sum = foo_2 + bar_1;
    Vector<int,3> expected_sum = { { 3, 7, 11 } };
    ok(sum == expected_sum, "operator +");
}

// -----------------------------------------------------------------------------

class MockITicker : public ITicker {
    public:
        int tick_count;
        Uint32 last_now;
        MockITicker() : tick_count(0), last_now(0) {}
        ~MockITicker() {}
        void tick(Uint32 now) {
            tick_count++;
            last_now = now;
        }
        void stop() {}
};

// -----------------------------------------------------------------------------

void test_Timeline() { // 4 tests
    diag("Timeline");

    Timeline timeline;
    MockITicker ticker;
    timeline.register_ticker(&ticker);

    timeline.tick(1);
    ok(ticker.tick_count == 1, "tick 1 count");
    ok(ticker.last_now == 1, "tick 1 now");

    timeline.tick(3);
    ok(ticker.tick_count == 2, "tick 3 count");
    ok(ticker.last_now == 3, "tick 3 now");

    timeline.unregister_ticker(&ticker);
}

// -----------------------------------------------------------------------------

class MockTicker : public Ticker {
    public:
        int tick_count;
        MockTicker(IClock *clock, ICompleter *completer) :
            Ticker(clock, completer), tick_count(0) {}
        ~MockTicker() {}
        void on_tick(Uint32 now) { tick_count++; }
};

// -----------------------------------------------------------------------------

class MockCompleter : public ICompleter {
    public:
        int last_complete_time;
        MockCompleter() : last_complete_time(0) {}
        ~MockCompleter() {}
        void animation_complete(Uint32 now) { last_complete_time = now; }
};

// -----------------------------------------------------------------------------


void test_Ticker() { // 4 tests
    diag("Ticker");

    Timeline timeline;
    MockCompleter *completer = new MockCompleter();
    MockTicker ticker(&timeline, completer);

    ticker.start(1);
    timeline.tick(2);
    ok(ticker.tick_count == 1, "tick 1 count");

    ticker.stop();
    timeline.tick(4);
    ok(ticker.tick_count == 1, "tick 2 count");

    ticker.start(5);
    timeline.tick(6);
    ok(ticker.tick_count == 2, "tick 3 count");

    ticker.stop();
    timeline.tick(48);
    ok(ticker.tick_count == 2, "tick 4 count");

}

// -----------------------------------------------------------------------------

class MockProxy : public IProxy<int,2> {
    public:
        Vector2i last_value;
        MockProxy() : last_value() {}
        ~MockProxy() {}
        void update(Vector2i& v) { last_value = v; }
};

// -----------------------------------------------------------------------------

void test_LinearTweenForm() { // 4 tests
    diag("LinearTweenForm");
    Vector2i      from = { {   0,   0} };
    Vector2i      to   = { {1000, 500} };
    MockProxy *proxy   = new MockProxy();
    LinearTweenForm2i form(proxy, from, to);

    form.start(0);
    ok(proxy->last_value[0] == 0, "start 0.0");
    form.tick(0.1);
    ok(proxy->last_value[1] == 50, "tick 0.1");
    form.tick(0.900001);
    ok(proxy->last_value[0] == 900, "tick 0.9");
    form.tick(1);
    ok(proxy->last_value[1] == 500, "tick 1.0");
}

// -----------------------------------------------------------------------------

void test_Tween() { // 2 tests
    diag("Tween");
    Vector2i           from  = { { 10,  10} };
    Vector2i           to    = { {110, 110} };
    MockProxy         *proxy = new MockProxy();
    MockCompleter *completer = new MockCompleter();
    LinearTweenForm2i  *form = new LinearTweenForm2i(proxy, from, to);
    CycleControl    *control = new CycleControl(false, 1, false, false);
    Timeline timeline;
    Tween tween(&timeline, completer, form, 10, EaseLinear, control);

    tween.start(1);
    timeline.tick(3);

    ok(proxy->last_value[1] == 30, "tick 3");

    timeline.tick(12);
    ok(completer->last_complete_time == 11, "complete");
}

// -----------------------------------------------------------------------------

class MockProxy1i : public IProxy<int,1> {
    public:
        Vector1i last_value;
        MockProxy1i() : last_value() {}
        ~MockProxy1i() {}
        void update(Vector1i& v) { last_value = v; }
};

// -----------------------------------------------------------------------------

void test_tween_int() { // 1 test
    diag("tween_int");
    MockProxy1i       *proxy = new MockProxy1i();
    MockCompleter *completer = new MockCompleter();
    CycleControl    *control = new CycleControl(false, 1, false, false);
    Timeline timeline;
    Tween *tween = timeline.build_int_tween
        (proxy, completer, 10, 1, 100, EaseLinear, control);

    tween->start(0);
    timeline.tick(5);

    ok(proxy->last_value[0] == 50, "tick 0");

    delete tween;
}

// -----------------------------------------------------------------------------

int main() {
    plan_tests(9 + 4 + 4 + 4 + 2 + 1);

    test_Vector();
    test_Timeline();
    test_Ticker();
    test_LinearTweenForm();
    test_Tween();
    test_tween_int();

    return 0;
}

