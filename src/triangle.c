#include "triangle.h"

void int_swap(s16 * a, s16 * b){
    s16 tmp = *a;
    *a = *b;
    *b = tmp;
}

///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat top
///////////////////////////////////////////////////////////////////////////////
//
//  (x0,y0)------(x1,y1)
//      \         /
//       \       /
//        \     /
//         \   /
//          \ /
//        (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void fill_flat_top_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color){
    // Find the two slopes (two triangles legs)
    fix16 inv_slope_1 = fix16Div(intToFix16(x2 - x0), intToFix16(y2 - y0));
    fix16 inv_slope_2 = fix16Div(intToFix16(x2 - x1), intToFix16(y2 - y1));

    // start x_start and x_end from the bottom vertex (x2,y2)
    fix16 x_start = intToFix16(x2);
    fix16 x_end = intToFix16(x2);

    // loop all scanlines from bottom to top
    for (s16 y = y2; y >= y0; y--){
        draw_line(fix16ToRoundedInt(x_start), y, fix16ToRoundedInt(x_end), y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

/*//////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat bottom
///////////////////////////////////////////////////////////////////////////////
//
//        (x0,y0)
//          / \
//         /   \
//        /     \
//       /       \
//      /         \
//  (x1,y1)------(x2,y2)
//
//////////////////////////////////////////////////////////////////////////////*/
void fill_flat_bottom_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color){
    // Find the two slopes (two triangles legs)
    fix16 inv_slope_1 = fix16Div(intToFix16(x1 - x0), intToFix16(y1 - y0));
    fix16 inv_slope_2 = fix16Div(intToFix16(x2 - x0), intToFix16(y2 - y0));

    // start x_start and x_end from the top vertex (x0,y0)
    fix16 x_start = intToFix16(x0);
    fix16 x_end = intToFix16(x0);

    // loop all scanlines from top to bottom
    for (s16 y = y0; y <= y2; y++){
        draw_line(fix16ToRoundedInt(x_start), y, fix16ToRoundedInt(x_end), y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

/*//////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
//
//////////////////////////////////////////////////////////////////////////////*/
void draw_filled_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color){
    // sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1){
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }
    if (y1 > y2){
        int_swap(&y1, &y2);
        int_swap(&x1, &x2);
    }
    if (y0 > y1){
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }

    // if y1 and y2 is equal, just draw the triangle to prevent division by zero
    if (y1 == y2){
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    // if y0 and y1 is equal, just draw the triangle to prevent division by zero
    } else if (y0 == y1){
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // calculate the new vertex (Mx, My) using triangle similarity
        s16 My = y1;
        s16 Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);
        // Draw flat-top triangle
        fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
    }

}