#include "floatfactory.h"

namespace floatfactory {
namespace swimp {

fp4_t cvt_fp32_to_fp4(fp32_t fp32_value) {
    fp4_t res;
    res.value = 0;
    if (fp32_value.field.exp == 0xff && fp32_value.field.man != 0) {
        // NAN converts to positive FP4_MAXNORM
        res.value = 0x7;
        return res;
    }
    /*
        0.5
        fp32(0.5) =  s 01111110 00000000000000000000000
        min =        s 01111101 11000000000000000000000  >= 1.75 * 2 ^ -2
    */
    
}

} // namespace swimp
} // namespace floatfactory