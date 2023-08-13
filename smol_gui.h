#ifndef SMOL_GUI_H
#define SMOL_GUI_H

#ifndef SMOL_CANVAS_H
#error Please include smol_canvas before smol_gui
#endif

#ifndef SMOL_UTILS_H
#error Please include smol_utils before smol_gui
#endif

typedef struct _smol_grect_t {
    int x, y, width, height;
} smol_grect_t;

typedef struct _smol_point_t {
    int x, y;
} smol_point_t;

#define smol_rect(x, y, w, h) (smol_grect_t){ (x), (y), (w), (h) }

int smol_rect_has_point(smol_grect_t rect, smol_point_t point);

typedef struct _smol_rectcut_t {
    int minx, miny, maxx, maxy;
} smol_rectcut_t;

smol_rectcut_t smol_rectcut_left(smol_rectcut_t* rect, int a);
smol_rectcut_t smol_rectcut_right(smol_rectcut_t* rect, int a);
smol_rectcut_t smol_rectcut_top(smol_rectcut_t* rect, int a);
smol_rectcut_t smol_rectcut_bottom(smol_rectcut_t* rect, int a);
void smol_rectcut_expand(smol_rectcut_t* rect, int a);

#define smol_to_rect(rectcut) (smol_rect_t){ rectcut.minx, rectcut.miny, rectcut.maxx - rectcut.minx, rectcut.maxy - rectcut.miny }
#define smol_from_rect(rec) (smol_rectcut_t){ rec.x, rec.y, rec.width + rec.x, rec.height + rec.y }

typedef enum _smol_gui_drag_axis {
    SMOL_GUI_DRAG_AXIS_X = (1 << 0),
    SMOL_GUI_DRAG_AXIS_Y = (1 << 1),
    SMOL_GUI_DRAG_AXIS_XY = SMOL_GUI_DRAG_AXIS_X | SMOL_GUI_DRAG_AXIS_Y
} smol_gui_drag_axis;

typedef enum _smol_gui_widget_state {
    SMOL_GUI_WIDGET_STATE_IDLE = 0,
    SMOL_GUI_WIDGET_STATE_DISABLED,
    SMOL_GUI_WIDGET_STATE_HOVERED,
    SMOL_GUI_WIDGET_STATE_ACTIVE,
    SMOL_GUI_WIDGET_STATE_COUNT
} smol_gui_widget_state;

typedef enum _smol_gui_style_patch_type {
    SMOL_GUI_STYLE_PATCH_TYPE_EMPTY = 0,
    
    SMOL_GUI_STYLE_PATCH_TYPE_PRIMARY_CONTAINER,        // Windows
    SMOL_GUI_STYLE_PATCH_TYPE_SECONDARY_CONTAINER,      // Sliders, checkbox's box, text box, etc...
    SMOL_GUI_STYLE_PATCH_TYPE_TERTIARY_CONTAINER,       // Group box, labelled container (with a title)
    
    SMOL_GUI_STYLE_PATCH_TYPE_BUTTON,
    SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR,
    SMOL_GUI_STYLE_PATCH_TYPE_SHADOW,

    SMOL_GUI_STYLE_PATCH_TYPE_TICK_CHECKED,
    SMOL_GUI_STYLE_PATCH_TYPE_TICK_UNCHECKED,
    SMOL_GUI_STYLE_PATCH_TYPE_RADIO_CHECKED,
    SMOL_GUI_STYLE_PATCH_TYPE_RADIO_UNCHECKED,

    SMOL_GUI_STYLE_PATCH_TYPE_COUNT
} smol_gui_style_patch_type;

typedef struct _smol_gui_style_t {
    smol_grect_t sourceRect;
    smol_u32 patchSides[4]; // L, R, B, T
    smol_pixel_t foreground;

    enum {
        SMOL_GUI_STYLE_TYPE_NONE = 0,
        SMOL_GUI_STYLE_TYPE_PATCH,
        SMOL_GUI_STYLE_TYPE_ICON
    } type;
} smol_gui_style_t;

typedef struct _smol_gui_theme_t {
    smol_image_t skin;
    smol_gui_style_t styles[SMOL_GUI_STYLE_PATCH_TYPE_COUNT][SMOL_GUI_WIDGET_STATE_COUNT];
} smol_gui_theme_t;

static const smol_gui_style_t gui_theme_default_styles[SMOL_GUI_STYLE_PATCH_TYPE_COUNT][SMOL_GUI_WIDGET_STATE_COUNT] = {
    { // SMOL_GUI_STYLE_PATCH_TYPE_EMPTY
        { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, SMOL_GUI_STYLE_TYPE_NONE },
        { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, SMOL_GUI_STYLE_TYPE_NONE },
        { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, SMOL_GUI_STYLE_TYPE_NONE },
        { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, SMOL_GUI_STYLE_TYPE_NONE }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_PRIMARY_CONTAINER
        { { 32, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 32, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 32, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 32, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_SECONDARY_CONTAINER
        { { 40, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 40, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 40, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 40, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TERTIARY_CONTAINER
        { { 48, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 48, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 48, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 48, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_BUTTON
        { { 0,  0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 24, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 8,  0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 16, 0, 8, 8 }, { 2, 2, 2, 2 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR
        { { 56, 0, 8, 8 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 56, 0, 8, 8 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 56, 0, 8, 8 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 56, 0, 8, 8 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_SHADOW
        { { 0, 8, 8, 8 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 8, 8, 8 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 8, 8, 8 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 8, 8, 8 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TICK_CHECKED
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TICK_UNCHECKED
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_RADIO_CHECKED
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 8, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_RADIO_UNCHECKED
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 24, 8, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    }
};

smol_gui_theme_t smol_gui_theme_load_default();

typedef struct _smol_gui_t {
    smol_canvas_t* canvas;
    smol_gui_theme_t theme;

    smol_i32 activeId, hoveredId;

    smol_point_t mousePosition, mouseDelta;
    int mouseClicked;
} smol_gui_t;

smol_gui_t smol_gui_create(smol_canvas_t* canvas);
void smol_gui_begin(smol_gui_t* gui);
void smol_gui_end(smol_gui_t* gui);

void smol_gui_input_mouse_move(smol_gui_t* gui, smol_point_t position, smol_point_t delta);
void smol_gui_input_mouse_click(smol_gui_t* gui, int clicked);

int smol_gui_is_mouse_down(smol_gui_t* gui, int wid);
int smol_gui_clickable_area(smol_gui_t* gui, const char* id, smol_grect_t bounds);

int smol_gui_button(
    smol_gui_t* gui, const char* id, const char* text,
    smol_grect_t bounds
);

void smol_gui_draw_style(
    smol_gui_t* gui,
    smol_gui_style_patch_type patchType,
    smol_gui_widget_state widgetState,
    smol_grect_t bounds
);

#ifdef SMOL_GUI_IMPLEMENTATION

// https://gist.github.com/sgsfak/9ba382a0049f6ee885f68621ae86079b
smol_u32 fnv32_hash(const char *str) {
    unsigned char *s = (unsigned char *)str;	/* unsigned string */

    /* See the FNV parameters at www.isthe.com/chongo/tech/comp/fnv/#FNV-param */
    const smol_u32 FNV_32_PRIME = 0x01000193; /* 16777619 */

    smol_u32 h = 0x811c9dc5; /* 2166136261 */
    while (*s) {
        /* xor the bottom with the current octet */
        h ^= *s++;
        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        h *= FNV_32_PRIME;
    }

    return h;
}

int smol_rect_has_point(smol_grect_t rect, smol_point_t point) {
    return point.x >= rect.x &&
        point.x <= rect.x + rect.width &&
        point.y >= rect.y &&
        point.y <= rect.y + rect.height;
}

smol_rectcut_t smol_rectcut_left(smol_rectcut_t* rect, int a) {
    int minx = rect->minx;
    rect->minx = min(rect->maxx, rect->minx + a);
    return (smol_rectcut_t) { minx, rect->miny, rect->minx, rect->maxy };
}

smol_rectcut_t smol_rectcut_right(smol_rectcut_t* rect, int a) {
    int maxx = rect->maxx;
    rect->maxx = max(rect->minx, rect->maxx - a);
    return (smol_rectcut_t) { rect->maxx, rect->miny, maxx, rect->maxy };
}

smol_rectcut_t smol_rectcut_top(smol_rectcut_t* rect, int a) {
    int miny = rect->miny;
    rect->miny = min(rect->maxy, rect->miny + a);
    return (smol_rectcut_t) { rect->minx, miny, rect->maxx, rect->miny };
}

smol_rectcut_t smol_rectcut_bottom(smol_rectcut_t* rect, int a) {
    int maxy = rect->maxy;
    rect->maxy = max(rect->miny, rect->maxy - a);
    return (smol_rectcut_t) { rect->minx, rect->maxy, rect->maxx, maxy };
}

void smol_rectcut_expand(smol_rectcut_t* rect, int a) {
    rect->minx -= a;
    rect->miny -= a;
    rect->maxx += a;
    rect->maxy += a;
}

// from https://gist.github.com/toboqus/5bb75442b7535b68a65906f6663ba3ce
static char values[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

static int indexOf(char* array, char value){
	int i;
	for(i = 0; *array; ++i, ++array)
		if(*array == value)
			return i;
	return -1;
}

static char valid(char value) { 		//check to see if the char is valid
	return (value < 64 && value >= 0) ? 1 : 0;
}

static unsigned char* b64decode(char* input, size_t len, size_t* outLen) {
    *outLen = 1 + ((len * 3)/4);
	unsigned char *res = malloc(*outLen), *p = res, b[4];

	for (size_t i = 0; i < len; i += 4) {
		for (size_t a = 0; a < 4; a++){
			b[a] = indexOf(values, input[i+a]);
		}

		if (!valid(b[0])) {
			*p++ = (b[0] << 2);
		} else {
			*p++ =  (b[0] << 2) | ((valid(b[1])) ? (b[1] >> 4) : 0);
			if (valid(b[1])) {
				*p++ = (b[1] << 4) | ((valid(b[2])) ? (b[2] >> 2) : 0);
				if (valid(b[2])) {
					*p++ = (b[2] << 6) | ((valid(b[3])) ? b[3] : 0);
				}
			}
		}
	}

	*p = '\0';
	return res;
}
//

smol_gui_theme_t smol_gui_theme_load_default() {
    smol_gui_theme_t theme;
    memset(&theme, 0, sizeof(smol_gui_theme_t));

    static const unsigned char* gui_theme_b64 =
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP//p43//6eN//+njf//p43//6eN//+njf//p43//6eN/wAAAP/Jycn/ycnJ/8nJyf/Jycn/ycnJ/8nJyf8AAAD/"
        "AAAA//Dw8P/w8PD/8PDw//Dw8P/w8PD/8PDw/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAP+Tk5P/k5OT/5OTk/+Tk5P/k5OT/5OTk/8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAD/2tra/9ra2v/a2tr/2tra/9ra2v/a2tr/AAAA/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/"
        "/6GG//+hhv//oYb//6GG//+hhv//oYb//6GG//+hhv8AAAD/ycnJ/8nJyf/Jycn/ycnJ/8nJyf/Jycn/AAAA/wAAAP/w8PD/8PDw//Dw8P/w8PD/8PDw//Dw8P8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAD/k5OT/5OTk/+Tk5P/k5OT/5OTk/+Tk5P/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/9zc3P/c3Nz/3Nzc/9zc3P/c3Nz/3Nzc/wAAAP8AAAD/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//+hhv//oYb//6GG//+hhv//oIP//6GE//+ghf//oYb/"
        "AAAA/8nJyf/Jycn/ycnJ/8nJyf/Jycn/ycnJ/wAAAP8AAAD/8PDw//Dw8P/w8PD/8PDw//Dw8P/w8PD/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/5OTk/+Tk5P/k5OT/5OTk/+Tk5P/k5OT/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAP/c3Nz/3Nzc/9zc3P/c3Nz/3Nzc/9zc3P8AAAD/"
        "AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/7mHn/+5h5//uYef/7mHn/+5h5//uYef/7mHn/+5h5/wAAAP/Jycn/ycnJ/8nJyf/Jycn/ycnJ/8nJyf8AAAD/"
        "AAAA//Dw8P/w8PD/8PDw//Dw8P/w8PD/8PDw/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAP+Tk5P/k5OT/5OTk/+Tk5P/k5OT/5OTk/8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAD/3Nzc/9zc3P/c3Nz/3Nzc/9zc3P/c3Nz/AAAA/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/"
        "9o9t//aPbf/2j23/9o9t//aPbf/2j23/9o9t//aPbf8AAAD/ycnJ/8nJyf/Jycn/ycnJ/8nJyf/Jycn/AAAA/wAAAP/w8PD/8PDw//Dw8P/w8PD/8PDw//Dw8P8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAD/k5OT/5OTk/+Tk5P/k5OT/5OTk/+Tk5P/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/9zc3P/c3Nz/3Nzc/9zc3P/c3Nz/3Nzc/wAAAP8AAAD/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/++BXP/vgl3/74Ne/++CXv/vg17/74Rh/++EYP/vgV3/"
        "AAAA/8nJyf/Jycn/ycnJ/8nJyf/Jycn/ycnJ/wAAAP8AAAD/8PDw//Dw8P/w8PD/8PDw//Dw8P/w8PD/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/5OTk/+Tk5P/k5OT/5OTk/+Tk5P/k5OT/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAP/c3Nz/3Nzc/9zc3P/c3Nz/3Nzc/9zc3P8AAAD/"
        "AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/vgVz/74Fc/++BXP/vgVz/74Fc/++BXf/vgV3/74Fc/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "84Jo//OCaP/zgmj/84Jo//OCaP/ygmf98oFn/vOCaP8AAAABAAAABAAAAAkAAAALAAAACwAAAAkAAAAEAAAAAgAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAABAAAAAwAAAAbAAAAIgAAACIAAAAbAAAADAAAAAUAAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAkAAAAbAAAAPwAAAFAAAABQAAAAPwAAABwAAAAM"
        "AAAA/0VFRf///////////0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX///////////9FRUX/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAALAAAAIgAAAFAAAABlAAAAZQAAAFAAAAAkAAAADwAAAP9FRUX/////////////////RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/////////////////RUVF/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAACwAAACIAAABQAAAAZQAAAGUAAABQAAAAJAAAAA8AAAD/RUVF/0VFRf////////////////9FRUX/RUVF/0VFRf9FRUX/////////////////RUVF/0VFRf8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAkAAAAbAAAAPwAAAFAAAABQAAAAPwAAABwAAAAM"
        "AAAA/0VFRf9FRUX/RUVF/////////////////0VFRf9FRUX/////////////////RUVF/0VFRf9FRUX/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAAAADAAAABwAAAAkAAAAJAAAABwAAAANAAAABQAAAP9FRUX/RUVF/0VFRf9FRUX/////////////////"
        "////////////////RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAgAAAAUAAAAMAAAADwAAAA8AAAAMAAAABQAAAAIAAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf//////////////////////RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX//////////////////////0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP9FRUX/RUVF/0VFRf9FRUX/////////////////"
        "////////////////RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/RUVF/0VFRf9FRUX/////////////////RUVF/0VFRf////////////////9FRUX/RUVF/0VFRf8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAA/0VFRf9FRUX/////////////////RUVF/0VFRf9FRUX/RUVF/////////////////0VFRf9FRUX/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP9FRUX/////////////////RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/////////////////RUVF/wAAAP8AAAD/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf8AAAD/"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD/RUVF////////////RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf///////////0VFRf8AAAD/"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAA/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/AAAA/wAAAP9FRUX/RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/"
        "RUVF/0VFRf9FRUX/RUVF/0VFRf9FRUX/RUVF/wAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=";

    const size_t gui_theme_png_width = 64;
    const size_t gui_theme_png_height = 32;
    
    size_t gui_theme_len = 0;
    unsigned char* gui_theme = b64decode(gui_theme_b64, strlen(gui_theme_b64), &gui_theme_len);

    theme.skin = smol_image_create_from_buffer(gui_theme_png_width, gui_theme_png_height, gui_theme);
    memcpy(&theme.styles, gui_theme_default_styles, sizeof(gui_theme_default_styles));

    return theme;
}

smol_gui_t smol_gui_create(smol_canvas_t* canvas) {
    smol_gui_t gui;
    memset(&gui, 0, sizeof(smol_gui_t));

    gui.canvas = canvas;
    gui.theme = smol_gui_theme_load_default();

    return gui;
}

void smol_gui_draw_style(
    smol_gui_t* gui,
    smol_gui_style_patch_type patchType,
    smol_gui_widget_state widgetState,
    smol_grect_t bounds
) {
    smol_gui_style_t style = gui->theme.styles[patchType][widgetState];
    int l = style.patchSides[0],
        r = style.patchSides[1],
        b = style.patchSides[2],
        t = style.patchSides[3];
    smol_grect_t sr = style.sourceRect;

#define draw(src, dst) smol_canvas_draw_image_subrect_streched( \
    gui->canvas, &gui->theme.skin, \
    dst.x, dst.y, dst.width, dst.height, \
    src.x, src.y, src.width, src.height \
)
    int wrl = (l + r),
        htb = (t + b);

    // top left
    if (l > 0 && t > 0) {
        smol_grect_t src = smol_rect(sr.x, sr.y, l, t);
        smol_grect_t dst = smol_rect(bounds.x, bounds.y, l, t);
        draw(src, dst);
    }

    // top center
    if (t > 0) {
        smol_grect_t src = smol_rect(sr.x + l, sr.y, sr.width - wrl, t);
        smol_grect_t dst = smol_rect(bounds.x + l, bounds.y, bounds.width - wrl, t);
        draw(src, dst);
    }

    // top right
    if (r > 0 && t > 0) {
        smol_grect_t src = smol_rect(sr.x + sr.width - l, sr.y, r, t);
        smol_grect_t dst = smol_rect(bounds.x + bounds.width - l, bounds.y, r, t);
        draw(src, dst);
    }
    
    // mid left
    if (l > 0) {
        smol_grect_t src = smol_rect(sr.x, sr.y + t, l, sr.height - htb);
        smol_grect_t dst = smol_rect(bounds.x, bounds.y + t, l, bounds.height - htb);
        draw(src, dst);
    }

    // mid center
    smol_grect_t src = smol_rect(sr.x + l, sr.y + t, sr.width - wrl, sr.height - htb);
    smol_grect_t dst = smol_rect(bounds.x + l, bounds.y + t, bounds.width - wrl, bounds.height - htb);
    draw(src, dst);

    // mid right
    if (r > 0) {
        smol_grect_t src = smol_rect(sr.x + sr.width - l, sr.y + t, r, sr.height - htb);
        smol_grect_t dst = smol_rect(bounds.x + bounds.width - l, bounds.y + t, r, bounds.height - htb);
        draw(src, dst);
    }

    // bot left
    if (l > 0 && b > 0) {
        smol_grect_t src = smol_rect(sr.x, sr.y + sr.height - t, l, b);
        smol_grect_t dst = smol_rect(bounds.x, bounds.y + bounds.height - t, l, b);
        draw(src, dst);
    }

    // bot center
    if (b > 0) {
        smol_grect_t src = smol_rect(sr.x + l, sr.y + sr.height - t, sr.width - wrl, b);
        smol_grect_t dst = smol_rect(bounds.x + l, bounds.y + bounds.height - t, bounds.width - wrl, b);
        draw(src, dst);
    }

    // bot right
    if (r > 0 && b > 0) {
        smol_grect_t src = smol_rect(sr.x + sr.width - l, sr.y + sr.height - t, r, b);
        smol_grect_t dst = smol_rect(bounds.x + bounds.width - l, bounds.y + bounds.height - t, r, b);
        draw(src, dst);
    }
}

#define SMOL_GUI_INVALID_WIDGET -1

void smol_gui_begin(smol_gui_t* gui) {
    if (!gui->mouseClicked) gui->hoveredId = SMOL_GUI_INVALID_WIDGET;
}

void smol_gui_end(smol_gui_t* gui) {
    if (!gui->mouseClicked) gui->activeId = SMOL_GUI_INVALID_WIDGET;
    gui->mouseDelta.x = 0;
    gui->mouseDelta.y = 0;
}

void smol_gui_input_mouse_move(smol_gui_t* gui, smol_point_t position, smol_point_t delta) {
    gui->mousePosition.x = position.x;
    gui->mousePosition.y = position.y;
    gui->mouseDelta.x = delta.x;
    gui->mouseDelta.y = delta.y;
}

void smol_gui_input_mouse_click(smol_gui_t* gui, int clicked) {
    gui->mouseClicked = clicked;
}

int smol_gui_is_mouse_down(smol_gui_t* gui, int wid) {
    return gui->hoveredId == wid && gui->activeId == wid;
}

int smol_gui_clickable_area(smol_gui_t* gui, const char* id, smol_grect_t bounds) {
    smol_u32 wid = fnv32_hash(id);

    if (smol_rect_has_point(bounds, gui->mousePosition)) {
        gui->hoveredId = wid;

        if (gui->mouseClicked && gui->activeId == SMOL_GUI_INVALID_WIDGET) {
            gui->activeId = wid;
        }
    }

    if (!gui->mouseClicked && smol_gui_is_mouse_down(gui, wid)) {
        return 1;
    }

    return 0;
}

static smol_gui_widget_state smol_gui_widget_state_from_gui(smol_gui_t* gui, const char* id) {
    smol_u32 wid = fnv32_hash(id);
    smol_gui_widget_state state = SMOL_GUI_WIDGET_STATE_IDLE;
    
    if (gui->hoveredId == wid) {
        state = SMOL_GUI_WIDGET_STATE_HOVERED;
        if (gui->activeId == wid) {
            state = SMOL_GUI_WIDGET_STATE_ACTIVE;
        }
    }

    return state;
}

int smol_gui_button(
    smol_gui_t* gui, const char* id, const char* text,
    smol_grect_t bounds
) {
    smol_canvas_t* canvas = gui->canvas;

    int result = smol_gui_clickable_area(gui, id, bounds);

    smol_gui_widget_state state = smol_gui_widget_state_from_gui(gui, id);
    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_SHADOW, SMOL_GUI_WIDGET_STATE_IDLE, smol_rect(bounds.x - 1, bounds.y - 1, bounds.width + 2, bounds.height + 3));
    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_BUTTON, state, bounds);

    smol_canvas_push_color(canvas);
    smol_canvas_set_color(canvas, gui->theme.styles[SMOL_GUI_STYLE_PATCH_TYPE_BUTTON][state].foreground);

    int w, h;
    smol_text_size(canvas, 1, text, &w, &h);

    smol_canvas_push_scissor(canvas);
    smol_canvas_set_scissor(canvas, bounds.x, bounds.y, bounds.width, bounds.height);

    smol_canvas_draw_text(
        canvas,
        bounds.x + (bounds.width / 2 - w / 2),
        bounds.y + (bounds.height / 2 - h / 2) + 1,
        1,
        text
    );
    smol_canvas_pop_scissor(canvas);
    smol_canvas_pop_color(canvas);

    return result;
}

#endif

#endif // SMOL_GUI_H