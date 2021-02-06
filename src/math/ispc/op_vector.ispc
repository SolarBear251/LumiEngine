export void cross3(uniform float res[3], uniform const float a[3], uniform const float b[3])
{
    foreach(index = 0 ... 3) {
        int index_a = ((index == 2) ? 0 : index + 1);
        int index_b = ((index == 0) ? 2 : index - 1);
        res[index] = a[index_a] * b[index_b] - a[index_b] * b[index_a];
    }

    return;
}

export void normalize(uniform float v[], uniform const size_t cnt, uniform float length)
{
    if (!length) return;
    length = 1.0f / length;
    foreach (index = 0 ... cnt) {
        v[index] *= length;
    }
}
