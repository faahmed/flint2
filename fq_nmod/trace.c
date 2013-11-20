/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 Mike Hansen

******************************************************************************/

#include "fq_nmod.h"

void _fq_nmod_trace(fmpz_t rop2, const mp_limb_t *op, slong len, 
                    const fq_nmod_ctx_t ctx)
{
    const slong d = fq_nmod_ctx_degree(ctx);

    ulong i, l;
    mp_limb_t *t, rop;

    t = _nmod_vec_init(d);
    _nmod_vec_zero(t, d);

    t[0] = n_mod2_preinv(d, ctx->mod.n, ctx->mod.ninv);

    for (i = 1; i < d; i++)
    {
        for (l = ctx->len - 2; l >= 0 && ctx->j[l] >= d - (i - 1); l--)
        {
            t[i] = n_addmod(t[i],
                            n_mulmod2_preinv(t[ctx->j[l] + i - d], ctx->a[l], ctx->mod.n, ctx->mod.ninv), 
                            ctx->mod.n);
        }

        if (l >= 0 && ctx->j[l] == d - i)
        {
            t[i] = n_addmod(t[i],
                            n_mulmod2_preinv(ctx->a[l], i, ctx->mod.n, ctx->mod.ninv),
                            ctx->mod.n);
        }

        t[i] = n_negmod(t[i], ctx->mod.n);
    }

    
    rop = WORD(0);
    for (i = 0; i < d; i++)
    {
        rop = n_addmod(rop,
                       n_mulmod2_preinv(op[i], t[i], ctx->mod.n, ctx->mod.ninv),
                       ctx->mod.n);
    }

    _nmod_vec_clear(t);

    fmpz_set_ui(rop2, rop);
}

void fq_nmod_trace(fmpz_t rop, const fq_nmod_t op, const fq_nmod_ctx_t ctx)
{
    if (fq_nmod_is_zero(op, ctx))
    {
        fmpz_zero(rop);
        return;
    }

    _fq_nmod_trace(rop, op->coeffs, op->length, ctx);
}

