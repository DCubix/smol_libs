#ifndef SMOL_GUI_H
#define SMOL_GUI_H

#ifndef SMOL_CANVAS_H
#error Please include smol_canvas before smol_gui
#endif

#ifndef SMOL_UTILS_H
#error Please include smol_utils before smol_gui
#endif

typedef struct _smol_rect_t {
    int x, y, width, height;
} smol_rect_t;

#define smol_rect(x, y, w, h) (smol_rect_t){ x, y, w, h }

int smol_rect_has_point(smol_rect_t rect, smol_rect_t point);

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

typedef enum _smol_gui_widget_state {
    SMOL_GUI_WIDGET_STATE_IDLE = 0,
    SMOL_GUI_WIDGET_STATE_DISABLED,
    SMOL_GUI_WIDGET_STATE_HOVERED,
    SMOL_GUI_WIDGET_STATE_ACTIVE
} smol_gui_widget_state;

typedef enum _smol_gui_drag_axis {
    SMOL_GUI_DRAG_AXIS_X = (1 << 0),
    SMOL_GUI_DRAG_AXIS_Y = (1 << 1),
    SMOL_GUI_DRAG_AXIS_XY = SMOL_GUI_DRAG_AXIS_X | SMOL_GUI_DRAG_AXIS_Y
} smol_gui_drag_axis;

typedef struct _smol_gui_style_t {
    smol_image_t skin;
} smol_gui_style_t;

#ifdef SMOL_GUI_IMPLEMENTATION

int smol_rect_has_point(smol_rect_t rect, smol_rect_t point) {
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

#endif

#endif // SMOL_GUI_H