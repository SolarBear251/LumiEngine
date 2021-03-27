/**
 * @file       op_common.ispc
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-03-26
 * 
 * @brief    ISPC version of common operations
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#define __ISPC_DECLARE_FOR_EACH_TYPE(DECLARE) \
    DECLARE(float);                           \
    DECLARE(double);                          \
    DECLARE(int32);                           \
    DECLARE(int64)

#define __ISPC_SUM_TYPE(T)                               \
    export uniform T Sum_##T(const uniform T data[],     \
                            const uniform size_t cnt) {  \
        T sum = 0;                                       \
        foreach (i = 0 ... cnt)                          \
            sum += data[i];                              \
        return reduce_add(sum);                          \
    }
__ISPC_DECLARE_FOR_EACH_TYPE(__ISPC_SUM_TYPE);


#define __ISPC_SQUARESUM_TYPE(T)                               \
    export uniform T SquareSum_##T(const uniform T data[],     \
                                  const uniform size_t cnt) {  \
        T sum = 0;                                             \
        foreach (i = 0 ... cnt)                                \
            sum += data[i] * data[i];                          \
        return reduce_add(sum);                                \
    }
__ISPC_DECLARE_FOR_EACH_TYPE(__ISPC_SQUARESUM_TYPE);


#define __ISPC_NEGATE_TYPE(T)                                            \
    export void Negate_##T(uniform T data[], const uniform size_t cnt) { \
        foreach (i = 0 ... cnt)                                          \
            data[i] = -data[i];                                          \
    }
__ISPC_DECLARE_FOR_EACH_TYPE(__ISPC_NEGATE_TYPE);


#define __ISPC_ABS_TYPE(T)                                            \
    export void Abs_##T(uniform T data[], const uniform size_t cnt) { \
        foreach (i = 0 ... cnt)                                       \
            data[i] = abs(data[i]);                                   \
    }
__ISPC_DECLARE_FOR_EACH_TYPE(__ISPC_ABS_TYPE);


#define __ISPC_MULNUMBER_TYPE(T)                                         \
    export void MulNumber_##T(uniform T data[], const uniform float num, \
                              const uniform size_t cnt) {                \
        foreach (i = 0 ... cnt)                                          \
            data[i] *= num;                                              \
    }
__ISPC_DECLARE_FOR_EACH_TYPE(__ISPC_MULNUMBER_TYPE);


// export void Negate(uniform float res[], uniform const float data[], uniform const size_t cnt)
// {
//     foreach(index = 0 ... cnt)
//     {
//         res[index] = -data[index];
//     }

//     return;
// }

// export void Abs(uniform float res[], uniform const float data[], uniform const size_t cnt)
// {
//     foreach(index = 0 ... cnt)
//     {
//         res[index] = abs(data[index]);
//     }

//     return;
// }

// export void DivNumber(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
// {
//     foreach(index = 0 ... cnt)
//     {
//         res[index] = a[index] / b[index];
//     }

//     return;
// }


// export void addByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
// {
//     foreach(index = 0 ... cnt)
//     {
//         res[index] = a[index] + b[index];
//     }

//     return;
// }

// export void subByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
// {
//     foreach(index = 0 ... cnt)
//     {
//         res[index] = a[index] - b[index];
//     }

//     return;
// }

// export void mulByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
// {
//     foreach(index = 0 ... cnt)
//     {
//         res[index] = a[index] * b[index];
//     }

//     return;
// }