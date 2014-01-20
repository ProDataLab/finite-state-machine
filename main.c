#include "fsm.h"
#include <stdio.h>


void abc(fsm_t* self, int val, void** arg) {

    printf("%d\n", val);
    printf("%s\n", self->cur_state_name);
    fsm__change_state(self, "hello", 0, NULL);

}


void pqr(fsm_t* self, int val, void** arg) {

    printf("%d\n", val);
    printf("%s\n", self, self->cur_state_name);
    fsm__change_state(self, "default", 0, NULL);

}


void xyz(fsm_t* self, int val, void** arg) {


    printf("%d\n", val);
    printf("%s\n", self->cur_state_name);
    fsm__change_state(self, "qwerty", 0, NULL);
}


int main(void) {

    fsm_t fsm;
    fsm__init(&fsm);
    fsm__add_default_state_function(&fsm, abc);
    fsm__add_state(&fsm, "qwerty", pqr);
    fsm__add_state(&fsm, "hello", xyz);

    fsm__run(&fsm);

    return 0;

}































