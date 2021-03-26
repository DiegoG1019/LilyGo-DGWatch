#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_INFO_N_8PX
#define LV_ATTRIBUTE_IMG_INFO_N_8PX
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_INFO_N_8PX uint8_t info_n_8px_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x08, 0x00, 0x18, 0x27, 0x18, 0xb0, 0x18, 0xf3, 0x18, 0xf3, 0x18, 0xb0, 0x18, 0x28, 0x08, 0x00, 
  0x18, 0x27, 0x18, 0xef, 0x18, 0xff, 0x59, 0xff, 0x79, 0xff, 0x18, 0xff, 0x18, 0xf0, 0x18, 0x28, 
  0x18, 0xac, 0x18, 0xff, 0x18, 0xff, 0x9e, 0xff, 0xdf, 0xff, 0x18, 0xff, 0x18, 0xff, 0x18, 0xb0, 
  0x18, 0xec, 0x59, 0xff, 0xbf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0x79, 0xff, 0x18, 0xf3, 
  0x18, 0xec, 0x59, 0xff, 0xbf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0x7e, 0xff, 0x18, 0xf3, 
  0x18, 0xac, 0x18, 0xff, 0x18, 0xff, 0x9e, 0xff, 0xdf, 0xff, 0x18, 0xff, 0x18, 0xff, 0x18, 0xb0, 
  0x18, 0x27, 0x18, 0xef, 0x18, 0xff, 0x59, 0xff, 0x7a, 0xff, 0x18, 0xff, 0x18, 0xf0, 0x18, 0x28, 
  0x08, 0x00, 0x18, 0x27, 0x18, 0xaf, 0x18, 0xf3, 0x18, 0xf3, 0x18, 0xb0, 0x18, 0x28, 0x08, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0xc0, 0x01, 0x00, 0x40, 0x06, 0x27, 0x40, 0x06, 0xb0, 0x40, 0x06, 0xf3, 0x40, 0x06, 0xf3, 0x40, 0x06, 0xb0, 0x40, 0x06, 0x28, 0x80, 0x02, 0x00, 
  0x40, 0x06, 0x27, 0x40, 0x06, 0xef, 0x40, 0x06, 0xff, 0x68, 0x46, 0xff, 0x8b, 0x5e, 0xff, 0x40, 0x06, 0xff, 0x40, 0x06, 0xf0, 0x40, 0x06, 0x28, 
  0x40, 0x06, 0xac, 0x40, 0x06, 0xff, 0x40, 0x06, 0xff, 0xf2, 0x96, 0xff, 0x58, 0xc7, 0xff, 0x40, 0x06, 0xff, 0x40, 0x06, 0xff, 0x40, 0x06, 0xb0, 
  0x40, 0x06, 0xec, 0x69, 0x4e, 0xff, 0x15, 0xaf, 0xff, 0x59, 0xcf, 0xff, 0x9b, 0xdf, 0xff, 0x15, 0xaf, 0xff, 0x8c, 0x66, 0xff, 0x40, 0x06, 0xf3, 
  0x40, 0x06, 0xec, 0x69, 0x4e, 0xff, 0x15, 0xaf, 0xff, 0x79, 0xcf, 0xff, 0x9b, 0xdf, 0xff, 0x15, 0xaf, 0xff, 0x8c, 0x66, 0xff, 0x40, 0x06, 0xf3, 
  0x40, 0x06, 0xac, 0x40, 0x06, 0xff, 0x40, 0x06, 0xff, 0xf2, 0x96, 0xff, 0x58, 0xc7, 0xff, 0x40, 0x06, 0xff, 0x40, 0x06, 0xff, 0x40, 0x06, 0xb0, 
  0x40, 0x06, 0x27, 0x40, 0x06, 0xef, 0x40, 0x06, 0xff, 0x69, 0x4e, 0xff, 0x8c, 0x66, 0xff, 0x40, 0x06, 0xff, 0x40, 0x06, 0xf0, 0x40, 0x06, 0x28, 
  0xc0, 0x01, 0x00, 0x40, 0x06, 0x27, 0x40, 0x06, 0xaf, 0x40, 0x06, 0xf3, 0x40, 0x06, 0xf3, 0x40, 0x06, 0xb0, 0x40, 0x06, 0x28, 0x80, 0x02, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x01, 0xc0, 0x00, 0x06, 0x40, 0x27, 0x06, 0x40, 0xb0, 0x06, 0x40, 0xf3, 0x06, 0x40, 0xf3, 0x06, 0x40, 0xb0, 0x06, 0x40, 0x28, 0x02, 0x80, 0x00, 
  0x06, 0x40, 0x27, 0x06, 0x40, 0xef, 0x06, 0x40, 0xff, 0x46, 0x68, 0xff, 0x5e, 0x8b, 0xff, 0x06, 0x40, 0xff, 0x06, 0x40, 0xf0, 0x06, 0x40, 0x28, 
  0x06, 0x40, 0xac, 0x06, 0x40, 0xff, 0x06, 0x40, 0xff, 0x96, 0xf2, 0xff, 0xc7, 0x58, 0xff, 0x06, 0x40, 0xff, 0x06, 0x40, 0xff, 0x06, 0x40, 0xb0, 
  0x06, 0x40, 0xec, 0x4e, 0x69, 0xff, 0xaf, 0x15, 0xff, 0xcf, 0x59, 0xff, 0xdf, 0x9b, 0xff, 0xaf, 0x15, 0xff, 0x66, 0x8c, 0xff, 0x06, 0x40, 0xf3, 
  0x06, 0x40, 0xec, 0x4e, 0x69, 0xff, 0xaf, 0x15, 0xff, 0xcf, 0x79, 0xff, 0xdf, 0x9b, 0xff, 0xaf, 0x15, 0xff, 0x66, 0x8c, 0xff, 0x06, 0x40, 0xf3, 
  0x06, 0x40, 0xac, 0x06, 0x40, 0xff, 0x06, 0x40, 0xff, 0x96, 0xf2, 0xff, 0xc7, 0x58, 0xff, 0x06, 0x40, 0xff, 0x06, 0x40, 0xff, 0x06, 0x40, 0xb0, 
  0x06, 0x40, 0x27, 0x06, 0x40, 0xef, 0x06, 0x40, 0xff, 0x4e, 0x69, 0xff, 0x66, 0x8c, 0xff, 0x06, 0x40, 0xff, 0x06, 0x40, 0xf0, 0x06, 0x40, 0x28, 
  0x01, 0xc0, 0x00, 0x06, 0x40, 0x27, 0x06, 0x40, 0xaf, 0x06, 0x40, 0xf3, 0x06, 0x40, 0xf3, 0x06, 0x40, 0xb0, 0x06, 0x40, 0x28, 0x02, 0x80, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x39, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x27, 0x00, 0xc8, 0x00, 0xb0, 0x00, 0xc8, 0x00, 0xf3, 0x00, 0xc8, 0x00, 0xf3, 0x00, 0xc8, 0x00, 0xb0, 0x00, 0xc8, 0x00, 0x28, 0x00, 0x50, 0x00, 0x00, 
  0x00, 0xc8, 0x00, 0x27, 0x00, 0xc8, 0x00, 0xef, 0x00, 0xc8, 0x00, 0xff, 0x43, 0xcc, 0x43, 0xff, 0x5c, 0xd0, 0x5c, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xf0, 0x00, 0xc8, 0x00, 0x28, 
  0x00, 0xc8, 0x00, 0xac, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x8d, 0xdb, 0x8d, 0xff, 0xbd, 0xe7, 0xbd, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xb0, 
  0x00, 0xc8, 0x00, 0xec, 0x46, 0xcc, 0x46, 0xff, 0xa9, 0xe0, 0xa9, 0xff, 0xc5, 0xea, 0xc5, 0xff, 0xda, 0xf1, 0xda, 0xff, 0xa9, 0xe0, 0xa9, 0xff, 0x5f, 0xd0, 0x5f, 0xff, 0x00, 0xc8, 0x00, 0xf3, 
  0x00, 0xc8, 0x00, 0xec, 0x47, 0xcd, 0x47, 0xff, 0xab, 0xe2, 0xab, 0xff, 0xc6, 0xeb, 0xc6, 0xff, 0xdb, 0xf2, 0xdb, 0xff, 0xab, 0xe2, 0xab, 0xff, 0x61, 0xd1, 0x61, 0xff, 0x00, 0xc8, 0x00, 0xf3, 
  0x00, 0xc8, 0x00, 0xac, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x8d, 0xdb, 0x8d, 0xff, 0xbd, 0xe7, 0xbd, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xb0, 
  0x00, 0xc8, 0x00, 0x27, 0x00, 0xc8, 0x00, 0xef, 0x00, 0xc8, 0x00, 0xff, 0x48, 0xcd, 0x48, 0xff, 0x63, 0xd0, 0x63, 0xff, 0x00, 0xc8, 0x00, 0xff, 0x00, 0xc8, 0x00, 0xf0, 0x00, 0xc8, 0x00, 0x28, 
  0x00, 0x39, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x27, 0x00, 0xc8, 0x00, 0xaf, 0x00, 0xc8, 0x00, 0xf3, 0x00, 0xc8, 0x00, 0xf3, 0x00, 0xc8, 0x00, 0xb0, 0x00, 0xc8, 0x00, 0x28, 0x00, 0x50, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t info_n_8px = {
  .header.always_zero = 0,
  .header.w = 8,
  .header.h = 8,
  .data_size = 64 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = info_n_8px_map,
};

