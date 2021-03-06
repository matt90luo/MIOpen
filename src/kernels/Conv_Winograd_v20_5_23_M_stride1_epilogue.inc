/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/
s_endpgm
.Lfunc_end0:
   .size miopenSp3AsmConv_group_20_5_23_M_stride1, .Lfunc_end0 - miopenSp3AsmConv_group_20_5_23_M_stride1

   workgroup_size_x = 512
.amdgcn.next_free_sgpr = 101
.amdgcn.next_free_vgpr = 128

.rodata
.p2align 6
.amdhsa_kernel  miopenSp3AsmConv_group_20_5_23_M_stride1
    .amdhsa_group_segment_fixed_size 65536
    .amdhsa_user_sgpr_private_segment_buffer 1
    .amdhsa_user_sgpr_dispatch_ptr 1
    .amdhsa_user_sgpr_kernarg_segment_ptr 1
    .amdhsa_system_sgpr_workgroup_id_x 1
    .amdhsa_system_sgpr_workgroup_id_y 0
    .amdhsa_system_sgpr_workgroup_id_z 0
    .amdhsa_system_vgpr_workitem_id 0
    .amdhsa_next_free_vgpr .amdgcn.next_free_vgpr
    .amdhsa_next_free_sgpr .amdgcn.next_free_sgpr
    .amdhsa_reserve_vcc 1
    .amdhsa_reserve_xnack_mask 1
    .amdhsa_reserve_flat_scratch 0
    .amdhsa_ieee_mode 0
    .amdhsa_dx10_clamp 0
.end_amdhsa_kernel

.macro METADATA sc,wc,wg_x
.amdgpu_metadata
---
amdhsa.version: [ 1, 0 ]
amdhsa.kernels:
  - .name:  miopenSp3AsmConv_group_20_5_23_M_stride1
    .symbol:  miopenSp3AsmConv_group_20_5_23_M_stride1.kd
    .language: "OpenCL C"
    .language_version: [ 1, 2 ]
    .sgpr_count: \sc
    .vgpr_count: \wc
    .group_segment_fixed_size: 65536
    .private_segment_fixed_size: 0
    .kernarg_segment_size: 216
    .kernarg_segment_align: 8
    .reqd_workgroup_size: [ \wg_x, 1, 1 ]
    .max_flat_workgroup_size: \wg_x
    .wavefront_size: 64
    .args:
    - { .size: 4, .offset:   0, .value_kind: by_value, .value_type: i32, .name: N }
    - { .size: 4, .offset:   4, .value_kind: by_value, .value_type: i32, .name: C }
    - { .size: 4, .offset:   8, .value_kind: by_value, .value_type: i32, .name: H }
    - { .size: 4, .offset:  12, .value_kind: by_value, .value_type: i32, .name: W }
    - { .size: 4, .offset:  16, .value_kind: by_value, .value_type: i32, .name: K }
    - { .size: 4, .offset:  20, .value_kind: by_value, .value_type: i32, .name: n_groups }
    - { .size: 4, .offset:  24, .value_kind: by_value, .value_type: i32, .name: flags }
    - { .size: 4, .offset:  28, .value_kind: by_value, .value_type: i32, .name: reserved  }
    - { .size: 8, .offset:  32, .value_kind: global_buffer, .value_type: f32, .name: in,   .address_space: global, .is_const: false }
    - { .size: 8, .offset:  40, .value_kind: global_buffer, .value_type: f32, .name: weights,    .address_space: global, .is_const: false }
    - { .size: 8, .offset:  48, .value_kind: global_buffer, .value_type: f32, .name: out, .address_space: global, .is_const: false }
    - { .size: 8, .offset:  56, .value_kind: global_buffer, .value_type: f32, .name: rsv_ptr,     .address_space: global, .is_const: false }
    - { .size: 4, .offset:  64, .value_kind: by_value, .value_type: i32, .name: R }
    - { .size: 4, .offset:  68, .value_kind: by_value, .value_type: i32, .name: S }
    - { .size: 4, .offset:  72, .value_kind: by_value, .value_type: i32, .name: pad_h }
    - { .size: 4, .offset:  76, .value_kind: by_value, .value_type: i32, .name: pad_w }
    - { .size: 4, .offset:  80, .value_kind: by_value, .value_type: i32, .name: out_h }
    - { .size: 4, .offset:  84, .value_kind: by_value, .value_type: i32, .name: out_w }
    - { .size: 8, .offset:  88, .value_kind: global_buffer, .value_type: f32, .name: bias_addr,    .address_space: global, .is_const: true }
    - { .size: 4, .offset:  96, .value_kind: by_value, .value_type: f32, .name: RELU_alpha }
    - { .size: 4, .offset: 100, .value_kind: by_value, .value_type: i32, .name: d_N_stride }
    - { .size: 4, .offset: 104, .value_kind: by_value, .value_type: i32, .name: d_C_stride }
    - { .size: 4, .offset: 108, .value_kind: by_value, .value_type: i32, .name: d_H_stride }
    - { .size: 4, .offset: 112, .value_kind: by_value, .value_type: i32, .name: d_W_stride }
    - { .size: 4, .offset: 116, .value_kind: by_value, .value_type: i32, .name: f_K_stride }
    - { .size: 4, .offset: 120, .value_kind: by_value, .value_type: i32, .name: f_C_stride }
    - { .size: 4, .offset: 124, .value_kind: by_value, .value_type: i32, .name: f_R_stride }
    - { .size: 4, .offset: 128, .value_kind: by_value, .value_type: i32, .name: f_S_stride }
    - { .size: 4, .offset: 132, .value_kind: by_value, .value_type: i32, .name: o_N_stride }
    - { .size: 4, .offset: 136, .value_kind: by_value, .value_type: i32, .name: o_K_stride }
    - { .size: 4, .offset: 140, .value_kind: by_value, .value_type: i32, .name: o_H_stride }
    - { .size: 4, .offset: 144, .value_kind: by_value, .value_type: i32, .name: o_W_stride }
    - { .size: 4, .offset: 148, .value_kind: by_value, .value_type: i32, .name: G }
    - { .size: 4, .offset: 152, .value_kind: by_value, .value_type: i32, .name: d_G_stride }
    - { .size: 4, .offset: 156, .value_kind: by_value, .value_type: i32, .name: f_G_stride }
    - { .size: 4, .offset: 160, .value_kind: by_value, .value_type: i32, .name: o_G_stride }
    - { .size: 8, .offset: 168, .value_kind: hidden_global_offset_x, .value_type: i64 }
    - { .size: 8, .offset: 176, .value_kind: hidden_global_offset_y, .value_type: i64 }
    - { .size: 8, .offset: 184, .value_kind: hidden_global_offset_z, .value_type: i64 }
    - { .size: 8, .offset: 192, .value_kind: hidden_none,   .value_type: i8 }
    - { .size: 8, .offset: 200, .value_kind: hidden_none,   .value_type: i8 }
    - { .size: 8, .offset: 208, .value_kind: hidden_none,   .value_type: i8 }
...
.end_amdgpu_metadata
.endm // METADATA

.altmacro
.macro METADATA_WRAPPER sc,wc,wg_x
    METADATA %\sc, %\wc, %\wg_x
.endm

.ifnotdef workgroup_size_x
    .error "workgroup_size_x must be defined"
    .end
.endif

total_sgpr_count = .amdgcn.next_free_sgpr + 4 // vcc, xnack

METADATA_WRAPPER total_sgpr_count,.amdgcn.next_free_vgpr,workgroup_size_x

