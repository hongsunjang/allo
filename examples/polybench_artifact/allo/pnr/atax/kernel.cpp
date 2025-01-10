
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <math.h>
#include <stdint.h>
using namespace std;
void stage_M(
  float v0[390][410],
  float v1[410],
  hls::stream<float> &v2_fifo
) {	// L5
  #pragma HLS array_partition variable=v0 cyclic factor=39 dim=1

  float v2[390];
  #pragma HLS array_partition variable=v2 cyclic factor=39 dim=1
  for (int v4 = 0; v4 < 390; v4++) {	// L6
    v2[v4] = 0.000000;	// L6
  }

  l_S_m_0_r: for (int r = 0; r < 410; r++) {	// L6
    l_m: for (int m = 0; m < 390; m++) {	// L7
      #pragma HLS pipeline II=1
      #pragma HLS unroll factor=39
      float v5 = v0[m][r];	// L8
      float v6 = v1[r];	// L9
      float v7 = v5 * v6;	// L10
      float v8 = v2[m];	// L11
      float v9 = v8 + v7;	// L12
      v2[m] = v9;	// L13
    }
  }

  for (int i = 0; i < 390; i++) {
    v2_fifo.write(v2[i]);
  }
}

void stage_N(
  float v10[390][410],
  // float v11[390],
  hls::stream<float> &v11_fifo,
  float v12[410]
) {	// L18
  #pragma HLS array_partition variable=v10 cyclic factor=41 dim=2
  #pragma HLS array_partition variable=v12 cyclic factor=41 dim=1

  float v11[390];
  for (int v4 = 0; v4 < 390; v4++) {	// L6
    v11[v4] = v11_fifo.read();	// L6
  }

  l_S_n_0_k: for (int k = 0; k < 390; k++) {	// L19
    l_n: for (int n = 0; n < 410; n++) {	// L20
    #pragma HLS pipeline II=1
    #pragma HLS unroll factor=41
      float v15 = v10[k][n];	// L21
      float v16 = v11[k];	// L22
      float v17 = v15 * v16;	// L23
      float v18 = v12[n];	// L24
      float v19 = v18 + v17;	// L25
      v12[n] = v19;	// L26
    }
  }
}

void kernel_atax(
  float v20[390][410],
  float v21[390][410],
  float v22[410],
  float v23[410]
) {	// L31
#pragma HLS dataflow

  hls::stream<float> out_Ax_fifo;
  #pragma HLS stream variable=out_Ax_fifo depth=390

  stage_M(v20, v22, out_Ax_fifo);	// L36
  stage_N(v21, out_Ax_fifo, v23);	// L37
}

