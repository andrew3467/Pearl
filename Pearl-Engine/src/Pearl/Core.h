//
// Created by Andrew Graser on 2/5/2024.
//

#ifndef PEARL_CORE_H
#define PEARL_CORE_H


#define BIT(x) (1 << x)

#define PRL_ASSERT(x, ...) {if(!(x)) {PRL_ERROR("Assertion failed: {0}", __VA_ARGS__);}}
#define PRL_CORE_ASSERT(x, ...) {if(!(x)) {PRL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);}}


#endif //PEARL_CORE_H
