#include <assert.h>
#include "floatfactory.h"


namespace floatfactory {
namespace swimp {


fp32_t cvt_fp16_to_fp32(fp16_t fp16_value) {
    fp32_t res;
    if (fp16_value.field.exp == 0 && fp16_value.field.man == 0) {
        res.value = 0;
        res.field.sign = fp16_value.field.sign;
    }
    else if (fp16_value.field.exp == 0 && fp16_value.field.man != 0) {
        // subnormal
        unsigned man = fp16_value.field.man;
        unsigned nlz = 0;  // number of leading zeros  
        if ((man & 0xff00U) == 0) { nlz += 8; man <<= 8; }
        if ((man & 0xf000U) == 0) { nlz += 4; man <<= 4; }
        if ((man & 0xc000U) == 0) { nlz += 2; man <<= 2; }
        if ((man & 0x8000U) == 0) { nlz += 1; man <<= 1; }
        nlz -= 6;
        res.field.exp  = 0x70U - nlz;  // 0x7fU - 0xfU -nlz
        res.field.man  = fp16_value.field.man << (nlz + 14);
        res.field.sign = fp16_value.field.sign;
    }
    else if (fp16_value.field.exp == 0x1fU && fp16_value.field.man != 0) {
        // NAN
        res.value = 0x7fffffffU;  // qNAN
    }
    else if (fp16_value.field.exp == 0x1fU && fp16_value.field.man == 0) {
        // Inf
        res.value = 0x7f800000U;
        res.field.sign = fp16_value.field.sign;
    }
    else {
        res.field.exp = fp16_value.field.exp + 0x70U;
        res.field.man = fp16_value.field.man << 13;
        res.field.sign = fp16_value.field.sign;
    }
    return res;
}

fp32_t cvt_bf16_to_fp32(bf16_t bf16_value) {
    fp32_t res;
    res.value = bf16_value.value << 16;
    return res;
}


fp4_t cvt_fp32_to_fp4(fp32_t fp32_value) {
    fp4_t res;
    res.value = 0;
    uint32_t absx = fp32_value.value & 0x7fffffffU;
    if (absx <= 0x3e800000U) {
        // <= 0.25, res = {s, 0b000}
        res.field.sign = fp32_value.field.sign;
    }
    else if (absx > 0x3e800000U && absx < 0x3f400000U) {
        // > 0.25 && < 0.75, res = {s, 0b001}
        res.field.sign = fp32_value.field.sign;
        res.field.man = 0x1U;
    }
    else if (absx >= 0x3f400000U && absx <= 0x3fa00000U) {
        // >= 0.75 && <= 1.25, res = {s, 0b010}
        res.field.sign = fp32_value.field.sign;
        res.field.exp = 0x1U;
    }
    else if (absx > 0x3fa00000U && absx < 0x3fe00000U) {
        // > 1.25 && < 1.75, res = {s, 0b011}
        res.value = 0x3U;
        res.field.sign = fp32_value.field.sign;
    }
    else if (absx >= 0x3fe00000U && absx <= 0x40200000U) {
        // >= 1.75 && <= 2.5, res = {s, 0b100}
        res.field.sign = fp32_value.field.sign;
        res.field.exp = 0x2U;
    }
    else if (absx > 0x40200000U && absx < 0x40600000U) {
        // > 2.5 && < 3.5, res = {s, 0b101}
        res.value = 0x5U;
        res.field.sign = fp32_value.field.sign;
    }
    else if (absx >= 0x40600000U && absx <= 0x40a00000U) {
        // >= 3.5 && <= 5, res = {s, 0b110}
        res.field.exp = 0x3U;
        res.field.sign = fp32_value.field.sign;
    }
    else { // absx > 0x40a00000U
        res.value = 0x7U;
        // NAN converts to {0b0111}
        res.field.sign = (fp32_value.field.exp == 0xff && fp32_value.field.man != 0) ? 0x0U : fp32_value.field.sign;
    }
    return res;
}

fp4_t cvt_fp16_to_fp4(fp16_t fp16_value) {
    fp32_t fp32_value = cvt_fp16_to_fp32(fp16_value);
    return cvt_fp32_to_fp4(fp32_value);
}

fp4_t cvt_bf16_to_fp4(bf16_t bf16_value) {
    fp32_t fp32_value = cvt_bf16_to_fp32(bf16_value);
    return cvt_fp32_to_fp4(fp32_value);
}

fp16_t cvt_fp4_to_fp16(fp4_t fp4_value) {
    fp16_t res;
    switch (fp4_value.value & 0x7U) {
        case 0x0U: res.value = 0x0U;    break;
        case 0x1U: res.value = 0x3800U; break;
        case 0x2U: res.value = 0x3c00U; break;
        case 0x3U: res.value = 0x3e00U; break;
        case 0x4U: res.value = 0x4000U; break;
        case 0x5U: res.value = 0x4200U; break;
        case 0x6U: res.value = 0x4400U; break;
        case 0x7U: res.value = 0x4600U; break;
        default:
            assert(false && "this condition will not appear!");
    }
    res.field.sign = fp4_value.field.sign;
    return res;
}

} // namespace swimp
} // namespace floatfactory
