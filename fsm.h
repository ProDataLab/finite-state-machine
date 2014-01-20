#pragma once


typedef struct fsm_t fsm_t;

typedef struct fsm_state_t fsm_state_t;

typedef void (*callback_f)(fsm_t*, int, void**);



struct fsm_state_t {

    char*           name;
    callback_f      callback;
    fsm_state_t*    next;

};



struct fsm_t {

    fsm_state_t*        base_state;
    fsm_state_t*        cur_state;
    char*               cur_state_name;
    int                 arg_num;
    void**              arg_value;

};


int fsm__init(fsm_t* self);

int fsm__run(fsm_t* self);

int fsm__execute_next_state(fsm_t* self);

int fsm__add_state(fsm_t* self, char* state, callback_f callback);

int fsm__add_default_state_function(fsm_t* self, callback_f callback);

int fsm__remove_state(fsm_t* self, char* state);

int fsm__change_state(fsm_t* self, char* state, int num, void** arg);

void fsm__kill(fsm_t* self);






























