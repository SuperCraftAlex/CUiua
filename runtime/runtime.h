//
// Created by alex on 10/14/23.
//

#ifndef CUIUA_RUNTIME_H
#define CUIUA_RUNTIME_H

#include <stddef.h>
#include <stdbool.h>

// runtime error
void rerror(char *fmt, ...);

struct stack;
typedef struct stack stack;

// function pointer
typedef void (*funptr)(stack *);

struct elem;
typedef struct elem elem;

typedef struct {
    elem **data;
    size_t len;
} arr;

typedef enum {
    NUMBER,
    ARRAY,
    FUNPTR
} elem_type;

char *type_to_str(elem_type type);

struct elem {
    union {
        double number;
        arr array;
        funptr ptr;
    } data;
    elem_type type;
};

struct stack{
    elem **data;
    size_t nextpos;
    size_t alloc;
};

// initializes the runtime
void initrt();

// stops the runtime
void stoprt();

// allocates a new element
elem *new_elem(elem_type type);

// frees a element
void free_elem(elem *e);

// starts a array literal
void new_array(stack *s);

// ends a array literal
void end_array(stack *s);

// pushes a array onto the stack
void push_array(stack *s, arr array);

// pushes a number as a one dimensional array
void push_number(stack *s, double num);

// pushes a element onto the stack
void push(stack *s, elem *e);

bool has_next(stack *s);

// pops a element from the stack
elem *pop(stack *s);

// peeks at the top element on the stack
elem *peek(stack *s);

// calls the top element on the stack as a function
void call(stack *s);

// pushes a function pointer onto the stack
void push_addr(stack *s, funptr ptr);

// duplicates the top element on the stack
void dup(stack *s);

// swaps the top two elements on the stack
void swap(stack *s);

// duplicate the second-to-top value to the top of the stack
void over(stack *s);

// initializes a stack
void sinit(stack *s);

// frees a stack
void sfree(stack *s);

// element to string
char *etostr(elem *e);

// prints the whole stack
void sdump(stack *s);

// take the first n elements from an array
void take(stack *s);

// drop the first n elements from an array
void drop(stack *s);

// rotates an array by n elements
void rot(stack *s);

// reverses an array
void rev(stack *s);

// deshapes an array (makes the array one-dimensional)
void deshape(stack *s);

// checks if two arrays are the same
void match(stack *s);

// joins two arrays end-to-end
void join(stack *s);

// select elements from an array
// (the first element on the stack is a array of indecies)
// (the second element on the stack is the array to select from)
// (the result is pushed onto the stack)
void select_op(stack *s);

// gets element from an array at a index
void pick(stack *s);

// indexof   [x] [arr]  ->  [index]
// if x is a number, it returns the index of that number in the array (or -1 if it is not in the array)
// if x is an array, it does the indexof operation for each element in the array and returns a array of the resulting indecies
void indexof(stack *s);

// member   [x] [arr]  ->  [index]
// if x is a number, it returns true if that number is in the array
// if x is an array, it does the member operation for each element in the array and returns a array of the resulting booleans
void member(stack *s);

// returns the shape of an array (if it has a shape)
void shape(stack *s);

// repeats the given function n times
void repeat(stack *s);

// changes the shape of a flat array
// first arg: shape (array)
// second arg: array
void reshape(stack *s);

// executes the given function for each element in an array and returns a array of the results
void each(stack *s);

// adds the top two elements on the stack
void add(stack *s);

// subtracts the top two elements on the stack
void sub(stack *s);

// divides the top two elements on the stack
void div_op(stack *s);

// multiplies the top two elements on the stack
void mul(stack *s);

bool elems_equal(elem *a, elem *b);

elem *eclone(elem *e);

#endif //CUIUA_RUNTIME_H
