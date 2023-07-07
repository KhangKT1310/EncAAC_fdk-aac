#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "app_dbg.h"
#include "aac.h"

#include <fdk-aac/aacenc_lib.h>


typedef struct AacContext
{
    HANDLE_AACENCODER hAacEncoder;
    int inBufferIdentifier;
    int inputbufElsize;
#define readMaxLen 4096
    int outputIdentifier;
    int outputbufElsize;
    int outputBufferSize;

    AACENC_BufDesc inputBufDesc;
    AACENC_BufDesc outputBufDesc;
    AACENC_InArgs inputArgs;
    AACENC_OutArgs outputArgs;

} AacCtx_t;

typedef struct parameterDict
{
	AACENC_PARAM param;
	UINT value;

} Dict_t;

static AacCtx_t ctx; 

int aacEncInit(uint32_t sampleRate,uint8_t bitFormat,uint8_t channel)
{
	memset(&ctx, '\0', sizeof(AacCtx_t));
	AACENC_ERROR AAC_ERR = AACENC_OK;
	Dict_t m_Dict[] =
		{
			{AACENC_AOT, AOT_AAC_LC},
			{AACENC_SBR_MODE, AOT_NULL_OBJECT},
			{AACENC_SAMPLERATE, sampleRate},
			{AACENC_BITRATE, sampleRate * 1 * bitFormat},
			{AACENC_BITRATEMODE, 0},
			{AACENC_CHANNELMODE, MODE_1},
			{AACENC_TRANSMUX, TT_MP4_ADTS},
		};
	AAC_ERR = aacEncOpen(&ctx.hAacEncoder, 0x01, 0x02);
	if (ctx.hAacEncoder == NULL || AAC_ERR != AACENC_OK)
	{
		APP_ERR("Error: aacEncOpen failed.\n");
		return -1;
	}
	int i, j = sizeof(m_Dict) / sizeof(Dict_t);
	for (i = 0; i < j; i++)
	{
		AAC_ERR = aacEncoder_SetParam(ctx.hAacEncoder, m_Dict[i].param, m_Dict[i].value);
		if (AAC_ERR != AACENC_OK)
		{
			aacEncEnd(ctx);
			ctx.hAacEncoder = NULL;
			APP_ERR("Error: aacEncoder_SetParam Error %d \r\n", i);
			return -1;
		}
	}
	if (aacEncEncode(ctx.hAacEncoder, NULL, NULL, NULL, NULL) != AACENC_OK)
	{
		aacEncEnd(ctx);
		ctx.hAacEncoder = NULL;
		APP_ERR("Error: aacEncode test Error form aacEncInit\n");
		return -1;
	}

	ctx.inBufferIdentifier = IN_AUDIO_DATA;
	ctx.inputBufDesc.bufferIdentifiers = &ctx.inBufferIdentifier;
	ctx.inputbufElsize = 2;
	ctx.inputBufDesc.bufElSizes =&ctx.inputbufElsize;

	ctx.outputbufElsize = 1;
	ctx.outputBufDesc.bufElSizes = &ctx.outputbufElsize;
	ctx.outputIdentifier = OUT_BITSTREAM_DATA;
	ctx.outputBufDesc.bufferIdentifiers = &ctx.outputIdentifier;
	ctx.outputBufferSize = readMaxLen;
	ctx.outputBufDesc.bufSizes = (int *)&ctx.outputBufferSize;

	ctx.inputBufDesc.numBufs = 1;
	ctx.outputBufDesc.numBufs = 1;
	return 0;
}

int aacEncode(void *pPCMdata, unsigned int PCMdatasize, void *pAACdata)
{
	/* input buffer info */
	ctx.inputBufDesc.bufs = &pPCMdata;
	ctx.inputBufDesc.bufSizes = (int *)&PCMdatasize;
	/* output buffer info */
	ctx.outputBufDesc.bufs = &pAACdata;

	/* input argument */
	ctx.inputArgs.numInSamples = PCMdatasize / 2;

	/* output argument */
	memset((void *)&ctx.outputArgs, (int)'\0', sizeof(ctx.outputArgs));

	/* encode */

	if (aacEncEncode(ctx.hAacEncoder, &ctx.inputBufDesc, &ctx.outputBufDesc, &ctx.inputArgs, &ctx.outputArgs) != AACENC_OK)
	{
		APP_PRINT("aacEncEncode AACENC CODE output bytes:%d \r\n", ctx.outputArgs.numOutBytes);
		return 0;
	}
	return ctx.outputArgs.numOutBytes;
}
int aacEncEnd()
{
	if (!ctx.hAacEncoder)
	{
		return -1;
	}
	if (aacEncClose(&ctx.hAacEncoder) != AACENC_OK)
	{
		return -1;
	}
	ctx.hAacEncoder = NULL;
	return 0;
}
