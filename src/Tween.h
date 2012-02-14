
#ifndef TWEEN_H
#define TWEEN_H

#include <stdlib.h>
#include "Types.h"
#include "IClock.h"
#include "Ticker.h"
#include "ITweenForm.h"

class Tween : public Ticker {

    public:
        Tween(IClock *clock, ICompleter *completer, ITweenForm *form, Uint32 duration);
        ~Tween();
        void start   (Uint32 now);
        void stop    ();
        void pause   (Uint32 now);
        void resume  (Uint32 now);
    protected:
        void on_tick (Uint32 now);
    private:
        ITweenForm  *form;
        Uint32       duration;
        Uint32       cycle_start_time;
        Uint32       last_cycle_complete_time;
        Uint32       pause_start_time;
        Uint32       total_pause_time;

 
};

#endif