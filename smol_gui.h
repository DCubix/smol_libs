#ifndef SMOL_GUI_H
#define SMOL_GUI_H

#ifndef SMOL_CANVAS_H
#error Please include smol_canvas before smol_gui
#endif

#ifndef SMOL_UTILS_H
#error Please include smol_utils before smol_gui
#endif

#include <math.h>
#include <assert.h>

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

typedef enum _smol_gui_text_align {
    SMOL_GUI_TEXT_ALIGN_NEAR = 0,
    SMOL_GUI_TEXT_ALIGN_CENTER,
    SMOL_GUI_TEXT_ALIGN_FAR
} smol_gui_text_align;

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
        { { 64, 0, 16, 16 }, { 4, 4, 4, 4 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 64, 0, 16, 16 }, { 4, 4, 4, 4 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 64, 0, 16, 16 }, { 4, 4, 4, 4 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 64, 0, 16, 16 }, { 4, 4, 4, 4 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_SECONDARY_CONTAINER
        { { 80, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 80, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 80, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 80, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TERTIARY_CONTAINER
        { { 96, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 96, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 96, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 96, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_BUTTON
        { { 0,  0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 48, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 16, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 32, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR
        { { 112, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 112, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 112, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 112, 0, 16, 16 }, { 6, 6, 6, 6 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_SHADOW
        { { 0, 16, 16, 16 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 16, 16, 16 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 16, 16, 16 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 16, 16, 16 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TICK_CHECKED
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TICK_UNCHECKED
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_RADIO_CHECKED
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 112, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_RADIO_UNCHECKED
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 96, 16, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
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

void smol_gui_draw_style(
    smol_gui_t* gui,
    smol_gui_style_patch_type patchType,
    smol_gui_widget_state widgetState,
    smol_grect_t bounds
);

int smol_gui_is_mouse_down(smol_gui_t* gui, int wid);
int smol_gui_clickable_area(smol_gui_t* gui, const char* id, smol_grect_t bounds);
int smol_gui_holdable_area(smol_gui_t* gui, const char* id, smol_grect_t bounds);

int smol_gui_xdrag_area(smol_gui_t* gui, const char* id, smol_grect_t bounds);
int smol_gui_ydrag_area(smol_gui_t* gui, const char* id, smol_grect_t bounds);
int smol_gui_draggable_area(
    smol_gui_t* gui, const char* id,
    smol_gui_drag_axis axis,
    smol_grect_t bounds,
    int* outX, int* outY,
    double xStep, double yStep
);

int smol_gui_button(
    smol_gui_t* gui, const char* id, const char* text,
    smol_grect_t bounds
);

typedef struct _smol_number_t smol_number_t;

smol_number_t smol_number_add(smol_number_t a, smol_number_t b);
smol_number_t smol_number_sub(smol_number_t a, smol_number_t b);
smol_number_t smol_number_mul(smol_number_t a, smol_number_t b);
smol_number_t smol_number_div(smol_number_t a, smol_number_t b);
smol_number_t smol_number_muls(smol_number_t a, double b);
smol_number_t smol_number_round(smol_number_t a);
smol_number_t smol_number_min(smol_number_t a, smol_number_t b);
smol_number_t smol_number_max(smol_number_t a, smol_number_t b);
smol_number_t smol_number_snap(smol_number_t a, smol_number_t step);
int smol_number_diff(smol_number_t a, smol_number_t b);
double smol_number_norm(smol_number_t value, smol_number_t minValue, smol_number_t maxValue);

int smol_gui_slideri(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    smol_i64* value,
    smol_i64 minValue, smol_i64 maxValue,
    smol_i64 step
);

int smol_gui_sliderf(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    float* value,
    float minValue, float maxValue,
    float step
);

int smol_gui_sliderd(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    double* value,
    double minValue, double maxValue,
    double step
);

#define SMOL_GUI_SLIDER_SENS 0.55
#define SMOL_GUI_INVALID_WIDGET -1

#ifdef SMOL_GUI_IMPLEMENTATION
typedef struct _smol_number_t {
    enum {
        SMOL_NUMBER_TYPE_INT = 0,
        SMOL_NUMBER_TYPE_FLOAT,
        SMOL_NUMBER_TYPE_DOUBLE
    } type;

    union {
        smol_i64 intValue;
        float floatValue;
        double doubleValue;
    };
} smol_number_t;

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

// from https://github.com/elzoughby/Base64/blob/master/base64.c

char base46_map[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

static char* base64_decode(char* cipher, size_t* outlen) {
    int len = strlen(cipher) * 3 / 4;

    char counts = 0;
    char buffer[4];
    char* plain = malloc(len * sizeof(char));
    int i = 0, p = 0;

    for (i = 0; cipher[i] != '\0'; i++) {
        char k;
        for (k = 0; k < 64 && base46_map[k] != cipher[i]; k++);
        buffer[counts++] = k;
        if (counts == 4) {
            plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
            if (buffer[2] != 64)
                plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
            if (buffer[3] != 64)
                plain[p++] = (buffer[2] << 6) + buffer[3];
            counts = 0;
        }
    }

    *outlen = p;

    plain[p] = '\0';
    return plain;
}
//

smol_gui_theme_t smol_gui_theme_load_default() {
    smol_gui_theme_t theme;
    memset(&theme, 0, sizeof(smol_gui_theme_t));

    static const unsigned char* gui_theme_b64 =
        "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";

    size_t gui_theme_len = 0;
    unsigned char* gui_theme = base64_decode(gui_theme_b64, &gui_theme_len);

    theme.skin = smol_load_image_qoi_from_memory(gui_theme, gui_theme_len);
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

    if (bounds.width < l + r) {
        l = bounds.width/2;
        r = bounds.width/2;
    }
    if (bounds.height < t + b) {
        t = bounds.height / 2;
        b = bounds.height / 2;
    }

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

typedef smol_span(char) char_span_t;

int _char_is_any_of(const char* str, char ch) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == ch) return 1;
    }
    return 0;
}

int smol_span_find_next(const char* delim, char_span_t* span) {
    span->data += span->count;
    span->count = 0;

#define current span->data[span->count]
    while (current != 0 && !_char_is_any_of(delim, current)) {
        span->count++;
    }
    if (current == 0) return 0; // not found
    return 1;
}

static void smol_gui_draw_text_ww(
    smol_gui_t* gui,
    const char* text,
    smol_gui_text_align halign,
    smol_gui_text_align valign,
    smol_gui_style_patch_type patchType,
    smol_gui_widget_state widgetState,
    smol_grect_t bounds
) {
    smol_gui_style_t style = gui->theme.styles[patchType][widgetState];
    const char* delim = " \t";

    char_span_t ptr;
    ptr.count = 0;
    ptr.data = text;

    smol_vector(char_span_t) lines;
    smol_vector_init(&lines, 128);

#define lastChar (*(currentSpan.data + currentSpan.count - 1))
#define pushline(sw) do {\
    size_t adv = 0; \
    if (lastChar == ' ' || lastChar == '\0') { \
        currentSpan.count--; \
        currentWidth -= sw; \
        adv++; \
    } \
    smol_vector_push(&lines, currentSpan); \
    currentSpan.data += currentSpan.count + adv; \
    currentSpan.count = 0; \
    currentWidth = 0; \
    totalHeight += h; \
} while (0)

    int spaceW, spaceH;
    smol_text_size(gui->canvas, 1, " ", &spaceW, &spaceH);

    int w, h;
    char_span_t currentSpan;
    memset(&currentSpan, 0, sizeof(char_span_t));

    currentSpan.data = ptr.data;

    int currentWidth = 0,
        totalHeight = 0;

    while (1) {
        smol_span_find_next(delim, &ptr);

        char txt[1024] = { 0 };
        strncpy(txt, ptr.data, ptr.count);

        smol_text_size(gui->canvas, 1, txt, &w, &h);
        if (currentWidth + w >= bounds.width) {
            pushline(spaceW);
        }

        size_t len = strlen(txt);

        currentWidth += w + spaceW;
        currentSpan.count += len + 1;
        ptr.count++; // include space

        for (size_t i = 0; i < len; i++) {
            if (txt[i] == '\n') {
                pushline(spaceW);
                break;
            }
        }

        if (ptr.data[ptr.count] == NULL) break;
    }

    pushline(spaceW);

    int y = 0;
    switch (valign) {
        case SMOL_GUI_TEXT_ALIGN_NEAR: y = 0; break;
        case SMOL_GUI_TEXT_ALIGN_CENTER: y = bounds.height / 2 - totalHeight / 2; break;
        case SMOL_GUI_TEXT_ALIGN_FAR: y = bounds.height - totalHeight; break;
    }

    smol_canvas_push_color(gui->canvas);
    smol_canvas_set_color(gui->canvas, style.foreground);

    smol_canvas_push_scissor(gui->canvas);
    smol_canvas_set_scissor(gui->canvas, bounds.x, bounds.y, bounds.width, bounds.height);
    
    char_span_t* lineData = smol_vector_iterate(&lines, i) {
        char txt[4096] = { 0 };
        strncpy(txt, lineData[i].data, lineData[i].count);

        int lw, lh;
        smol_text_size(gui->canvas, 1, txt, &lw, &lh);

        int x = 0;
        switch (halign) {
            case SMOL_GUI_TEXT_ALIGN_NEAR: x = 0; break;
            case SMOL_GUI_TEXT_ALIGN_CENTER: x = bounds.width / 2 - lw / 2; break;
            case SMOL_GUI_TEXT_ALIGN_FAR: x = bounds.width - lw; break;
        }

        smol_canvas_draw_text_formated(
            gui->canvas, x + bounds.x, y + bounds.y, 1, "%.*s", lineData[i].count, lineData[i].data
        );

        y += lh;
    };
    smol_canvas_pop_scissor(gui->canvas);

    smol_canvas_pop_color(gui->canvas);

    smol_vector_free(&lines);
}

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

#define _SMOL_NUMBER_OP(op) switch (res.type) { \
    case SMOL_NUMBER_TYPE_INT: res.intValue = a.intValue op b.intValue; break; \
    case SMOL_NUMBER_TYPE_FLOAT: res.floatValue = a.floatValue op b.floatValue; break; \
    case SMOL_NUMBER_TYPE_DOUBLE: res.doubleValue = a.doubleValue op b.doubleValue; break; \
}

smol_number_t smol_number_add(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);

    smol_number_t res;
    res.type = a.type;

    _SMOL_NUMBER_OP(+)

    return res;
}

smol_number_t smol_number_sub(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);

    smol_number_t res;
    res.type = a.type;

    _SMOL_NUMBER_OP(-)

    return res;
}

smol_number_t smol_number_mul(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);

    smol_number_t res;
    res.type = a.type;

    _SMOL_NUMBER_OP(*)

    return res;
}

smol_number_t smol_number_div(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);

    smol_number_t res;
    res.type = a.type;

    _SMOL_NUMBER_OP(/)

    return res;
}

smol_number_t smol_number_muls(smol_number_t a, double b) {
    smol_number_t res;
    res.type = a.type;

    switch (res.type) {
        case SMOL_NUMBER_TYPE_INT: res.intValue = (int)((double)a.intValue * b); break;
        case SMOL_NUMBER_TYPE_FLOAT: res.floatValue = a.floatValue * (float)b; break;
        case SMOL_NUMBER_TYPE_DOUBLE: res.doubleValue = a.doubleValue * b; break;
    }

    return res;
}

smol_number_t smol_number_round(smol_number_t a) {
    smol_number_t res;
    res.type = a.type;

    switch (res.type) {
        case SMOL_NUMBER_TYPE_INT: res.intValue = a.intValue; break;
        case SMOL_NUMBER_TYPE_FLOAT: res.floatValue = roundf(a.floatValue); break;
        case SMOL_NUMBER_TYPE_DOUBLE: res.doubleValue = round(a.doubleValue); break;
    }

    return res;
}

smol_number_t smol_number_min(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);
    smol_number_t res;
    res.type = a.type;
    switch (res.type) {
        case SMOL_NUMBER_TYPE_INT: res.intValue = min(a.intValue, b.intValue); break;
        case SMOL_NUMBER_TYPE_FLOAT: res.floatValue = min(a.floatValue, b.floatValue); break;
        case SMOL_NUMBER_TYPE_DOUBLE: res.doubleValue = min(a.doubleValue, b.doubleValue); break;
    }
    return res;
}

smol_number_t smol_number_max(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);
    smol_number_t res;
    res.type = a.type;
    switch (res.type) {
        case SMOL_NUMBER_TYPE_INT: res.intValue = max(a.intValue, b.intValue); break;
        case SMOL_NUMBER_TYPE_FLOAT: res.floatValue = max(a.floatValue, b.floatValue); break;
        case SMOL_NUMBER_TYPE_DOUBLE: res.doubleValue = max(a.doubleValue, b.doubleValue); break;
    }
    return res;
}

smol_number_t smol_number_snap(smol_number_t a, smol_number_t step) {
    assert(a.type == step.type);

    smol_number_t res;
    res.type = a.type;

    switch (res.type) {
        case SMOL_NUMBER_TYPE_INT: {
            res.intValue = (int)((double)(a.intValue / step.intValue) * (double)step.intValue);
        } break;
        case SMOL_NUMBER_TYPE_FLOAT: {
            res.floatValue = a.floatValue;
            res.floatValue -= fmodf(res.floatValue, step.floatValue);
        } break;
        case SMOL_NUMBER_TYPE_DOUBLE: {
            res.doubleValue = a.doubleValue;
            res.doubleValue -= fmod(res.doubleValue, step.doubleValue);
        } break;
    }
    return res;
}

int smol_number_diff(smol_number_t a, smol_number_t b) {
    assert(a.type == b.type);
    switch (a.type) {
        case SMOL_NUMBER_TYPE_INT: return a.intValue != b.intValue;
        case SMOL_NUMBER_TYPE_FLOAT: return a.floatValue != b.floatValue;
        case SMOL_NUMBER_TYPE_DOUBLE: return a.doubleValue != b.doubleValue;
    }
}

double smol_number_norm(smol_number_t value, smol_number_t minValue, smol_number_t maxValue) {
    assert(value.type == minValue.type);
    assert(value.type == maxValue.type);
    assert(maxValue.type == minValue.type);

    switch (value.type) {
        case SMOL_NUMBER_TYPE_INT: return (double)(value.intValue - minValue.intValue) / (maxValue.intValue - minValue.intValue);
        case SMOL_NUMBER_TYPE_FLOAT: return (double)(value.floatValue - minValue.floatValue) / (maxValue.floatValue - minValue.floatValue);
        case SMOL_NUMBER_TYPE_DOUBLE: return (value.doubleValue - minValue.doubleValue) / (maxValue.doubleValue - minValue.doubleValue);
    }
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

int smol_gui_holdable_area(smol_gui_t* gui, const char* id, smol_grect_t bounds) {
    smol_u32 wid = fnv32_hash(id);

    if (smol_rect_has_point(bounds, gui->mousePosition)) {
        gui->hoveredId = wid;

        if (gui->mouseClicked) {
            gui->activeId = wid;
        }
    }

    if (gui->mouseClicked && smol_gui_is_mouse_down(gui, wid)) {
        return 1;
    }

    return 0;
}

int smol_gui_xdrag_area(smol_gui_t* gui, const char* id, smol_grect_t bounds) {
    smol_u32 wid = fnv32_hash(id);

    if (smol_rect_has_point(bounds, gui->mousePosition)) {
        gui->hoveredId = wid;

        if (gui->mouseClicked && gui->activeId == SMOL_GUI_INVALID_WIDGET) {
            gui->activeId = wid;
        }
    }

    if (gui->mouseClicked && smol_gui_is_mouse_down(gui, wid) && abs(gui->mouseDelta.x) > 0) {
        return gui->mouseDelta.x;
    }

    return 0;
}

int smol_gui_ydrag_area(smol_gui_t* gui, const char* id, smol_grect_t bounds) {
    smol_u32 wid = fnv32_hash(id);

    if (smol_rect_has_point(bounds, gui->mousePosition)) {
        gui->hoveredId = wid;

        if (gui->mouseClicked && gui->activeId == SMOL_GUI_INVALID_WIDGET) {
            gui->activeId = wid;
        }
    }

    if (gui->mouseClicked && smol_gui_is_mouse_down(gui, wid) && abs(gui->mouseDelta.y) > 0) {
        return gui->mouseDelta.y;
    }

    return 0;
}

int smol_gui_draggable_area(
    smol_gui_t* gui, const char* id,
    smol_gui_drag_axis axis,
    smol_grect_t bounds,
    int* outX, int* outY,
    double xStep, double yStep
) {
    smol_u32 wid = fnv32_hash(id);

    if (smol_rect_has_point(bounds, gui->mousePosition)) {
        gui->hoveredId = wid;

        if (gui->mouseClicked && gui->activeId == SMOL_GUI_INVALID_WIDGET) {
            gui->activeId = wid;
        }
    }

    int result = 0;
    if (smol_gui_is_mouse_down(gui, wid)) {
        if (axis & SMOL_GUI_DRAG_AXIS_X == SMOL_GUI_DRAG_AXIS_X) {
            if (outX) *outX += gui->mouseDelta.x * xStep;
            result = 1;
        }
        if (axis & SMOL_GUI_DRAG_AXIS_Y == SMOL_GUI_DRAG_AXIS_Y) {
            if (outY) *outY += gui->mouseDelta.y * yStep;
            result = 1;
        }
    }

    return result;
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
    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_BUTTON, state, bounds);

    smol_gui_draw_text_ww(
        gui,
        text,
        SMOL_GUI_TEXT_ALIGN_CENTER, SMOL_GUI_TEXT_ALIGN_CENTER,
        SMOL_GUI_STYLE_PATCH_TYPE_BUTTON,
        state,
        bounds
    );

    return result;
}

static int smol_gui_slider(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    smol_number_t* value,
    smol_number_t minValue, smol_number_t maxValue,
    smol_number_t step
) {
    const int btnWidth = 16;

    int changed = 0;
    int held = smol_gui_holdable_area(gui, id, bounds);

    smol_number_t maxMin = smol_number_sub(maxValue, minValue);

    if (held) {
        smol_number_t oldValue = *value;

        double normX = (double)(gui->mousePosition.x - bounds.x) / (bounds.width - btnWidth);

        *value = smol_number_add(minValue, smol_number_muls(maxMin, normX));
        *value = smol_number_snap(*value, step);
        *value = smol_number_max(smol_number_min(*value, maxValue), minValue);

        if (smol_number_diff(oldValue, *value)) changed = 1;
    }

    double normVal = smol_number_norm(*value, minValue, maxValue);
    smol_grect_t prog = smol_rect(bounds.x, bounds.y, normVal * (bounds.width - btnWidth + 1), bounds.height);

    smol_gui_style_t pbarStyle = gui->theme.styles[SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR][SMOL_GUI_WIDGET_STATE_IDLE];
    int l = pbarStyle.patchSides[0],
        r = pbarStyle.patchSides[1],
        b = pbarStyle.patchSides[2],
        t = pbarStyle.patchSides[3];

    prog.x += 1;
    prog.y += 1;
    prog.width -= 2;
    prog.height -= 2;
    prog.width += r;

    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_SECONDARY_CONTAINER, SMOL_GUI_WIDGET_STATE_IDLE, bounds);
    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR, SMOL_GUI_WIDGET_STATE_IDLE, prog);

    smol_gui_widget_state state = smol_gui_widget_state_from_gui(gui, id);
    smol_gui_draw_style(
        gui, SMOL_GUI_STYLE_PATCH_TYPE_BUTTON, state,
        smol_rect(bounds.x + normVal * (bounds.width - btnWidth), bounds.y, btnWidth, bounds.height)
    );

    return changed;
}

#define _SMOL_GUI_SLIDER_IMPL(vl, T) \
smol_number_t nvalue; nvalue.type = T; \
nvalue.##vl = *value; \
smol_number_t nmin; nmin.type = T; \
nmin.##vl = minValue; \
smol_number_t nmax; nmax.type = T; \
nmax.##vl = maxValue; \
smol_number_t nstep; nstep.type = T; \
nstep.##vl = step; \
int result = smol_gui_slider( \
    gui, id, bounds, \
    &nvalue, nmin, nmax, nstep \
); \
*value = nvalue.##vl; \
return result

int smol_gui_slideri(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    smol_i64* value,
    smol_i64 minValue, smol_i64 maxValue,
    smol_i64 step
) {
    _SMOL_GUI_SLIDER_IMPL(intValue, SMOL_NUMBER_TYPE_INT);
}

int smol_gui_sliderf(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    float* value,
    float minValue, float maxValue,
    float step
) {
    _SMOL_GUI_SLIDER_IMPL(floatValue, SMOL_NUMBER_TYPE_FLOAT);
}

int smol_gui_sliderd(
    smol_gui_t* gui, const char* id,
    smol_grect_t bounds,
    double* value,
    double minValue, double maxValue,
    double step
) {
    _SMOL_GUI_SLIDER_IMPL(doubleValue, SMOL_NUMBER_TYPE_DOUBLE);
}

#endif

#endif // SMOL_GUI_H