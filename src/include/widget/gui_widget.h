/**	
 * \file            gui_widget.h
 * \brief           Widget specific shared functions
 */
 
/*
 * Copyright (c) 2017 Tilen Majerle
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of EasyGUI library.
 *
 * Author:          Tilen Majerle <tilen@majerle.eu>
 */
#ifndef __GUI_WIDGET_H
#define __GUI_WIDGET_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup        GUI_WIDGETS Widgets
 * \brief           Group for visible widgets on screen
 * \{
 */
    
/**
 * \defgroup        GUI_WIDGETS_CORE Core widget functions
 * \brief           Core functions for all widgets
 * \{
 */
#include "gui/gui.h"
#include "gui/gui_draw.h"

/**
 * \defgroup        GUI_WIDGET_ID_Values Predefined ID values
 * \brief           Macros for fast ID setup
 * \{
 */  
    
#define GUI_ID_WINDOW_BASE          ((gui_id_t)0x0000)                          /*!< Window base ID */
#define GUI_ID_KEYBOARD_BASE        ((gui_id_t)(GUI_ID_WINDOW_BASE + 0x1000))   /*!< Keyboard based ID */

#define GUI_ID_USER                 ((gui_id_t)(0x10000))                       /*!< Start number of user based ID values for widgets */

#define GUI_WIDGET_ZINDEX_MAX       (int32_t)(0x7FFFFFFF)                       /*!< Maximal allowed z-index value */
#define GUI_WIDGET_ZINDEX_MIN       (int32_t)(0x80000000)                       /*!< Maximal allowed z-index value */
    
/**
 * \}
 */
 
/**
 * \defgroup        GUI_WIDGET_CREATE_FLAGS flags for widget create
 * \brief           A list of flags supported for widget creation
 *
 * List of flags used on \ref guii_widget_create function when creating new widget
 * 
 * \{
 */
#define GUI_FLAG_WIDGET_CREATE_PARENT_DESKTOP       0x01    /*!< Indicates parent object of widget should be desktop window */
#define GUI_FLAG_WIDGET_CREATE_NO_PARENT            0x02    /*!< No parent widget */
#define GUI_FLAG_WIDGET_CREATE_IGNORE_INVALIDATE    0x04    /*!< Ignore invalidate on widget creation */

/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_PRIVATE Private functions
 * \brief           Private widget functions and enumerations.
 *
 * \note            Since they are not thread safe, they can only be used when inside GUI library.
 *                  It means they can be used in custom widget implementations where thread safety is guaranteed
 *
 * \{
 */
 
/**
 * \brief           Widget footprint value
 * \hideinitializer
 */
#define GUI_WIDGET_FOOTPRINT                        0x00ACCE55
 
/**
 * \brief           Checks if inserted pointer is valid widget
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Input pointer to test for widget
 * \return          `1` on success, `0` otherwise Pointer is widget
 * \return          `1` on success, `0` otherwise Pointer is not widget
 * \hideinitializer
 */
#define guii_widget_iswidget(h)                     ((h) != NULL && (h)->footprint == GUI_WIDGET_FOOTPRINT)

/**
 * \brief           Get widget relative X position according to parent widget
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Relative X according to parent widget
 * \hideinitializer
 */
#define guii_widget_getrelativex(h)                 GUI_DIM((gui_widget_isexpanded(h, 0) ? 0 : \
                                                        (guii_widget_getflag(h, GUI_FLAG_XPOS_PERCENT) ? (gui_dim_t)((float)GUI_ROUND((h)->x * guii_widget_getparentinnerwidth(h)) / 100.0f) : (h)->x) \
                                                    ))

/**
 * \brief           Get widget relative Y position according to parent widget
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Relative Y according to parent widget
 * \hideinitializer
 */
#define guii_widget_getrelativey(h)                 GUI_DIM(gui_widget_isexpanded(h, 0) ? 0 : \
                                                        (guii_widget_getflag(h, GUI_FLAG_YPOS_PERCENT) ? (gui_dim_t)((float)GUI_ROUND((h)->y * guii_widget_getparentinnerheight(h)) / 100.0f) : (h)->y) \
                                                    )

/**
 * \brief           Get widget flag(s)
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \param[in]       flag: Flag(s) to check
 * \return          0 on failure, non-zero otherwise
 * \hideinitializer
 */
#define guii_widget_getflag(h, flag)                (__GH(h)->flags & (flag))

/**
 * \brief           Get widget core flag(s)
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \param[in]       flag: Flag(s) to check
 * \return          0 on failure, non-zero otherwise (flags)
 * \hideinitializer
 */
#define guii_widget_getcoreflag(h, flag)            (__GH(h)->widget->flags & (flag))

/**
 * \brief           Set widget flag(s)
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \param[in]       flag: Flag(s) to set
 * \hideinitializer
 */
#define guii_widget_setflag(h, flag)                ((h)->flags |= (flag))

/**
 * \brief           Clear widget flag(s)
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \param[in]       flag: Flag(s) to clear
 * \hideinitializer
 */
#define guii_widget_clrflag(h, flag)                ((h)->flags &= ~(flag))

/**
 * \brief           Checks if widget has enabled 3D mode
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#define guii_widget_is3d(h)                         (!!guii_widget_getflag(h, GUI_FLAG_3D))

/**
 * \brief           Get pointer to parent widget
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Pointer to parent widget
 * \hideinitializer
 */
#define guii_widget_getparent(h)                    ((h) != NULL ? (h)->parent : NULL)

/**
 * \brief           Check if widget has parent widget
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#define guii_widget_hasparent(h)                    ((h) != NULL && (h)->parent != NULL)

/**
 * \brief           Process widget callback with command, parameters and result pointers
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \param[in]       cmd: Callback command. This parameter can be a value of \ref gui_wc_t enumeration
 * \param[in]       param: Pointer to parameters if any for this command
 * \param[out]      result: Pointer to result pointer where calback can store result
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#define guii_widget_callback(h, cmd, param, result) ((h)->callback != NULL ? (h)->callback(h, cmd, param, result) : (h)->widget->callback(h, cmd, param, result))

/**
 * \brief           Get widget colors from list of colors
 *                  It takes colors from allocated memory if exists or from default widget setup for default
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \param[in]       index: Color index from color array for specific widget
 * \retval          Color index
 * \hideinitializer
 */
#define guii_widget_getcolor(h, index)              ((h)->colors != NULL ? (h)->colors[(uint8_t)(index)] : ((h)->widget->colors != NULL ? (h)->widget->colors[(uint8_t)(index)] : GUI_COLOR_BLACK))

/**
 * \brief           Get inner width (total width - padding left - padding right)
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          height in units of pixels
 * \hideinitializer
 */
#define guii_widget_getinnerwidth(h)                GUI_DIM((gui_widget_getwidth(h, 0) - (gui_widget_getpaddingleft(h, 0) + gui_widget_getpaddingright(h, 0))))

/**
 * \brief           Get inner height (total height - padding top - padding bottom)
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Inner height in units of pixels
 * \hideinitializer
 */
#define guii_widget_getinnerheight(h)               GUI_DIM((gui_widget_getheight(h, 0) - (gui_widget_getpaddingtop(h, 0) + gui_widget_getpaddingbottom(h, 0))))

/**
 * \brief           Returns width of parent element. If parent does not exists, it returns LCD width
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Parent width in units of pixels
 * \hideinitializer
 */
#define guii_widget_getparentwidth(h)               GUI_DIM((guii_widget_hasparent(h) ? gui_widget_getwidth(guii_widget_getparent(h), 0) : GUI.lcd.width))

/**
 * \brief           Returns height of parent element. If parent does not exists, it returns LCD height
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Parent height in units of pixels
 * \hideinitializer
 */
#define guii_widget_getparentheight(h)              GUI_DIM((guii_widget_hasparent(h) ? guii_widget_getheight(guii_widget_getparent(h), 0) : GUI.lcd.height))

/**
 * \brief           Returns inner width of parent element. If parent does not exists, it returns LCD width
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 *
 * \note            It returns inner width = total width - padding left - padding right
 * \param[in]       h: Widget handle
 * \retval          Parent width in units of pixels
 * \hideinitializer
 */
#define guii_widget_getparentinnerwidth(h)          GUI_DIM((guii_widget_hasparent(h) ? guii_widget_getinnerwidth(guii_widget_getparent(h)) : GUI.lcd.width))

/**
 * \brief           Returns inner height of parent element. If parent does not exists, it returns LCD height
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 *
 * \note            It returns inner height = total height - padding top - padding bottom
 * \param[in]       h: Widget handle
 * \retval          Parent height in units of pixels
 * \hideinitializer
 */
#define guii_widget_getparentinnerheight(h)         GUI_DIM((guii_widget_hasparent(h) ? guii_widget_getinnerheight(guii_widget_getparent(h)) : GUI.lcd.height))

/**
 * \brief           Check if widget is visible in any way, either with transparency or hidden flag
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#if GUI_CFG_USE_ALPHA
#define guii_widget_isvisible(h)                    (!guii_widget_getflag(h, GUI_FLAG_HIDDEN) && (h)->alpha)
#else /* GUI_CFG_USE_ALPHA */
#define guii_widget_isvisible(h)                    (!guii_widget_getflag(h, GUI_FLAG_HIDDEN))
#endif /* !GUI_CFG_USE_ALPHA */

/**
 * \brief           Check if widget is hidden
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#define guii_widget_ishidden(h)                     (!guii_widget_isvisible(h))

/**
 * \brief           Check if widget allows children widgets
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#define guii_widget_allowchildren(h)                (!!guii_widget_getcoreflag(h, GUI_FLAG_WIDGET_ALLOW_CHILDREN))

/**
 * \brief           Check if widget is base for dialog
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 * \hideinitializer
 */
#define guii_widget_isdialogbase(h)                 (!!(guii_widget_getcoreflag(h, GUI_FLAG_WIDGET_DIALOG_BASE) || guii_widget_getflag(h, GUI_FLAG_WIDGET_DIALOG_BASE)))

/**
 * \brief           Checks if widget handle is currently in focus
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Status whether widget is in focus or not
 * \hideinitializer
 */
#define guii_widget_isfocused(h)                    (!!guii_widget_getflag(h, GUI_FLAG_FOCUS))

/**
 * \brief           Checks if widget handle is currently active
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          Status whether widget is active or not
 * \hideinitializer
 */
#define guii_widget_isactive(h)                     (!!guii_widget_getflag(h, GUI_FLAG_ACTIVE))

/**
 * \brief           Check is widget has alpha less than maximum
 * \note            Check if widget is visible and alpha is not set to 1 (full view)
 *
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \return          `1` on success, `0` otherwise
 */
#define guii_widget_hasalpha(h)                     (guii_widget_isvisible(h) && gui_widget_getalpha(h, 0) < 0xFF)

/**
 * \brief           Get z-index value from widget
 * \note            The function is private and can be called only when GUI protection against multiple access is activated
 * \param[in]       h: Widget handle
 * \retval          z-index value
 * \hideinitializer
 */
#define guii_widget_getzindex(h)                   GUI_I32((h)->zindex)

gui_dim_t       guii_widget_getabsolutex(gui_handle_p h);
gui_dim_t       guii_widget_getabsolutey(gui_handle_p h);
gui_dim_t       guii_widget_getparentabsolutex(gui_handle_p h);
gui_dim_t       guii_widget_getparentabsolutey(gui_handle_p h);
uint8_t         guii_widget_invalidate(gui_handle_p h);
uint8_t         guii_widget_invalidatewithparent(gui_handle_p h);
uint8_t         guii_widget_setinvalidatewithparent(gui_handle_p h, uint8_t value);

uint8_t         guii_widget_set3dstyle(gui_handle_p h, uint8_t enable);

void*           guii_widget_create(const gui_widget_t* widget, gui_id_t id, float x, float y, float width, float height, gui_handle_p parent, gui_widget_callback_t cb, uint16_t flags, const uint8_t protect);

uint8_t         guii_widget_isfontandtextset(gui_handle_p h);

uint8_t         guii_widget_processtextkey(gui_handle_p h, guii_keyboard_data_t* key);
uint8_t         guii_widget_setcolor(gui_handle_p h, uint8_t index, gui_color_t color, const uint8_t protect);

uint8_t         guii_widget_setparam(gui_handle_p h, uint16_t cfg, const void* data, uint8_t invalidate, uint8_t invalidateparent, const uint8_t protect);
uint8_t         guii_widget_getparam(gui_handle_p h, uint16_t cfg, void* data);

/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_TEXT Text management
 * \brief           Text and font management functions
 * \{
 */

uint32_t        gui_widget_alloctextmemory(gui_handle_p h, uint32_t size, const uint8_t protect);
uint8_t         gui_widget_freetextmemory(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_settext(gui_handle_p h, const gui_char* text, const uint8_t protect);
const gui_char *    gui_widget_gettext(gui_handle_p h, const uint8_t protect);
const gui_char *    gui_widget_gettextcopy(gui_handle_p h, gui_char* dst, uint32_t len, const uint8_t protect);
uint8_t         gui_widget_setfont(gui_handle_p h, const gui_font_t* font, const uint8_t protect);
const gui_font_t *  gui_widget_getfont(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_setfontdefault(const gui_font_t* font, const uint8_t protect);

/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_SIZE Size management
 * \brief           Size management functions
 * \{
 */

uint8_t         gui_widget_setsize(gui_handle_p h, gui_dim_t width, gui_dim_t height, const uint8_t protect);
uint8_t         gui_widget_setsizepercent(gui_handle_p h, float width, float height, const uint8_t protect);
uint8_t         gui_widget_setwidth(gui_handle_p h, gui_dim_t width, const uint8_t protect);
uint8_t         gui_widget_setheight(gui_handle_p h, gui_dim_t height, const uint8_t protect);
uint8_t         gui_widget_setwidthpercent(gui_handle_p h, float width, const uint8_t protect);
uint8_t         gui_widget_setheightpercent(gui_handle_p h, float height, const uint8_t protect);
gui_dim_t       gui_widget_getwidth(gui_handle_p h, const uint8_t protect);
gui_dim_t       gui_widget_getheight(gui_handle_p h, const uint8_t protect);

uint8_t         gui_widget_setexpanded(gui_handle_p h, uint8_t state, const uint8_t protect);
uint8_t         gui_widget_toggleexpanded(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_isexpanded(gui_handle_p h, const uint8_t protect);

/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_POSITION Position management
 * \brief           Position management functions
 * \{
 */
 
uint8_t         gui_widget_setposition(gui_handle_p h, gui_dim_t x, gui_dim_t y, const uint8_t protect);
uint8_t         gui_widget_setpositionpercent(gui_handle_p h, float x, float y, const uint8_t protect);
uint8_t         gui_widget_setxposition(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setxpositionpercent(gui_handle_p h, float x, const uint8_t protect);
uint8_t         gui_widget_setyposition(gui_handle_p h, gui_dim_t y, const uint8_t protect);
uint8_t         gui_widget_setypositionpercent(gui_handle_p h, float y, const uint8_t protect);
uint8_t         gui_widget_setscrollx(gui_handle_p h, gui_dim_t scroll, const uint8_t protect);
uint8_t         gui_widget_setscrolly(gui_handle_p h, gui_dim_t scroll, const uint8_t protect);
uint8_t         gui_widget_incscrollx(gui_handle_p h, gui_dim_t scroll, const uint8_t protect);
uint8_t         gui_widget_incscrolly(gui_handle_p h, gui_dim_t scroll, const uint8_t protect);
gui_dim_t       gui_widget_getscrollx(gui_handle_p h, const uint8_t protect);
gui_dim_t       gui_widget_getscrolly(gui_handle_p h, const uint8_t protect);

/**
 * \}
 */
 
/**
 * \defgroup        GUI_WIDGET_VISIBILITY Visibility management
 * \brief           Visibility management functions
 * \{
 */

uint8_t         gui_widget_show(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_hide(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_hidechildren(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_putonfront(gui_handle_p h, uint8_t focus, const uint8_t protect);
uint8_t         gui_widget_getalpha(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_setalpha(gui_handle_p h, uint8_t alpha, const uint8_t protect);
 
/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_MISC Miscellaneous
 * \brief           Miscellaneous functions
 * \{
 */

uint8_t         gui_widget_invalidate(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_setignoreinvalidate(gui_handle_p h, uint8_t en, uint8_t invalidate, const uint8_t protect);
uint8_t         gui_widget_setuserdata(gui_handle_p h, void* data, const uint8_t protect);
void *          gui_widget_getuserdata(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_ischildof(gui_handle_p h, gui_handle_p parent, const uint8_t protect);
uint8_t         gui_widget_incselection(gui_handle_p h, int16_t dir, const uint8_t protect);
uint8_t         gui_widget_setfocus(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_setzindex(gui_handle_p h, int32_t zindex, const uint8_t protect);
int32_t         gui_widget_getzindex(gui_handle_p h, const uint8_t protect);
uint8_t         gui_widget_set3dstyle(gui_handle_p h, uint8_t enable, const uint8_t protect);
gui_handle_p    gui_widget_getparent(gui_handle_p h, const uint8_t protect);
gui_id_t        gui_widget_getid(gui_handle_p h, const uint8_t protect);
gui_handle_p    gui_widget_getbyid(gui_id_t id, const uint8_t protect);
gui_handle_p    gui_widget_getbyid_ex(gui_id_t id, gui_handle_p parent, uint8_t deep, const uint8_t protect);
uint8_t         gui_widget_remove(gui_handle_p* h, const uint8_t protect);

/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_PADDING Padding
 * \brief           Padding related functions
 * \{
 */
 
uint8_t         gui_widget_setpaddingtop(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setpaddingright(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setpaddingbottom(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setpaddingleft(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setpaddingtopbottom(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setpaddingleftright(gui_handle_p h, gui_dim_t x, const uint8_t protect);
uint8_t         gui_widget_setpadding(gui_handle_p h, gui_dim_t x, const uint8_t protect);

gui_dim_t       gui_widget_getpaddingtop(gui_handle_p h, const uint8_t protect);
gui_dim_t       gui_widget_getpaddingright(gui_handle_p h, const uint8_t protect);
gui_dim_t       gui_widget_getpaddingbottom(gui_handle_p h, const uint8_t protect);
gui_dim_t       gui_widget_getpaddingleft(gui_handle_p h, const uint8_t protect);

/**
 * \}
 */

/**
 * \defgroup        GUI_WIDGET_CALLBACK Callback processing
 * \brief           Callback based functions
 * \{
 */

uint8_t         gui_widget_processdefaultcallback(gui_handle_p h, gui_wc_t ctrl, gui_widget_param_t* param, gui_widget_result_t* result);
uint8_t         gui_widget_setcallback(gui_handle_p h, gui_widget_callback_t callback, const uint8_t protect);
uint8_t         gui_widget_callback(gui_handle_p h, gui_wc_t ctrl, gui_widget_param_t* param, gui_widget_result_t* result);

/**
 * \}
 */
 
#if defined(GUI_INTERNAL) && !__DOXYGEN__
//Strictly private functions by GUI
//Widget initialization purpose
void guii_widget_init(void);

//Clipping regions
uint8_t guii_widget_isinsideclippingregion(gui_handle_p h, uint8_t check_sib_cover);

//Move widget down and all its parents with it
void guii_widget_movedowntree(gui_handle_p h);

void guii_widget_focus_clear(void);
void guii_widget_focus_set(gui_handle_p h);
void guii_widget_active_clear(void);
void guii_widget_active_set(gui_handle_p h);

//Execute actual widget remove process
uint8_t guii_widget_executeremove(void);
#endif /* !__DOXYGEN__ */

/**
 * \}
 */
 
/**
 * \}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* __GUI_WIDGET_H */
