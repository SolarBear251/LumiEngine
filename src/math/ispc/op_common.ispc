export void addByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = a[index] + b[index];
    }

    return;
}

export void subByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = a[index] - b[index];
    }

    return;
}

export void mulByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = a[index] * b[index];
    }

    return;
}

export void divByElement(uniform float res[], uniform const float a[], uniform const float b[], uniform const size_t cnt)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = a[index] / b[index];
    }

    return;
}

export void negate(uniform float res[], uniform const float data[], uniform const size_t cnt)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = -data[index];
    }

    return;
}

export void absolute(uniform float res[], uniform const float data[], uniform const size_t cnt)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = abs(data[index]);
    }

    return;
}

export void power(uniform float res[], uniform const float data[], uniform const size_t cnt, uniform const float exponent)
{
    foreach(index = 0 ... cnt)
    {
        res[index] = pow(data[index], exponent);
    }

    return;
}
