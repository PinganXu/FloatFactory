#include "floatfactory.h"

namespace floatfactory {
namespace swimp {

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

} // namespace swimp
} // namespace floatfactory
