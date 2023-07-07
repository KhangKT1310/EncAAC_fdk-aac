#ifndef __MTCE_aac_H__
#define __MTCE_aac_H__

#include <stdio.h>
#include <stdint.h>


int aacEncInit(uint32_t sampleRate,uint8_t bitFormat,uint8_t channel);
int aacEncode(void *pPCMdata, unsigned int PCMdatasize, void *pAACdata);
int aacEncEnd();

#endif // __MTCE_aac_H__