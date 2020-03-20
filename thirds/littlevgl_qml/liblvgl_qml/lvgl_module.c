/****************************************************************************
**
** Copyright (C) 2020 @scriptiot
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  支持js、python、qml、lua等多种脚本语言，纯Ｃ开发，零依赖，支持主流 ROM > 50KB, RAM > 2KB的MCU;
**  自带垃圾回收（GC）先进的内存管理，采用最复杂的压缩算法，无内存碎片（大部分解释器都存在内存碎片）
**  Version : 1.0
**  Email   : scriptiot@aliyun.com
**  Website : https://github.com/scriptiot
**  Licence: MIT Licence
****************************************************************************/
#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <string.h>
#include "evm.h"

//draw_rect(x, y, w, h, style)
/*
{
    'body': {
        'main_color': xxx,
        'grad_color': xxx,
        'radius': xxx,
        'opa': xxx
    },
    'line': {
        'color': xxx,
        'width': xxx,
        'opa': xxx
    },
    'text': {
        'color': xxx,
        'sel_color': xxx,
        'line_space': xxx
    },
}
 */
lv_color_t lvgl_style_get_color(evm_t * e, evm_val_t * v){
    if( !v ) return LV_COLOR_BLACK;
    if( evm_is_string(v)) {
        char * s = evm_2_string(v);
        if( !strcmp(s, "white") ) return LV_COLOR_WHITE;
        if( !strcmp(s, "silver") ) return LV_COLOR_SILVER;
        if( !strcmp(s, "gray") ) return LV_COLOR_GRAY;
        if( !strcmp(s, "black") ) return LV_COLOR_BLACK;
        if( !strcmp(s, "red") ) return LV_COLOR_RED;
        if( !strcmp(s, "maroon") ) return LV_COLOR_MAROON;
        if( !strcmp(s, "yellow") ) return LV_COLOR_YELLOW;
        if( !strcmp(s, "olive") ) return LV_COLOR_OLIVE;
        if( !strcmp(s, "lime") ) return LV_COLOR_LIME;
        if( !strcmp(s, "green") ) return LV_COLOR_GREEN;
        if( !strcmp(s, "cyan") ) return LV_COLOR_CYAN;
        if( !strcmp(s, "aqua") ) return LV_COLOR_AQUA;
        if( !strcmp(s, "teal") ) return LV_COLOR_TEAL;
        if( !strcmp(s, "blue") ) return LV_COLOR_BLUE;
        if( !strcmp(s, "green") ) return LV_COLOR_GREEN;
        if( !strcmp(s, "navy") ) return LV_COLOR_NAVY;
        if( !strcmp(s, "magenta") ) return LV_COLOR_MAGENTA;
        if( !strcmp(s, "purple") ) return LV_COLOR_PURPLE;
        if( !strcmp(s, "orange") ) return LV_COLOR_ORANGE;
    } else if( evm_is_number(v) ){
        int i = evm_2_integer(v);
        return LV_COLOR_MAKE((i >>16) & 0xFF, (i >>8) & 0xFF, i & 0xFF);
    }
    return LV_COLOR_BLACK;
}

lv_label_align_t lvgl_get_label_align(evm_t * e, evm_val_t * v){
    if( !evm_is_string(v) ) return LV_LABEL_ALIGN_AUTO;
    char * s = evm_2_string(v);
    if( !strcmp(s, "left") ) return LV_LABEL_ALIGN_LEFT;
    if( !strcmp(s, "right") ) return LV_LABEL_ALIGN_RIGHT;
    if( !strcmp(s, "center") ) return LV_LABEL_ALIGN_CENTER;
    if( !strcmp(s, "auto") ) return LV_LABEL_ALIGN_AUTO;
    return LV_LABEL_ALIGN_AUTO;
}

lv_point_t * lvgl_array_to_points(evm_t * e, evm_val_t * v){
    if( evm_is_list(v) ){
        int len = evm_list_len(v);
        if( len == 0) return NULL;
        if( (len % 2) != 0 ) return NULL;
        lv_point_t * points = evm_malloc(len / 2);
        int j = 0;
        for(int i = 0; i < len;){
            evm_val_t * x_v = evm_list_get(e, v, i++);
            evm_val_t * y_v = evm_list_get(e, v, i++);
            if( evm_is_number(x_v) && evm_is_number(y_v)){
                points[j].x = evm_2_integer(x_v);
                points[j++].y = evm_2_integer(y_v);
            }
        }
        return points;
    }
    return NULL;
}

lv_coord_t lvgl_style_get_coord(evm_val_t * v){
    if( !v ) return 0;
    if( evm_is_number(v) ) return evm_2_integer(v);
    return 0;
}
lv_style_t style;
lv_style_t * lvgl_get_style(evm_t * e, evm_val_t * v){
    lv_style_copy(&style, &lv_style_plain);
    evm_val_t * local = evm_prop_get(e, v, "body", 0);
    if( local ){
        style.body.main_color = lvgl_style_get_color(e, evm_prop_get(e, local, "main_color", 0));
        style.body.grad_color = lvgl_style_get_color(e, evm_prop_get(e, local, "grad_color", 0));
        style.body.radius = lvgl_style_get_coord(evm_prop_get(e, local, "radius", 0));
        evm_val_t * item = evm_prop_get(e, local, "border", 0);
        if( item ){
            style.body.border.width = lvgl_style_get_coord(evm_prop_get(e, item, "width", 0));
            style.body.border.color = lvgl_style_get_color(e, evm_prop_get(e, item, "color", 0));
        }
        item = evm_prop_get(e, local, "shadow", 0);
        if( item ){
            style.body.border.width = lvgl_style_get_coord(evm_prop_get(e, item, "width", 0));
            style.body.border.color = lvgl_style_get_color(e, evm_prop_get(e, item, "color", 0));
        }
    }
    local = evm_prop_get(e, v, "line", 0);
    if( local ){
        style.line.color = lvgl_style_get_color(e, evm_prop_get(e, local, "color", 0));
        style.line.width = lvgl_style_get_coord(evm_prop_get(e, local, "width", 0));
    }
    local = evm_prop_get(e, v, "text", 0);
    if( local ){
        style.text.color = lvgl_style_get_color(e, evm_prop_get(e, local, "color", 0));
        style.text.sel_color = lvgl_style_get_color(e, evm_prop_get(e, local, "sel_color", 0));
    }
    return &style;
}

lv_color_t lvgl_int_to_color(evm_t * e, evm_val_t *v){
    lv_color_t c;
    c.full = evm_2_integer(v);
    return c;
}

lv_layout_t lvgl_get_layout(evm_t * e, evm_val_t * v){
    if( !evm_is_string(v) ) return LV_LAYOUT_OFF;
    char * s = evm_2_string(v);
    if( !strcmp(s, "off") ) return LV_LAYOUT_OFF;
    if( !strcmp(s, "col_left") ) return LV_LAYOUT_COL_L;
    if( !strcmp(s, "col_right") ) return LV_LAYOUT_COL_R;
    if( !strcmp(s, "col_middle") ) return LV_LAYOUT_COL_M;
    if( !strcmp(s, "center") ) return LV_LAYOUT_CENTER;
    if( !strcmp(s, "row_top") ) return LV_LAYOUT_ROW_T;
    if( !strcmp(s, "row_middle") ) return LV_LAYOUT_ROW_M;
    if( !strcmp(s, "row_buttom") ) return LV_LAYOUT_ROW_B;
    if( !strcmp(s, "pretty") ) return LV_LAYOUT_PRETTY;
    if( !strcmp(s, "grid") ) return LV_LAYOUT_GRID;

    return LV_LAYOUT_OFF;
}

/*XXX: GENERATED CODE, DONT EDIT IT.*/
#include "lvgl/lvgl.h"
#include "evm.h"

evm_val_t wrap_scr_act(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* ret = NULL;
  ret = (lv_obj_t*)lv_scr_act();

  jret = *evm_object_create_ext_data(e, GC_OBJECT, ret);
  }
  return jret;
}

evm_val_t wrap_obj_set_pos(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 3) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  int x = (int)evm_2_integer(v + 1);
  int y = (int)evm_2_integer(v + 2);
  lv_obj_set_pos(obj, x, y);
  }
  return jret;
}

evm_val_t wrap_obj_set_x(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  int x = (int)evm_2_integer(v + 1);
  lv_obj_set_x(obj, x);
  }
  return jret;
}

evm_val_t wrap_obj_set_y(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  int y = (int)evm_2_integer(v + 1);
  lv_obj_set_y(obj, y);
  }
  return jret;
}

evm_val_t wrap_obj_set_width(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  int width = (int)evm_2_integer(v + 1);
  lv_obj_set_width(obj, width);
  }
  return jret;
}

evm_val_t wrap_obj_set_height(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  int height = (int)evm_2_integer(v + 1);
  lv_obj_set_height(obj, height);
  }
  return jret;
}

evm_val_t wrap_obj_set_auto_realign(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_auto_realign(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_ext_click_area(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 5) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  int left = (int)evm_2_integer(v + 1);
  int right = (int)evm_2_integer(v + 2);
  int top = (int)evm_2_integer(v + 3);
  int bottom = (int)evm_2_integer(v + 4);
  lv_obj_set_ext_click_area(obj, left, right, top, bottom);
  }
  return jret;
}

evm_val_t wrap_obj_set_style(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  lv_style_t* style = lvgl_get_style(e, v + 1);
  lv_obj_set_style(obj, style);
  }
  return jret;
}

evm_val_t wrap_obj_set_hidden(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_hidden(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_click(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_click(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_top(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_top(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_drag(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_drag(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_drag_throw(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_drag_throw(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_drag_parent(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_drag_parent(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_parent_event(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_parent_event(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_set_opa_scale_enable(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  bool en = (bool)evm_2_intptr(v + 1);
  lv_obj_set_opa_scale_enable(obj, en);
  }
  return jret;
}

evm_val_t wrap_obj_get_x(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  int ret = (int)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (int)lv_obj_get_x(obj);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_y(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  int ret = (int)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (int)lv_obj_get_y(obj);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_width(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  int ret = (int)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (int)lv_obj_get_width(obj);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_height(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  int ret = (int)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (int)lv_obj_get_height(obj);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_width_fit(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  int ret = (int)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (int)lv_obj_get_width_fit(obj);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_height_fit(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  int ret = (int)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (int)lv_obj_get_height_fit(obj);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_auto_realign(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_auto_realign(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_hidden(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_hidden(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_click(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_click(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_top(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_top(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_drag(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_drag(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_drag_throw(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_drag_throw(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_drag_parent(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_drag_parent(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_get_parent_event(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_get_parent_event(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t wrap_obj_is_focused(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  bool ret = (bool)0;
  lv_obj_t* obj = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  ret = (bool)lv_obj_is_focused(obj);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t canvas_draw_rect(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 5) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  int x = (int)evm_2_integer(v + 0);
  int y = (int)evm_2_integer(v + 1);
  int w = (int)evm_2_integer(v + 2);
  int h = (int)evm_2_integer(v + 3);
  lv_style_t* style = lvgl_get_style(e, v + 4);
  lv_canvas_draw_rect(canvas, x, y, w, h, style);
  }
  return jret;
}

evm_val_t canvas_create(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 4) {
  lv_obj_t* ret = NULL;
  lv_obj_t* parent = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  lv_obj_t* copy = (lv_obj_t*)evm_object_get_ext_data(v + 1);
  int w = (int)evm_2_integer(v + 2);
  int h = (int)evm_2_integer(v + 3);
  ret = (lv_obj_t*)lv_canvas_create(parent, copy);
  lv_color_t * cbuf = evm_malloc(LV_CANVAS_BUF_SIZE_TRUE_COLOR(w, h));
  lv_canvas_set_buffer(ret, cbuf, w, h, LV_IMG_CF_TRUE_COLOR);
  evm_object_set_ext_data(p, (intptr_t)(ret));
  }
  return jret;
}

evm_val_t canvas_fill_bg(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  lv_color_t color = lvgl_style_get_color(e, v + 0);
  lv_canvas_fill_bg(canvas, color);
  }
  return jret;
}

evm_val_t canvas_draw_text(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 6) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  int x = (int)evm_2_integer(v + 0);
  int y = (int)evm_2_integer(v + 1);
  int max_w = (int)evm_2_integer(v + 2);
  lv_style_t* style = lvgl_get_style(e, v + 3);
  char * txt = (char *)evm_object_get_ext_data(v + 4);
  char * align = lvgl_get_label_align(e, v + 5);
  lv_canvas_draw_text(canvas, x, y, max_w, style, txt, align);
  }
  return jret;
}

evm_val_t canvas_draw_line(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  lv_point_t * points = lvgl_array_to_points(e, v + 0);
  lv_style_t* style = lvgl_get_style(e, v + 1);
  if(points == NULL) return jret;
  int count = evm_list_len(v)/2;
  lv_canvas_draw_line(canvas, points, count, style);
  evm_free(points);
  }
  return jret;
}

evm_val_t canvas_draw_polygon(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  lv_point_t * points = lvgl_array_to_points(e, v + 0);
  lv_style_t* style = lvgl_get_style(e, v + 1);
  if(points == NULL) return jret;
  int count = evm_list_len(v)/2;
  lv_canvas_draw_polygon(canvas, points, count, style);
  evm_free(points);
  }
  return jret;
}

evm_val_t canvas_draw_arc(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 6) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  int x = (int)evm_2_integer(v + 0);
  int y = (int)evm_2_integer(v + 1);
  int r = (int)evm_2_integer(v + 2);
  int start_angle = (int)evm_2_integer(v + 3);
  int end_angle = (int)evm_2_integer(v + 4);
  lv_style_t* style = lvgl_get_style(e, v + 5);
  lv_canvas_draw_arc(canvas, x, y, r, start_angle, end_angle, style);
  }
  return jret;
}

evm_val_t canvas_set_px(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 3) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  int x = (int)evm_2_integer(v + 0);
  int y = (int)evm_2_integer(v + 1);
  lv_color_t color = lvgl_int_to_color(e, v + 2);
  lv_canvas_set_px(canvas, x, y, color);
  }
  return jret;
}

evm_val_t canvas_set_palette(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  int id = (int)evm_2_integer(v + 0);
  lv_color_t c = lvgl_int_to_color(e, v + 1);
  lv_canvas_set_palette(canvas, id, c);
  }
  return jret;
}

evm_val_t canvas_get_px(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* canvas = (lv_obj_t*)evm_object_get_ext_data(p);
  int ret = (int)0;
  int x = (int)evm_2_integer(v + 0);
  int y = (int)evm_2_integer(v + 1);
  ret = lv_canvas_get_px(canvas, x, y).full;

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t * canvas_init(evm_t * e) {

  evm_builtin_t cls[] = {
  {"draw_rect", evm_mk_native( (intptr_t)canvas_draw_rect )},
  {"fill_bg", evm_mk_native( (intptr_t)canvas_fill_bg )},
  {"draw_text", evm_mk_native( (intptr_t)canvas_draw_text )},
  {"draw_line", evm_mk_native( (intptr_t)canvas_draw_line )},
  {"draw_polygon", evm_mk_native( (intptr_t)canvas_draw_polygon )},
  {"draw_arc", evm_mk_native( (intptr_t)canvas_draw_arc )},
  {"set_px", evm_mk_native( (intptr_t)canvas_set_px )},
  {"set_palette", evm_mk_native( (intptr_t)canvas_set_palette )},
  {"get_px", evm_mk_native( (intptr_t)canvas_get_px )},
  {NULL, NULL}
  };
 return evm_class_create(e, canvas_create, cls, NULL);
}

evm_val_t btn_create(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* ret = NULL;
  lv_obj_t* parent = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  lv_obj_t* copy = (lv_obj_t*)evm_object_get_ext_data(v + 1);
  ret = (lv_obj_t*)lv_btn_create(parent, copy);
  evm_object_set_ext_data(p, (intptr_t)(ret));
  }
  return jret;
}

evm_val_t btn_set_state(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* btn = (lv_obj_t*)evm_object_get_ext_data(p);
  int state = (int)evm_2_integer(v + 0);
  lv_btn_set_state(btn, state);
  }
  return jret;
}

evm_val_t btn_set_toggle(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* btn = (lv_obj_t*)evm_object_get_ext_data(p);
  bool tgl = (bool)evm_2_intptr(v + 0);
  lv_btn_set_toggle(btn, tgl);
  }
  return jret;
}

evm_val_t btn_set_layout(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* btn = (lv_obj_t*)evm_object_get_ext_data(p);
  lv_layout_t layout = lvgl_get_layout(e, v + 0);
  lv_btn_set_layout(btn, layout);
  }
  return jret;
}

evm_val_t * btn_init(evm_t * e) {

  evm_builtin_t cls[] = {
  {"set_state", evm_mk_native( (intptr_t)btn_set_state )},
  {"set_toggle", evm_mk_native( (intptr_t)btn_set_toggle )},
  {"set_layout", evm_mk_native( (intptr_t)btn_set_layout )},
  {NULL, NULL}
  };
 return evm_class_create(e, btn_create, cls, NULL);
}

evm_val_t label_create(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* ret = NULL;
  lv_obj_t* parent = (lv_obj_t*)evm_object_get_ext_data(v + 0);
  lv_obj_t* copy = (lv_obj_t*)evm_object_get_ext_data(v + 1);
  ret = (lv_obj_t*)lv_label_create(parent, copy);
  evm_object_set_ext_data(p, (intptr_t)(ret));
  }
  return jret;
}

evm_val_t label_set_text(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  char* text = (char*)evm_2_string(v + 0);
  lv_label_set_text(label, text);
  }
  return jret;
}

evm_val_t label_set_array_text(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 2) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  char* array = (char*)evm_2_string(v + 0);
  int size = (int)evm_2_integer(v + 1);
  lv_label_set_array_text(label, array, size);
  }
  return jret;
}

evm_val_t label_set_static_text(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  char* text = (char*)evm_2_string(v + 0);
  lv_label_set_static_text(label, text);
  }
  return jret;
}

evm_val_t label_set_long_mode(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int mode = (int)evm_2_integer(v + 0);
  lv_label_set_long_mode(label, mode);
  }
  return jret;
}

evm_val_t label_set_align(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int align = (int)evm_2_integer(v + 0);
  lv_label_set_align(label, align);
  }
  return jret;
}

evm_val_t label_set_recolor(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  bool en = (bool)evm_2_intptr(v + 0);
  lv_label_set_recolor(label, en);
  }
  return jret;
}

evm_val_t label_set_body_draw(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  bool en = (bool)evm_2_intptr(v + 0);
  lv_label_set_body_draw(label, en);
  }
  return jret;
}

evm_val_t label_set_anim_speed(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int speed = (int)evm_2_integer(v + 0);
  lv_label_set_anim_speed(label, speed);
  }
  return jret;
}

evm_val_t label_set_text_sel_start(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int index = (int)evm_2_integer(v + 0);
  lv_label_set_text_sel_start(label, index);
  }
  return jret;
}

evm_val_t label_set_text_sel_end(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 1) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int index = (int)evm_2_integer(v + 0);
  lv_label_set_text_sel_end(label, index);
  }
  return jret;
}

evm_val_t label_get_text(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  char* ret = NULL;
  ret = (char*)lv_label_get_text(label);

  jret = evm_mk_foreign_string(ret);
  }
  return jret;
}

evm_val_t label_get_long_mode(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int ret = (int)0;
  ret = (int)lv_label_get_long_mode(label);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t label_get_align(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int ret = (int)0;
  ret = (int)lv_label_get_align(label);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t label_get_recolor(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  bool ret = (bool)0;
  ret = (bool)lv_label_get_recolor(label);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t label_get_body_draw(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  bool ret = (bool)0;
  ret = (bool)lv_label_get_body_draw(label);

  jret = evm_mk_boolean(ret);
  }
  return jret;
}

evm_val_t label_get_anim_speed(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int ret = (int)0;
  ret = (int)lv_label_get_anim_speed(label);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t label_get_text_sel_start(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int ret = (int)0;
  ret = (int)lv_label_get_text_sel_start(label);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t label_get_text_sel_end(evm_t * e, evm_val_t *p, int argc, evm_val_t *v)  {
  evm_val_t jret = EVM_VAL_UNDEFINED;
  if(argc >= 0) {
  lv_obj_t* label = (lv_obj_t*)evm_object_get_ext_data(p);
  int ret = (int)0;
  ret = (int)lv_label_get_text_sel_end(label);

  jret = evm_mk_number(ret);
  }
  return jret;
}

evm_val_t * label_init(evm_t * e) {

  evm_builtin_t cls[] = {
  {"set_text", evm_mk_native( (intptr_t)label_set_text )},
  {"set_array_text", evm_mk_native( (intptr_t)label_set_array_text )},
  {"set_static_text", evm_mk_native( (intptr_t)label_set_static_text )},
  {"set_long_mode", evm_mk_native( (intptr_t)label_set_long_mode )},
  {"set_align", evm_mk_native( (intptr_t)label_set_align )},
  {"set_recolor", evm_mk_native( (intptr_t)label_set_recolor )},
  {"set_body_draw", evm_mk_native( (intptr_t)label_set_body_draw )},
  {"set_anim_speed", evm_mk_native( (intptr_t)label_set_anim_speed )},
  {"set_text_sel_start", evm_mk_native( (intptr_t)label_set_text_sel_start )},
  {"set_text_sel_end", evm_mk_native( (intptr_t)label_set_text_sel_end )},
  {"get_text", evm_mk_native( (intptr_t)label_get_text )},
  {"get_long_mode", evm_mk_native( (intptr_t)label_get_long_mode )},
  {"get_align", evm_mk_native( (intptr_t)label_get_align )},
  {"get_recolor", evm_mk_native( (intptr_t)label_get_recolor )},
  {"get_body_draw", evm_mk_native( (intptr_t)label_get_body_draw )},
  {"get_anim_speed", evm_mk_native( (intptr_t)label_get_anim_speed )},
  {"get_text_sel_start", evm_mk_native( (intptr_t)label_get_text_sel_start )},
  {"get_text_sel_end", evm_mk_native( (intptr_t)label_get_text_sel_end )},
  {NULL, NULL}
  };
 return evm_class_create(e, label_create, cls, NULL);
}

evm_val_t * lvgl_init(evm_t * e) {

  evm_builtin_t cls[] = {
  {"scr_act", evm_mk_native( (intptr_t)wrap_scr_act) },
  {"obj_set_pos", evm_mk_native( (intptr_t)wrap_obj_set_pos) },
  {"obj_set_x", evm_mk_native( (intptr_t)wrap_obj_set_x) },
  {"obj_set_y", evm_mk_native( (intptr_t)wrap_obj_set_y) },
  {"obj_set_width", evm_mk_native( (intptr_t)wrap_obj_set_width) },
  {"obj_set_height", evm_mk_native( (intptr_t)wrap_obj_set_height) },
  {"obj_set_auto_realign", evm_mk_native( (intptr_t)wrap_obj_set_auto_realign) },
  {"obj_set_ext_click_area", evm_mk_native( (intptr_t)wrap_obj_set_ext_click_area) },
  {"obj_set_style", evm_mk_native( (intptr_t)wrap_obj_set_style) },
  {"obj_set_hidden", evm_mk_native( (intptr_t)wrap_obj_set_hidden) },
  {"obj_set_click", evm_mk_native( (intptr_t)wrap_obj_set_click) },
  {"obj_set_top", evm_mk_native( (intptr_t)wrap_obj_set_top) },
  {"obj_set_drag", evm_mk_native( (intptr_t)wrap_obj_set_drag) },
  {"obj_set_drag_throw", evm_mk_native( (intptr_t)wrap_obj_set_drag_throw) },
  {"obj_set_drag_parent", evm_mk_native( (intptr_t)wrap_obj_set_drag_parent) },
  {"obj_set_parent_event", evm_mk_native( (intptr_t)wrap_obj_set_parent_event) },
  {"obj_set_opa_scale_enable", evm_mk_native( (intptr_t)wrap_obj_set_opa_scale_enable) },
  {"obj_get_x", evm_mk_native( (intptr_t)wrap_obj_get_x) },
  {"obj_get_y", evm_mk_native( (intptr_t)wrap_obj_get_y) },
  {"obj_get_width", evm_mk_native( (intptr_t)wrap_obj_get_width) },
  {"obj_get_height", evm_mk_native( (intptr_t)wrap_obj_get_height) },
  {"obj_get_width_fit", evm_mk_native( (intptr_t)wrap_obj_get_width_fit) },
  {"obj_get_height_fit", evm_mk_native( (intptr_t)wrap_obj_get_height_fit) },
  {"obj_get_auto_realign", evm_mk_native( (intptr_t)wrap_obj_get_auto_realign) },
  {"obj_get_hidden", evm_mk_native( (intptr_t)wrap_obj_get_hidden) },
  {"obj_get_click", evm_mk_native( (intptr_t)wrap_obj_get_click) },
  {"obj_get_top", evm_mk_native( (intptr_t)wrap_obj_get_top) },
  {"obj_get_drag", evm_mk_native( (intptr_t)wrap_obj_get_drag) },
  {"obj_get_drag_throw", evm_mk_native( (intptr_t)wrap_obj_get_drag_throw) },
  {"obj_get_drag_parent", evm_mk_native( (intptr_t)wrap_obj_get_drag_parent) },
  {"obj_get_parent_event", evm_mk_native( (intptr_t)wrap_obj_get_parent_event) },
  {"obj_is_focused", evm_mk_native( (intptr_t)wrap_obj_is_focused) },
  {"canvas", *canvas_init(e)},
  {"btn", *btn_init(e)},
  {"label", *label_init(e)},
  {NULL, NULL}
 };
 evm_module_create(e, "littlevgl", cls);
  return e->err;
}









