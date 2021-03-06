/*
    Copyright (C) 2010 William Hart
    Copyright (C) 2014 Abhinav Baid

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "mpf_mat.h"

void
mpf_mat_randtest(mpf_mat_t mat, flint_rand_t state, mp_bitcnt_t bits)
{
    slong r, c, i, j;

    r = mat->r;
    c = mat->c;

    _flint_rand_init_gmp(state);

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            mpf_urandomb(mpf_mat_entry(mat, i, j), state->gmp_state, bits);
}
