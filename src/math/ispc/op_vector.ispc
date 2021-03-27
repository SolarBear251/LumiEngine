// /**
//  * @file       op_vector.ispc
//  * @author     Lumi (lumiowo@hotmail.com)
//  * @date       2021-03-26
//  * 
//  * @brief    ISPC version of vector operations
//  * 
//  * *********************************************************************************
//  * 
//  * 
//  * *********************************************************************************
//  */


#define __ISPC_CROSS3(type)                                                 \
    export void cross3(uniform type res[3], uniform const type a[3],        \
                       uniform const type b[3]) {                           \
        foreach (i = 0 ... 3) {                                         \
            int i_a = ((i == 2) ? 0 : i + 1);                   \
            int i_b = ((i == 0) ? 2 : i - 1);                   \
            res[i] = a[i_a] * b[i_b] - a[i_b] * b[i_a]; \
        }                                                                   \
                                                                            \
        return;                                                             \
    }

__ISPC_CROSS3(float);

// // export void cross3(uniform float res[3], uniform const float a[3], uniform const float b[3])
// // {
// //     foreach(index = 0 ... 3) {
// //         int index_a = ((index == 2) ? 0 : index + 1);
// //         int index_b = ((index == 0) ? 2 : index - 1);
// //         res[index] = a[index_a] * b[index_b] - a[index_b] * b[index_a];
// //     }

// //     return;
// // }

// export void normalize(uniform float v[], uniform const size_t cnt, uniform float length)
// {
//     if (!length) return;
//     length = 1.0f / length;
//     foreach (index = 0 ... cnt) {
//         v[index] *= length;
//     }
// }
