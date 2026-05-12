/* Stellarium Web Engine - Copyright (c) 2022 - Stellarium Labs SRL
 *
 * This program is licensed under the terms of the GNU AGPL v3, or
 * alternatively under a commercial licence.
 *
 * The terms of the AGPL v3 license can be found in the main directory of this
 * repository.
 */

#include "swe.h"

// Render a pointer around the selected object.
// This is convenient to put this as a module, because it has to be rendered
// Before the UI.

typedef struct pointer {
    obj_t           obj;
    bool            visible;
} pointer_t;

static int pointer_init(obj_t *obj, json_value *args)
{
    pointer_t *pointer = (void*)obj;
    pointer->visible = true;
    return 0;
}

// Pulsating red concentric circle implementation
static int pointer_render(obj_t *obj, const painter_t *painter_)
{
    double win_pos[2], win_size[2], angle;
    const double T = 1.5;    // Animation period (seconds).
    double r, pulse, alpha;
    double size[2];
    const pointer_t *pointer = (const pointer_t*)obj;
    obj_t *selection = core->selection;
    painter_t painter = *painter_;

    if (!pointer->visible) return 0;
    if (!selection) return 0;

    // If the selection has a custom rendering method, we use it.
    if (selection->klass->render_pointer) {
        vec4_set(painter.color, 1, 1, 1, 1);
        selection->klass->render_pointer(selection, &painter);
        return 0;
    }

    obj_get_2d_ellipse(selection, painter.obs, painter.proj,
                       win_pos, win_size, &angle);

    // Base radius at object edge
    r = fmax(win_size[0], win_size[1]) * 0.5;
    r = fmax(r, 3);  // Minimum radius for tiny objects

    // Ripple animation: circle expands outward and fades away, then repeats
    // pulse goes from 0 to 1 over the animation period
    pulse = fmod(sys_get_unix_time() / T, 1.0);  // 0 to 1, sawtooth wave

    // Radius expands from edge outward by 10 pixels
    r += pulse * 10;

    // Alpha fades from 1.0 to 0.0 as circle expands
    alpha = 1.0 - pulse;

    // Set red color with fading alpha
    vec4_set(painter.color, 1, 0, 0, alpha);
    painter.lines.width = 4;

    // Draw the expanding/fading circle
    size[0] = r;
    size[1] = r;
    paint_2d_ellipse(&painter, NULL, 0, win_pos, size, NULL);

    return 0;
}

#if 0
// Original implementation: four strokes around the object
static int pointer_render_old(obj_t *obj, const painter_t *painter_)
{
    int i;
    double win_pos[2], win_size[2], angle;
    const double T = 2.0;    // Animation period.
    double r, transf[3][3];
    bool skip_top_bar = false;
    const pointer_t *pointer = (const pointer_t*)obj;
    obj_t *selection = core->selection;
    painter_t painter = *painter_;

    if (!pointer->visible) return 0;
    vec4_set(painter.color, 1, 1, 1, 1);
    if (!selection) return 0;

    // If the selection has a custom rendering method, we use it.
    if (selection->klass->render_pointer) {
        selection->klass->render_pointer(selection, &painter);
        return 0;
    }

    obj_get_2d_ellipse(selection, painter.obs, painter.proj,
                       win_pos, win_size, &angle);
    r = fmax(win_size[0], win_size[1]);
    r += 5;

    // Draw four strokes around the object.
    // Skip the upper stroke if the selection has a label on top.
    skip_top_bar = labels_has_obj(selection);

    for (i = 0; i < 4; i++) {
        if (skip_top_bar && i == 3) continue;
        r = fmax(r, 8);
        r += 0.4 * (sin(sys_get_unix_time() / T * 2 * M_PI) + 1.1);
        mat3_set_identity(transf);
        mat3_itranslate(transf, win_pos[0], win_pos[1]);
        mat3_rz(i * 90 * DD2R, transf, transf);
        mat3_itranslate(transf, r, 0);
        mat3_iscale(transf, 8, 1, 1);
        painter.lines.width = 3;
        paint_2d_line(&painter, transf, VEC(0, 0), VEC(1, 0));
    }
    return 0;
}
#endif

/*
 * Meta class declarations.
 */

static obj_klass_t pointer_klass = {
    .id = "pointer",
    .size = sizeof(pointer_t),
    .flags = OBJ_IN_JSON_TREE | OBJ_MODULE,
    .init = pointer_init,
    .render = pointer_render,
    .render_order = 199, // Just before the ui.
    .attributes = (attribute_t[]) {
        PROPERTY(visible, TYPE_BOOL, MEMBER(pointer_t, visible)),
        {}
    },
};

OBJ_REGISTER(pointer_klass)
