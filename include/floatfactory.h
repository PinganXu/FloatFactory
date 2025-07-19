#pragma once

#include <cstdint>



namespace floatfactory {

/*
    implement of float factory:
    1. software implement: it will use built-in functions and has no detailed infomation
       about calculation, just for correct result and high performance!
    2. hardware implement: it will expose detailed information about the calculation which
       are same as rtl. 
*/
enum ff_imp {
    sw_imp = 0,
    hw_imp
};

typedef union {
    struct {
        uint32_t sign: 1;
        uint32_t exp : 8;
        uint32_t man : 23;
    } field;
    uint32_t value;
} fp32_t;

typedef union {
    struct {
        uint16_t sign: 1;
        uint16_t exp : 5;
        uint16_t man : 10;
    } field;
    uint16_t value;
} fp16_t;

typedef union {
    struct {
        uint16_t sign: 1;
        uint16_t exp : 8;
        uint16_t man : 7;
    } field;
    uint16_t value;
} bf16_t;

typedef union {
    struct {
        uint8_t sign: 1;
        uint8_t exp : 4;
        uint8_t man : 3;
    } field;
    uint8_t value;
} fp8_t;

typedef union {
    struct {
        uint8_t sign: 1;
        uint8_t exp : 5;
        uint8_t man : 2;
    } field;
    uint8_t value;
} bf8_t;

namespace swimp {

}  // namespace floatfactory::swimp

namespace hwimp {

}  // namespace floatfactory::hwimp

}  // namespace floatfactory
