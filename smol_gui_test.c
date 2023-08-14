#include <stdio.h>

#define SMOL_FRAME_IMPLEMENTATION
#include "smol_frame.h"

#define SMOL_CANVAS_IMPLEMENTATION
#include "smol_canvas.h"

#define SMOL_UTILS_IMPLEMENTATION
#include "smol_utils.h"

#define SMOL_GUI_IMPLEMENTATION
#include "smol_gui.h"

int main() {
    smol_frame_t* frame = smol_frame_create(800, 600, "Test");
	smol_canvas_t canvas = smol_canvas_create(800, 600);

    smol_gui_t gui = smol_gui_create(&canvas);

    while (!smol_frame_is_closed(frame)) {
		smol_frame_update(frame);
		
		SMOL_FRAME_EVENT_LOOP(frame, ev) {
            if (ev.type == SMOL_FRAME_EVENT_MOUSE_BUTTON_UP) {
				smol_gui_input_mouse_click(&gui, SMOL_FALSE);
			}
			else if (ev.type == SMOL_FRAME_EVENT_MOUSE_BUTTON_DOWN) {
				smol_gui_input_mouse_click(&gui, SMOL_TRUE);
			}
			else if (ev.type == SMOL_FRAME_EVENT_MOUSE_MOVE) {
				smol_gui_input_mouse_move(
					&gui,
					(smol_point_t) { ev.mouse.x, ev.mouse.y },
					(smol_point_t) { ev.mouse.dx, ev.mouse.dy }
				);
			}
		}

        smol_canvas_set_blend(&canvas, smol_pixel_blend_mix);
		smol_canvas_clear(&canvas, SMOL_RGB(147, 147, 147));

        smol_gui_begin(&gui);

        if (smol_gui_button(&gui, "test", "Button", smol_rect(10, 10, 120, 24))) {
            printf("Clicked!\n");
        }

        static int value = 0;
        smol_gui_slideri(&gui, "slider", smol_rect(10, 40, 120, 22), &value, 0, 10, 1);

		static double value2 = 0.0;
        smol_gui_sliderd(&gui, "slider2", smol_rect(10, 70, 120, 22), &value2, 0.0, 1.0, 0.5);

        smol_gui_end(&gui);

		smol_canvas_present(&canvas, frame);
	}

	smol_frame_destroy(frame);

    return 0;
}
