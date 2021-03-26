/**
 * @file       op_matrix.ispc
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-03-26
 * 
 * @brief    ISPC version of matrix operations
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

export void transform(uniform float v[4], uniform const float m[16])
{
    foreach(index = 0 ... 4) {
        v[index] = (v[0] * m[index]) 
            + (v[1] * m[index + 4]) 
            + (v[2] * m[index + 8]) 
            + (v[3] * m[index + 12]);
    }
}

export void transpose(uniform float res[], uniform const float m[], uniform const size_t rows, uniform const size_t cols) {
	foreach(i = 0 ... rows, j = 0 ... cols) {
		res[j * rows + i] = m[i * cols + j];
	}
}

export void setIdentity(uniform float data[], const uniform int n)
{
	foreach(i = 0 ... n, j = 0 ... n) {
		if (i == j)
			data[i * n + j] = 1;
		else
			data[i * n + j] = 0;
	}
}

export void MatrixExchangeYandZ(uniform float data[], const uniform int rows, const uniform int cols)
{
    foreach(row_index = 0 ... rows) {
        int start_index = row_index * cols;
        unsigned int* p = (unsigned int*)(data + start_index + 1);
        unsigned int* q = (unsigned int*)(data + start_index + 2);
        *p ^= *q;
        *q ^= *p;
        *p ^= *q;
    }
}

float inv3x3(int i, int j, uniform const float matrix[9])
{
	int pre_i = ((i == 0) ? 2 : i - 1);
	int next_i = ((i + 1 == 3) ? 0 : i + 1);
	int pre_j = ((j == 0) ? 2 : j - 1);
	int next_j = ((j + 1 == 3) ? 0 : j + 1);

#define e(a, b) matrix[(a)*3 + (b)]
    float inv =
        + e(next_i, next_j) * e(pre_i, pre_j)
        - e(next_i, pre_j) * e(pre_i, next_j);

    return inv;
#undef e
}

float inv4x4(int i, int j, uniform const float matrix[16])
{
	int pre_i = ((i == 0) ? 3 : i - 1);
	int next_i = ((i + 1 == 4) ? 0 : i + 1);
	int next_next_i = ((i + 2 >= 4) ? i - 2 : i + 2);
	int pre_j = ((j == 0) ? 3 : j - 1);
	int next_j = ((j + 1 == 4) ? 0 : j + 1);
	int next_next_j = ((j + 2 >= 4) ? j - 2 : j + 2);
    int o = i-j < 0? j-i:i-j;

#define e(a, b) matrix[(a)*4 + (b)]
    float inv =
        + e(next_i, next_j) * e(next_next_i, next_next_j) * e(pre_i, pre_j)
        + e(next_i, next_next_j) * e(next_next_i, pre_j) * e(pre_i, next_j)
        + e(next_i, pre_j) * e(next_next_i, next_j) * e(pre_i, next_next_j)
        - e(next_i, next_j) * e(next_next_i, pre_j) * e(pre_i, next_next_j)
        - e(next_i, next_next_j) * e(next_next_i, next_j) * e(pre_i, pre_j)
        - e(next_i, pre_j) * e(next_next_i, next_next_j) * e(pre_i, next_j);

    return (o & 0x1) ? -inv : inv;
#undef e
}

export uniform bool invMat3x3f(uniform float matrix[9])
{
    uniform float inv[9];
    uniform double D = 0;

    foreach_tiled(i = 0 ... 3, j = 0 ... 3) {
        inv[j * 3 + i] = inv3x3(i, j, matrix);
    }

    foreach(k = 0 ... 3) {
        float s = matrix[k] * inv[k * 3];
        D = reduce_add(s);
    }

    if (D == 0) return false;

    D = 1.0 / D;

    foreach(i = 0 ... 9) {
        matrix[i] = inv[i] * D;
    }

    return true;
}

export uniform bool invMat4x4f(uniform float matrix[16])
{
    uniform float inv[16];
    uniform double D = 0;

    foreach_tiled(i = 0 ... 4, j = 0 ... 4) {
        inv[j * 4 + i] = inv4x4(i, j, matrix);
    }

    foreach(k = 0 ... 4) {
        float s = matrix[k] * inv[k * 4];
        D = reduce_add(s);
    }

    if (D == 0) return false;

    D = 1.0 / D;

    foreach(i = 0 ... 16) {
        matrix[i] = inv[i] * D;
    }

    return true;
}

uniform const float one_over_four = 1.0f / 4.0f;
uniform const float PI_over_sixteen = PI / 16.0f;

inline float normalizing_scale_factor(float a)
{
    return (a == 0)? 1.0f/sqrt(2.0f) : 1.0f;
}

export void DCT8x8(uniform float G[64], uniform const float g[64])
{
    uniform float result_cache[8][8][8][8];

    foreach(u = 0 ... 8, v = 0 ... 8, x = 0 ... 8, y = 0 ... 8) {
        float scale_factor = one_over_four * normalizing_scale_factor(u)
                * normalizing_scale_factor(v);
        float normial = g[x * 8 + y] * cos((2.0f * x + 1.0f) * u * PI_over_sixteen)
                * cos((2.0f * y + 1.0f) * v * PI_over_sixteen);
        result_cache[u][v][x][y] = scale_factor * normial;
    }

    foreach(u = 0 ... 8, v = 0 ... 8) {
        G[u * 8 + v] = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                G[u * 8 + v] += result_cache[u][v][x][y];
            }
        }
    }
}

export void IDCT8x8(uniform float g[64], uniform const float G[64])
{
    uniform float result_cache[8][8][8][8];

    foreach(x = 0 ... 8, y = 0 ... 8, u = 0 ... 8, v = 0 ... 8) {
        float scale_factor = one_over_four * normalizing_scale_factor(u)
            * normalizing_scale_factor(v);
        float normial = G[u * 8 + v] * cos((2.0f * x + 1.0f) * u * PI_over_sixteen)
            * cos((2.0f * y + 1.0f) * v * PI_over_sixteen);
        result_cache[x][y][u][v] = scale_factor * normial;
    }

    foreach(x = 0 ... 8, y = 0 ... 8) {
        float sum = 0.0f;
        for (int u = 0; u < 8; u++) {
            for (int v = 0; v < 8; v++) {
                sum += result_cache[x][y][u][v];
            }
        }
        g[x * 8 + y] = sum;
    }
}
