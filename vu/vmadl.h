#include "vu.h"

static void VMADL(int vd, int vs, int vt, int e)
{
    register unsigned int product;
    register int i;

    for (i = 0; i < 8; i++)
    {
        product = (unsigned short)VR[vs][i] * (unsigned short)VR[vt][ei[e][i]];
        VACC[i].DW += product >> 16;
    }
    for (i = 0; i < 8; i++) /* Sign-clamp bits 15..0 of ACC to dest. VR. */
        if (CLAMP_BASE(i, 16) < -32768)
            VR[vd][i] = 0; /* element underflow */
        else if (CLAMP_BASE(i, 16) > +32767)
            VR[vd][i] = -1; /* element overflow */
        else
            VR[vd][i] = VACC[i].DW & 0x00000000FFFF;
    return;
}
