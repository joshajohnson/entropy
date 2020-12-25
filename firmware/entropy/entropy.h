/* Copyright 2020 joshajohnson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// 2U keys on numpad, plus 1.5U on RHS of split space bar
#define LAYOUT_2U_SS( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K116,    K118,    K119,  \
         K21, K22, K23, K24,   K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217,   K218,  K219,  \
    K30, K31, K32, K33, K34,    K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316,      K317,    K319,  \
         K41, K42, K43, K45,     K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,       K417,  K418, K419,  \
    K50, K51,      K53, K54,   K55,  K57,      K59,   K510,    K512,           K514, K516,      K517, K518, K519   \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019 },  \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K116,  ___, K118, K119 },  \
    { ___, K21, K22, K23, K24, ___, K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219 },  \
    { K30, K31, K32, K33, K34, ___, K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316, K317,  ___, K319 },  \
    { ___, K41, K42, K43, ___, K45, K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,  ___, K417, K418, K419 },  \
    { K50, K51, ___, K53, K54, K55, ___, K57, ___, K59, K510,  ___, K512,  ___, K514,  ___, K516, K517, K518, K519 }   \
}

// 2U keys on numpad, plus 1.5U on RHS of single space bar
#define LAYOUT_2U( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K116,    K118,    K119,  \
         K21, K22, K23, K24,   K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217,   K218,  K219,  \
    K30, K31, K32, K33, K34,    K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316,      K317,    K319,  \
         K41, K42, K43, K45,     K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,       K417,  K418, K419,  \
    K50, K51,      K53, K54,   K55,  K57,             K510,                  K514, K516,        K517, K518, K519   \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019 },  \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K116,  ___, K118, K119 },  \
    { ___, K21, K22, K23, K24, ___, K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219 },  \
    { K30, K31, K32, K33, K34, ___, K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316, K317,  ___, K319 },  \
    { ___, K41, K42, K43, ___, K45, K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,  ___, K417, K418, K419 },  \
    { K50, K51, ___, K53, K54, K55, ___, K57, ___, ___, K510,  ___,  ___,  ___, K514,  ___, K516, K517, K518, K519 }   \
}

// 1U keys wherever possible, single space bar, single backspace
#define LAYOUT_1U( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K116,    K118,    K119,  \
    K20, K21, K22, K23, K24,   K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217,   K218,  K219,  \
    K30, K31, K32, K33, K34,    K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316,      K317,    K319,  \
    K40, K41, K42, K43, K45,     K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,       K417,  K418, K419,  \
    K50, K51, K52, K53, K54,   K55,  K57,             K510,                   K514, K515, K516, K517, K518, K519   \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019 },  \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K116, ___,  K118, K119 },  \
    { K20, K21, K22, K23, K24, ___, K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219 },  \
    { K30, K31, K32, K33, K34, ___, K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316, K317, ___,  K319 },  \
    { K40, K41, K42, K43, ___, K45, K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,  ___, K417, K418, K419 },  \
    { K50, K51, K52, K53, K54, K55, ___, K57, ___, ___, K510,  ___,  ___,  ___, K514, K515, K516, K517, K518, K519 }   \
}

// 1U keys wherever possible, split space, split backspace
#define LAYOUT_1U_SS( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K170, K171, K178, K119,  \
    K20, K21, K22, K23, K24,   K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217,   K218,  K219,  \
    K30, K31, K32, K33, K34,    K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316,      K317,    K319,  \
    K40, K41, K42, K43, K45,     K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,       K417,  K418, K419,  \
    K50, K51, K52, K53, K54,   K55,  K57,      K59,   K510,    K512,          K514, K515, K516, K517, K518, K519   \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014, K015, K016, K017, K018, K019 },  \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114, K115, K170, K171, K178, K119 },  \
    { K20, K21, K22, K23, K24, ___, K26, K27, K28, K29, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219 },  \
    { K30, K31, K32, K33, K34, ___, K36, K37, K38, K39, K310, K311, K312, K313, K314, K315, K316, K317, ___,  K319 },  \
    { K40, K41, K42, K43, ___, K45, K46, K47, K48, K49, K410, K411, K412, K413, K414, K415,  ___, K417, K418, K419 },  \
    { K50, K51, K52, K53, K54, K55, ___, K57, ___, K59, K510,  ___, K512,  ___, K514, K515, K516, K517, K518, K519 }   \
}
