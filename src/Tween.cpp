
#include <stdlib.h>
#include <iostream>
#include "Tween.h"

Tween::Tween(IClock *clock, ICompleter *completer,
             ITweenForm *form, Uint32 duration) :
    Ticker(clock, completer),
    form(form),
    duration(duration),
    cycle_start_time(0),
    last_cycle_complete_time(0),
    pause_start_time(0),
    total_pause_time(0) {
}

Tween::~Tween() {
    delete form;
}

void Tween::start(Uint32 now) {
    Ticker::start(now);
    cycle_start_time = now;
    last_cycle_complete_time = 0;
    form->start(0);
}

void Tween::stop() {
    Ticker::stop();
    last_cycle_complete_time =
        cycle_start_time + duration + total_pause_time;
    total_pause_time = 0;
}

void Tween::pause(Uint32 now) {
    Ticker::pause(now);
    pause_start_time = now;
}

void Tween::resume(Uint32 now) {
    Ticker::resume(now);
    total_pause_time += now - pause_start_time;
    pause_start_time = 0;
}

void Tween::on_tick(Uint32 now) {
    bool is_complete = 0;
    Uint32 elapsed = now - cycle_start_time - total_pause_time;

    if (elapsed >= duration) {
        is_complete = 1;
        elapsed = duration;
    }
    float t_normal = (float) elapsed / duration;
    form->tick(t_normal);

    if (!is_active() || !is_complete) { return; }

    stop();
    on_complete(last_cycle_complete_time);
}

