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
        { { 128, 0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 128, 0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 128, 0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 128, 0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_SECONDARY_CONTAINER
        { { 160, 0, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 160, 0, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 160, 0, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 160, 0, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TERTIARY_CONTAINER
        { { 192, 0, 32, 32 }, { 7, 7, 7, 7 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 192, 0, 32, 32 }, { 7, 7, 7, 7 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 192, 0, 32, 32 }, { 7, 7, 7, 7 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 192, 0, 32, 32 }, { 7, 7, 7, 7 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_BUTTON
        { { 0,  0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 96, 0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 32, 0, 32, 32 }, { 5, 5, 5, 5 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 64, 0, 32, 32 }, { 5, 5, 5, 5 }, { 255, 255, 255, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR
        { { 224, 0, 32, 32 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 224, 0, 32, 32 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 224, 0, 32, 32 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 224, 0, 32, 32 }, { 3, 3, 3, 3 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_SHADOW
        { { 0, 32, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 32, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 32, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH },
        { { 0, 32, 32, 32 }, { 8, 8, 8, 8 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_PATCH }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TICK_CHECKED
        { { 241, 32, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 241, 32, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 241, 32, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 241, 32, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_TICK_UNCHECKED
        { { 241, 49, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 241, 49, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 241, 49, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 241, 49, 14, 15 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_RADIO_CHECKED
        { { 224, 33, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 224, 33, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 224, 33, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 224, 33, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
    },

    { // SMOL_GUI_STYLE_PATCH_TYPE_RADIO_UNCHECKED
        { { 224, 49, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 224, 49, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 224, 49, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON },
        { { 224, 49, 16, 16 }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, SMOL_GUI_STYLE_TYPE_ICON }
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
        "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"
        "A/3o/8fHx4z/ycnJ8zbK/7S0tPMDwP+rq6vB/+3t7f82yI2I/7i4uLcD/wADDAH/AAMMBP8AAwwH/wADDA4V/wADDB3/AAMMI/8AAwwn/wADDCn/AAMMKsD/AAMMK8H/"
        "AAMMLME8wTHBJhAkIv8AAwwVPTsPBAPeI8AzxCPCM8YjwjPEI8ADxiPCM8YjwgP96P/o6OgR/6enp8H/3t7e/zbI/8vLy/MD/+3t7Q4D/8XFxYz/vb298TeiiMYd/6+v"
        "r/H/1tbWjAP/AAMMAf8AAwwC/wADDAQ7Jx4//wADDBb/AAMMGMH/AAMMGccrwhU/Hic7DzkuA+Aj2gPMI8YD/ez/7e3tBAP/qqqq8f/b29v/tIjGFv+lpaWV/+bm5g4D"
        "wD3/09PTjP+2tra3nYjGqIj/2dnZjD0DLsAE/wADDAX/AAMMCP8AAwwLMv8AAwwOwAjB/wADDBDFCMI9wCf/AAMMCjD/AAMMBAQuwAPgI9oDzCPGA/3t/+3t7Q4D/6am"
        "psH/v7+/8zewiDbAnYiLiP+0tLTz/8PDw5X/5ubmDgP9/f34/+3t7QT/7OzsEf/T09OO/7a2trn/qqqqvP+zs7PM/7Gxscf/p6enuv+8vLy3/+rq6gD/7e3tDgP9/f36"
        "/u3t7YyIg4iXiP7W1taqiECRiP6rq6u7iL+IIwP9/f33I/7Hx8eRiP7x8fGriMNVK/6qqqr+0tLSIwP9/f31I/7JyckaNQTGmoj+srKy/tXV1SMD/f398//t7e0E/9zc"
        "3AD+t7e3/vr6+gTImIj+p6en/uzs7AP9/f3z/+3t7Qb/vr6+AP7u7u4Eyv7X19eaiAP9/f3z/+Xl5RH/tra2AATLmoj+tLS0A/39/fP+1NTUwATM/q+vrwP9/f3z/s3N"
        "zQIEwEAqnYgfVR/APSomBMD+v7+//gCkOf39/fP+zc3NArqImoidiMg9Jv64uLj+AKQ5/f398/7Y2NgxAcsUCQP9/f3z/urq6v6oqKj+6+vrAcoog4gD/f398w8pBwHK"
        "DDcD/f399P7o6OgJAgHI/svLy5iIIwP9/f30Iyz+qqqq/tvb2wHGJf6lpaX+5ubmA/39/fYjCv6mpqYxAjIBwBQZDC3+5ubmA/39/fgjFIeIgog2qYhACbWIvogjA/39"
        "/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39"
        "/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39/f39"
        "1AAAAAAAAAAB";

    size_t gui_theme_len = 0;
    unsigned char* gui_theme = base64_decode(gui_theme_b64, &gui_theme_len);

    theme.skin = smol_load_image_qoi("D:\\Projects\\smol_libs\\res\\gfx\\gui.qoi");//smol_load_image_qoi_from_memory(gui_theme, gui_theme_len);
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

typedef struct _span_t {
    size_t position; size_t length;
    size_t width, height;
} span_t;

int _char_is_any_of(const char* str, char ch) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == ch) return 1;
    }
    return 0;
}

int smol_span_find_next(const char* buf, const char* delim, span_t* span) {
    span->position += span->length + 1;
    span->length = 0;

#define current buf[span->position + span->length]
    while (current != 0 && !_char_is_any_of(delim, current)) {
        span->length++;
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

    span_t ptr;
    memset(&ptr, 0, sizeof(span_t));
    smol_span_find_next(text, delim, &ptr);

    smol_vector(span_t) lines;
    smol_vector_init(&lines, 128);

#define lastChar (*(text + currentSpan.position + currentSpan.length - 1))
#define pushline(sw) do {\
    size_t adv = 0; \
    if (lastChar == ' ' || lastChar == '\0') { \
        currentSpan.length--; \
        currentSpan.width -= sw; \
        adv++; \
    } \
    currentSpan.height = h; \
    smol_vector_push(&lines, currentSpan); \
    currentSpan.position += currentSpan.length + adv; \
    currentSpan.length = 0; \
    currentSpan.width = 0; \
} while (0)

    int spaceW, spaceH;
    smol_text_size(gui->canvas, 1, " ", &spaceW, &spaceH);

    int w, h;
    span_t currentSpan;
    memset(&currentSpan, 0, sizeof(span_t));

    while (1) {
        char txt[1024] = { 0 };
        strncpy(txt, text + ptr.position, ptr.length);

        smol_text_size(gui->canvas, 1, txt, &w, &h);
        if (currentSpan.width + w >= bounds.width) {
            pushline(spaceW);
        }

        size_t len = strlen(txt);

        currentSpan.width += w + spaceW;
        currentSpan.length += len + 1;

        for (size_t i = 0; i < len; i++) {
            if (txt[i] == '\n') {
                pushline(spaceW);
                break;
            }
        }

        if (!smol_span_find_next(text, delim, &ptr)) {
            break;
        }
    }

    pushline(spaceW);

    int totalHeight = 0;
    span_t* lineData = smol_vector_iterate(&lines, i) {
        totalHeight += lineData[i].height;
    };

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
    
    lineData = smol_vector_iterate(&lines, i) {
        int x = 0;
        switch (halign) {
            case SMOL_GUI_TEXT_ALIGN_NEAR: x = 0; break;
            case SMOL_GUI_TEXT_ALIGN_CENTER: x = bounds.width / 2 - lineData[i].width / 2; break;
            case SMOL_GUI_TEXT_ALIGN_FAR: x = bounds.width - lineData[i].width; break;
        }

        smol_canvas_draw_text_formated(
            gui->canvas, x + bounds.x, y + bounds.y, 1, "%.*s", lineData[i].length, text + lineData[i].position
        );

        y += lineData[i].height;
    };
    smol_canvas_pop_scissor(gui->canvas);

    //smol_canvas_draw_rect(gui->canvas, bounds.x, bounds.y, bounds.width, bounds.height);

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
    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_SHADOW, SMOL_GUI_WIDGET_STATE_IDLE, smol_rect(bounds.x - 1, bounds.y - 1, bounds.width + 2, bounds.height + 3));
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
    // smol_grect_t prog = smol_rect(bounds.x, bounds.y, normVal * (bounds.width - btnWidth + 1), bounds.height);

    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_SHADOW, SMOL_GUI_WIDGET_STATE_IDLE, smol_rect(bounds.x - 1, bounds.y - 1, bounds.width + 2, bounds.height + 3));
    smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_SECONDARY_CONTAINER, SMOL_GUI_WIDGET_STATE_IDLE, bounds);
    // smol_gui_draw_style(gui, SMOL_GUI_STYLE_PATCH_TYPE_PROGRESS_BAR, SMOL_GUI_WIDGET_STATE_IDLE, prog);

    smol_gui_draw_style(
        gui, SMOL_GUI_STYLE_PATCH_TYPE_BUTTON, SMOL_GUI_WIDGET_STATE_IDLE,
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