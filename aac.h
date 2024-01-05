#ifndef __AAC_H__
#define __AAC_H__

#include <stdio.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define readMaxLen 4096

    int aacEncInit(uint32_t sampleRate, uint8_t bitFormat, uint8_t channel);
    int aacEncode(void *pPCMdata, unsigned int PCMdatasize, void *pAACdata);
    int aacEncEnd();
#ifdef __cplusplus
}
#endif
#endif // __AAC_H__