#include "fsm.h"
#include <stdlib.h>
#include <string.h>


int fsm__init(fsm_t *self) {

    self->base_state = NULL;
    self->cur_state_name = NULL;
    self->arg_num = 0;
    self->arg_value = NULL;

    return 0;

}

int fsm__execute_next_state(fsm_t *self) {

    fsm_state_t* tmp = self->base_state;
    if ((self->base_state==NULL) || (self->cur_state_name==NULL))
        return -1;
    while ((tmp->name != self->cur_state_name) && tmp != NULL)
        tmp = tmp->next;
    if (tmp==NULL)
        return -1;
    tmp->callback(self, self->arg_num, self->arg_value);

    return 0;

}


int fsm__run(fsm_t *self) {

    while (!fsm__execute_next_state(self))
        ;

    return 0;

}


int fsm__add_state(fsm_t *self, char *state, callback_f callback) {

    fsm_state_t* tmp = self->base_state;
    fsm_state_t* new_state = malloc(sizeof(fsm_t));
    while (tmp->next)
        tmp = tmp->next;
    new_state->name = state;
    new_state->callback = callback;
    new_state->next = NULL;
    tmp->next = new_state;

    return 0;

}


int fsm__remove_state(fsm_t *self, char *state) {

    if (!strcmp(state, "default"))
        return -1;
    fsm_state_t* to_del;
    fsm_state_t* tmp = self->base_state;
    while ((tmp->next != NULL) && (strcmp(tmp->next->name, state)))
        tmp = tmp->next;
    if (tmp == NULL)
        return -1;
    to_del = tmp->next;
    tmp->next = tmp->next->next;
    free(to_del);

    return 0;

}


int fsm__change_state(fsm_t *self, char *state, int num, void **arg) {

    fsm_state_t* tmp = self->base_state;
    while ((tmp != NULL) && (strcmp(tmp->name, state)))
        tmp = tmp->next;
    if (tmp == NULL)
        return -1;
    self->cur_state = tmp;
    self->cur_state_name = tmp->name;
    self->arg_num = num;
    self->arg_value = arg;

    return 0;

}


int fsm__add_default_state_function(fsm_t *self, callback_f callback) {

    self->base_state = malloc(sizeof(fsm_state_t));
    self->base_state->name = "default";
    self->base_state->callback = callback;
    self->base_state->next = NULL;
    self->cur_state = self->base_state;
    self->cur_state_name = self->base_state->name;

    return 0;

}


void fsm__kill(fsm_t *self) {

    fsm_state_t* tmp = self->base_state;
    fsm_state_t* to_del = tmp;
    while (tmp) {
        to_del = tmp;
        tmp = tmp->next;
        free(to_del);
    }
    self->cur_state = NULL;
    self->cur_state_name = NULL;
    self->base_state = NULL;

}






















































