#include <genesis.h>
#include "display.h"

#define WHITE 0xff

const u16 palette[16] = {
    0x0000, //preto
    0x000E, //vermelho
    0x00EE, //amarelo
    0x0E00, //azul
    0x0E0E, //rosa
    0x00E0, //verde
    0x026e, //laranja
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0eee //branco
};

void initialize_window(void) {
    VDP_setScreenWidth256();
    // VDP_setHInterrupt(0);
    // VDP_setHilightShadow(0);
    BMP_init(TRUE, BG_A, PAL0, FALSE);
    PAL_setPalette(PAL0, palette, CPU);
}

u16 pos = 2;
void draw_fix16(fix16 v) {
    char str[30];
    fix16ToStr(v, str, 2);
    BMP_drawText(str, 0, pos);
    if (++pos >= 20) {
        pos = 2;
    };
}

void draw_fix16_reset(void) {
    pos = 2;
}

void draw_pixel(s16 x, s16 y, u8 color) {
    if (x >= 0 && y >= 0 && x < BMP_WIDTH && y < BMP_HEIGHT) {
        BMP_setPixelFast(x, y, color);
    }
}

void draw_grid(s16 grid_size) {
    for (s16 y = 0; y < BMP_HEIGHT; y++) {
        for (s16 x = 0; x < BMP_WIDTH; x++) {
            if (y % grid_size == 0 && x % grid_size == 0) {
                draw_pixel(x, y, WHITE);
            }
        }
    }
}

void draw_rect(s16 dx, s16 dy, s16 width, s16 height, u8 color) {
    for (s16 y = dy; y < (dy + height); y++) {
        for (s16 x = dx; x < (dx + width); x++) {
            draw_pixel(x, y, color);
        }
    }
}

//SGDK assembly drawline
void draw_line(s16 x0, s16 y0, s16 x1, s16 y1, u16 color) {

    Vect2D_s16 v1 = {
        .x = x0,
        .y = y0
    };    
    Vect2D_s16 v2 = {
        .x = x1,
        .y = y1
    };

    Line line = {
        .pt1 = v1,
        .pt2 = v2,
        .col = color
    };

    BMP_drawLine(&line);
}
// TODO fix div/0 bug when x0 and y0 is equal x1 and y1, this occurs after a few seconds
// DDA algorithm 
// void draw_line2(int x0, int y0, int x1, int y1, int color) {
//     int delta_x = (x1 - x0);
//     int delta_y = (y1 - y0);

//     fix16 longest_side_length = abs(delta_x) >= abs(delta_y) ? intToFix16(abs(delta_x)) : intToFix16(abs(delta_y));
//     // Find how increment in both x and y each step

//     // prevent a div/0
//     if (longest_side_length == 0) {
//         return;
//     }

//     fix16 x_inc = fix16Div(intToFix16(delta_x), longest_side_length);
//     fix16 y_inc = fix16Div(intToFix16(delta_y), longest_side_length);

//     fix16 current_x = intToFix16(x0);
//     fix16 current_y = intToFix16(y0);

//     for (int i = 0; i < fix16ToInt(longest_side_length); i++) {
//         draw_pixel(fix16ToRoundedInt(current_x), fix16ToRoundedInt(current_y), color);
//         current_x += x_inc;
//         current_y += y_inc;
//     }
// }

void draw_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}