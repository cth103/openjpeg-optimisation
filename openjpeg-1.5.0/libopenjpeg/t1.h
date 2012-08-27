/*
 * Copyright (c) 2002-2007, Communications and Remote Sensing Laboratory, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2007, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux and Antonin Descampe
 * Copyright (c) 2005, Herve Drolon, FreeImage Team
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __T1_H
#define __T1_H
/**
@file t1.h
@brief Implementation of the tier-1 coding (coding of code-block coefficients) (T1)

The functions in T1.C have for goal to realize the tier-1 coding operation. The functions
in T1.C are used by some function in TCD.C.
*/

/** @defgroup T1 T1 - Implementation of the tier-1 coding */
/*@{*/

/* ----------------------------------------------------------------------- */
#define T1_NMSEDEC_BITS 7

#define T1_SIG_NE 0x0001	/**< Context orientation : North-East direction */
#define T1_SIG_SE 0x0002	/**< Context orientation : South-East direction */
#define T1_SIG_SW 0x0004	/**< Context orientation : South-West direction */
#define T1_SIG_NW 0x0008	/**< Context orientation : North-West direction */
#define T1_SIG_N 0x0010		/**< Context orientation : North direction */
#define T1_SIG_E 0x0020		/**< Context orientation : East direction */
#define T1_SIG_S 0x0040		/**< Context orientation : South direction */
#define T1_SIG_W 0x0080		/**< Context orientation : West direction */
#define T1_SIG_OTH (T1_SIG_N|T1_SIG_NE|T1_SIG_E|T1_SIG_SE|T1_SIG_S|T1_SIG_SW|T1_SIG_W|T1_SIG_NW)
#define T1_SIG_PRIM (T1_SIG_N|T1_SIG_E|T1_SIG_S|T1_SIG_W)

#define T1_SGN_N 0x0100
#define T1_SGN_E 0x0200
#define T1_SGN_S 0x0400
#define T1_SGN_W 0x0800
#define T1_SGN (T1_SGN_N|T1_SGN_E|T1_SGN_S|T1_SGN_W)

#define T1_SIG 0x1000
#define T1_REFINE 0x2000
#define T1_VISIT 0x4000

#define T1_NUMCTXS_ZC 9
#define T1_NUMCTXS_SC 5
#define T1_NUMCTXS_MAG 3
#define T1_NUMCTXS_AGG 1
#define T1_NUMCTXS_UNI 1

#define T1_CTXNO_ZC 0
#define T1_CTXNO_SC (T1_CTXNO_ZC+T1_NUMCTXS_ZC)
#define T1_CTXNO_MAG (T1_CTXNO_SC+T1_NUMCTXS_SC)
#define T1_CTXNO_AGG (T1_CTXNO_MAG+T1_NUMCTXS_MAG)
#define T1_CTXNO_UNI (T1_CTXNO_AGG+T1_NUMCTXS_AGG)
#define T1_NUMCTXS (T1_CTXNO_UNI+T1_NUMCTXS_UNI)

#define T1_NMSEDEC_FRACBITS (T1_NMSEDEC_BITS-1)

#define T1_TYPE_MQ 0	/**< Normal coding using entropy coder */
#define T1_TYPE_RAW 1	/**< No encoding the information is store under raw format in codestream (mode switch RAW)*/

/** We hold the state of individual data points for the T1 encoder using
 *  a single 32-bit flags word to hold the state of 4 data points.  This corresponds
 *  to the 4-point-high columns that the data is processed in.
 *
 *  These #defines declare the layout of a 32-bit flags word.
 *
 *  This is currently done for encoding only.
 */

#define T1_SIGMA_0  (1 << 0)
#define T1_SIGMA_1  (1 << 1)
#define T1_SIGMA_2  (1 << 2)
#define T1_SIGMA_3  (1 << 3)
#define T1_SIGMA_4  (1 << 4)
#define T1_SIGMA_5  (1 << 5)
#define T1_SIGMA_6  (1 << 6)
#define T1_SIGMA_7  (1 << 7)
#define T1_SIGMA_8  (1 << 8)
#define T1_SIGMA_9  (1 << 9)
#define T1_SIGMA_10 (1 << 10)
#define T1_SIGMA_11 (1 << 11)
#define T1_SIGMA_12 (1 << 12)
#define T1_SIGMA_13 (1 << 13)
#define T1_SIGMA_14 (1 << 14)
#define T1_SIGMA_15 (1 << 15)
#define T1_SIGMA_16 (1 << 16)
#define T1_SIGMA_17 (1 << 17)

#define T1_CHI_0    (1 << 18)
#define T1_CHI_1    (1 << 19)
#define T1_MU_0     (1 << 20)
#define T1_PI_0     (1 << 21)
#define T1_CHI_2    (1 << 22)
#define T1_MU_1     (1 << 23)
#define T1_PI_1     (1 << 24)
#define T1_CHI_3    (1 << 25)
#define T1_MU_2     (1 << 26)
#define T1_PI_2     (1 << 27)
#define T1_CHI_4    (1 << 28)
#define T1_MU_3     (1 << 29)
#define T1_PI_3     (1 << 30)
#define T1_PI_3     (1 << 30)
#define T1_CHI_5    (1 << 31)


/** As an example, the bits T1_SIGMA_3, T1_SIGMA_4 and T1_SIGMA_5
 *  indicate the significance state of the west neighbour of data point zero
 *  of our four, the point itself, and its east neighbour respectively.
 *  Many of the bits are arranged so that given a flags word, you can
 *  look at the values for the data point 0, then shift the flags
 *  word right by 3 bits and look at the same bit positions to see the
 *  values for data point 1.
 *
 *  The #defines below help a bit with this; say you have a flags word
 *  f, you can do things like
 *
 *  (f & T1_SIGMA_THIS)
 *
 *  to see the significance bit of data point 0, then do
 *
 *  ((f >> 3) & T1_SIGMA_THIS)
 *
 *  to see the significance bit of data point 1.
 */

#define T1_SIGMA_NW   T1_SIGMA_0
#define T1_SIGMA_N    T1_SIGMA_1
#define T1_SIGMA_NE   T1_SIGMA_2
#define T1_SIGMA_W    T1_SIGMA_3
#define T1_SIGMA_THIS T1_SIGMA_4
#define T1_SIGMA_E    T1_SIGMA_5
#define T1_SIGMA_SW   T1_SIGMA_6
#define T1_SIGMA_S    T1_SIGMA_7
#define T1_SIGMA_SE   T1_SIGMA_8
#define T1_SIGMA_NEIGHBOURS (T1_SIGMA_NW | T1_SIGMA_N | T1_SIGMA_NE | T1_SIGMA_W | T1_SIGMA_E | T1_SIGMA_SW | T1_SIGMA_S | T1_SIGMA_SE)

#define T1_CHI_THIS   T1_CHI_1
#define T1_MU_THIS    T1_MU_0
#define T1_PI_THIS    T1_PI_0


/* ----------------------------------------------------------------------- */

typedef short dec_flags_t;
typedef unsigned int enc_flags_t;

/**
Tier-1 coding (coding of code-block coefficients)
*/
typedef struct opj_t1 {
	/** codec context */
	opj_common_ptr cinfo;

	/** MQC component */
	opj_mqc_t *mqc;
	/** RAW component */
	opj_raw_t *raw;

	int *data;
	dec_flags_t *dec_flags;
	enc_flags_t *enc_flags;
	int w;
	int h;
	int datasize;
	int dec_flags_size;
	int enc_flags_size;
	int dec_flags_stride;
	int enc_flags_stride;
} opj_t1_t;

#define MACRO_t1_flags(x,y) t1->dec_flags[((x)*(t1->dec_flags_stride))+(y)]

/** @name Exported functions */
/*@{*/
/* ----------------------------------------------------------------------- */
/**
Create a new T1 handle 
and initialize the look-up tables of the Tier-1 coder/decoder
@return Returns a new T1 handle if successful, returns NULL otherwise
@see t1_init_luts
*/
opj_t1_t* t1_create(opj_common_ptr cinfo);
/**
Destroy a previously created T1 handle
@param t1 T1 handle to destroy
*/
void t1_destroy(opj_t1_t *t1);
/**
Encode the code-blocks of a tile
@param t1 T1 handle
@param tile The tile to encode
@param tcp Tile coding parameters
*/
void t1_encode_cblks(opj_t1_t *t1, opj_tcd_tile_t *tile, opj_tcp_t *tcp);
/**
Decode the code-blocks of a tile
@param t1 T1 handle
@param tilec The tile to decode
@param tccp Tile coding parameters
*/
void t1_decode_cblks(opj_t1_t* t1, opj_tcd_tilecomp_t* tilec, opj_tccp_t* tccp);
/* ----------------------------------------------------------------------- */
/*@}*/

/*@}*/

#endif /* __T1_H */
