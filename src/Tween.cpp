
#include <stdlib.h>
#include <iostream>
#include "Tween.h"
#include "easing.h"

Tween::Tween(IClock *clock, ICompleter *completer,
             ITweenForm *form, Uint32 duration, int ease_type,
             CycleControl *control) :
    Ticker(clock, completer),
    form(form),
    control(control),
    duration(duration),
    cycle_start_time(0),
    last_cycle_complete_time(0),
    pause_start_time(0),
    total_pause_time(0),
    ease_func(Get_Ease(ease_type)) {
}

Tween::~Tween() {
    delete form;
    delete control;
}

void Tween::start(Uint32 now) {
    Ticker::start(now);
    cycle_start_time = now;
    last_cycle_complete_time = 0;
    control->animation_started();
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
    float eased    = ease_func(t_normal);
    form->tick(eased);

    if (!is_active() || !is_complete) { return; }

    control->cycle_complete();

    stop();
    on_complete(last_cycle_complete_time);
}

