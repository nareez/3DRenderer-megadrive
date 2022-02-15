#include <genesis.h>
#include "display.h"


#define WHITE 0xff

void initialize_window(void){
    VDP_setScreenWidth256();
    BMP_init(TRUE, BG_A, PAL0, FALSE);
}

int pos = 2;
void draw_fix16(fix16 v){
    char str[30];
    fix16ToStr(v, str, 2);
    BMP_drawText(str,0,pos);
    if(++pos>=20){
        pos = 2;
    };
}

void draw_fix16_reset(void){
    pos = 2;
}

void draw_pixel(int x, int y, int color){
    if (x >= 0 && y >= 0 && x < BMP_WIDTH && y < BMP_HEIGHT){
        BMP_setPixelFast(x, y, color);
    }
}

void draw_grid(int grid_size){
    for(int y = 0; y < BMP_HEIGHT; y++){
        for(int x = 0; x < BMP_WIDTH; x++){
            if (y % grid_size == 0 && x % grid_size == 0){
                draw_pixel(x, y, WHITE);
            }          
        }
    }
}

void draw_rect(int dx, int dy, int width, int height, int color){
    for(int y = dy; y < (dy + height); y++){
        for(int x = dx; x < (dx + width); x++){
            draw_pixel(x, y, color);
        }
    }
}

//TODO fix div/0 bug when x0 and y0 is equal x1 and y1, this occurs after a few seconds
vec3_t cube;
void draw_line(int x0, int y0, int x1, int y1, int color){
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    fix16 longest_side_length = abs(delta_x) >= abs(delta_y) ? intToFix16(abs(delta_x)) : intToFix16(abs(delta_y));
    // Find how increment in both x and y each step

    //prevent a div/0
    if(longest_side_length == 0){
        return;
    }

    fix16 x_inc = fix16Div(intToFix16(delta_x), longest_side_length);
    fix16 y_inc = fix16Div(intToFix16(delta_y), longest_side_length);
    
    fix16 current_x = intToFix16(x0);
    fix16 current_y = intToFix16(y0);
    
    for (int i = 0; i < fix16ToInt(longest_side_length); i++) {
        draw_pixel(fix16ToRoundedInt(current_x), fix16ToRoundedInt(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }

}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color){
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}