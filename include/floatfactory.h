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
        uint64_t sign: 1;
        uint64_t exp : 11;
        uint64_t man : 52;
    } field;
    uint64_t value;
    double   float_value;
} fp64_t;

typedef union {
    struct {
        uint32_t sign: 1;
        uint32_t exp : 8;
        uint32_t man : 23;
    } field;
    uint32_t value;
    float    float_value;
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

typedef union {
    struct {
        uint8_t sign: 1;
        uint8_t exp : 2;
        uint8_t man : 1;
        uint8_t reserved: 4;
    } field;
    uint8_t value;
} fp4_t;

namespace swimp {
    /* ===== fp32 arithmetic ===== */
    fp32_t fp32_add(fp32_t, fp32_t);
    fp32_t fp32_max(fp32_t, fp32_t);
    fp32_t fp32_min(fp32_t, fp32_t);

    /* ===== fp16 arithmetic ===== */
    fp16_t fp16_add(fp32_t, fp32_t);
    fp16_t fp16_max(fp16_t, fp16_t);
    fp16_t fp16_min(fp16_t, fp16_t);

    /* ===== bf16 arithmetic ===== */
    bf16_t bf16_add(bf16_t, bf16_t);
    bf16_t bf16_max(bf16_t, bf16_t);
    bf16_t bf16_min(bf16_t, bf16_t);

    /* ===== conversion ===== */
    fp32_t cvt_u64_to_fp32(uint64_t);
    fp32_t cvt_s64_to_fp32(int64_t);
    fp32_t cvt_u32_to_fp32(uint32_t);
    fp32_t cvt_s32_to_fp32(int32_t);
    fp32_t cvt_u16_to_fp32(uint16_t);
    fp32_t cvt_s16_to_fp32(int16_t);
    fp32_t cvt_fp16_to_fp32(fp16_t);
    fp32_t cvt_bf16_to_fp32(bf16_t);

    fp16_t cvt_u64_to_fp16(uint64_t);
    fp16_t cvt_s64_to_fp16(int64_t);
    fp16_t cvt_u32_to_fp16(uint32_t);
    fp16_t cvt_s32_to_fp16(int32_t);
    fp16_t cvt_u16_to_fp16(uint16_t);
    fp16_t cvt_s16_to_fp16(int16_t);
    fp16_t cvt_fp32_to_fp16(fp32_t);
    fp16_t cvt_bf16_to_fp16(bf16_t);




    fp4_t cvt_fp32_to_fp4(fp32_t);


}  // namespace floatfactory::swimp

namespace hwimp {

}  // namespace floatfactory::hwimp

}  // namespace floatfactory
