/* BEEBS queue benchmark

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>

   This file is part of the Bristol/Embecosm Embedded Energy Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include "support.h"
#include <stdio.h>
#include <stdlib.h>
#include "sglib.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 3)

// Alter list size to selected data size
#ifdef SMALL_D
  #define NUMELEMS 20
#elif defined(LARGE_D)
  #define NUMELEMS 500
#else
  //medium
  #define NUMELEMS 100
#endif

#ifdef SMALL_D
  int array[NUMELEMS] = {1, 18, 3, 7, 15, 8, 2, 19, 6, 9, 14, 17, 16, 12, 5, 10, 13, 0, 11, 4};
#else/*#elif defined(LARGE_D)
  int array[NUMELEMS] = {94, 368, 147, 298, 442, 115, 236, 128, 144, 169, 86, 221, 46, 24, 129, 226, 326, 67, 188, 71, 398, 33, 361, 489, 229, 422, 53, 76, 399, 377, 105, 121, 130, 244, 145, 297, 308, 439, 304, 178, 187, 99, 408, 16, 30, 282, 427, 148, 375, 395, 447, 210, 455, 91, 237, 143, 113, 396, 209, 493, 98, 197, 300, 400, 93, 323, 166, 448, 443, 189, 181, 222, 41, 81, 374, 324, 424, 172, 278, 283, 146, 175, 40, 284, 158, 389, 499, 257, 100, 84, 247, 26, 243, 412, 20, 280, 387, 51, 142, 124, 319, 491, 6, 109, 311, 160, 271, 111, 131, 9, 339, 211, 215, 357, 232, 55, 388, 328, 440, 240, 295, 373, 250, 369, 471, 133, 108, 163, 490, 23, 277, 122, 78, 185, 37, 36, 202, 343, 150, 219, 59, 322, 196, 449, 470, 186, 310, 134, 235, 164, 104, 425, 430, 141, 435, 48, 255, 264, 34, 167, 2, 43, 212, 258, 154, 431, 49, 8, 126, 497, 74, 140, 224, 259, 364, 292, 266, 329, 444, 47, 14, 358, 411, 127, 492, 260, 461, 451, 351, 494, 10, 415, 253, 333, 321, 469, 239, 162, 438, 429, 345, 362, 1, 80, 249, 265, 392, 63, 403, 92, 496, 95, 77, 393, 173, 290, 437, 498, 287, 246, 179, 135, 107, 19, 454, 315, 214, 356, 177, 458, 417, 330, 176, 25, 194, 45, 344, 359, 89, 299, 193, 460, 66, 183, 482, 379, 420, 223, 457, 410, 208, 153, 32, 252, 73, 118, 233, 123, 231, 405, 291, 204, 353, 174, 434, 313, 275, 42, 87, 456, 401, 139, 114, 376, 35, 317, 44, 106, 352, 62, 484, 390, 39, 227, 213, 168, 293, 27, 436, 190, 125, 241, 367, 225, 195, 414, 475, 464, 17, 478, 31, 342, 338, 316, 102, 50, 402, 331, 347, 423, 207, 341, 320, 228, 407, 203, 381, 38, 170, 149, 397, 272, 452, 136, 340, 156, 4, 487, 294, 288, 262, 117, 325, 335, 101, 332, 56, 137, 52, 60, 428, 29, 479, 486, 218, 28, 58, 171, 65, 64, 22, 285, 82, 476, 378, 138, 477, 465, 360, 180, 281, 119, 79, 268, 433, 472, 409, 70, 220, 191, 370, 336, 182, 157, 269, 348, 309, 120, 467, 97, 307, 155, 306, 274, 450, 192, 350, 205, 363, 445, 355, 165, 198, 152, 263, 303, 256, 481, 206, 421, 488, 466, 273, 365, 90, 419, 384, 279, 21, 0, 495, 314, 216, 453, 312, 200, 3, 382, 199, 432, 217, 441, 305, 385, 13, 230, 116, 327, 372, 132, 110, 474, 289, 446, 462, 426, 234, 5, 261, 483, 346, 54, 151, 245, 480, 468, 12, 112, 386, 184, 485, 366, 201, 276, 267, 354, 416, 251, 337, 394, 459, 7, 383, 413, 254, 96, 371, 301, 270, 159, 161, 57, 69, 391, 406, 473, 302, 75, 85, 238, 18, 418, 15, 72, 88, 61, 103, 404, 286, 11, 349, 334, 68, 242, 296, 248, 83, 463, 318, 380};
#else*/
  int array[NUMELEMS] = {14, 66, 12, 41, 86, 69, 19, 77, 68, 38, 26, 42, 37, 23, 17, 29, 55, 13,
  90, 92, 76, 99, 10, 54, 57, 83, 40, 44, 75, 33, 24, 28, 80, 18, 78, 32, 93, 89, 52, 11,
  21, 96, 50, 15, 48, 63, 87, 20, 8, 85, 43, 16, 94, 88, 53, 84, 74, 91, 67, 36, 95, 61,
  64, 5, 30, 82, 72, 46, 59, 9, 7, 3, 39, 31, 4, 73, 70, 60, 58, 81, 56, 51, 45, 1, 6, 49,
  27, 47, 34, 35, 62, 97, 2, 79, 98, 25, 22, 65, 71, 0};
#endif

#define MAX_PARAMS (NUMELEMS+1)

typedef struct iq {int a[MAX_PARAMS]; int i,j;} iq;
SGLIB_DEFINE_QUEUE_FUNCTIONS(iq, int, a, i, j, MAX_PARAMS);

int benchmark()
{
  int i, ai,aj, n;
  int a[NUMELEMS+1];
  int cnt = 0;

  // echo parameters using a queue
  SGLIB_QUEUE_INIT(int, a, ai, aj);
  for (i=0; i<100; i++) {
    n = array[i];
    SGLIB_QUEUE_ADD(int, a, n, ai, aj, NUMELEMS+1);
  }
  while(! SGLIB_QUEUE_IS_EMPTY(int, a, ai, aj)) {
  cnt += SGLIB_QUEUE_FIRST_ELEMENT(int, a, ai, aj);
  SGLIB_QUEUE_DELETE(int, a, ai, aj, NUMELEMS+1);
  }

  // print parameters in descending order
  SGLIB_HEAP_INIT(int, a, ai);
  for (i=0; i<100; i++) {
    n = array[i];
    SGLIB_HEAP_ADD(int, a, n, ai, NUMELEMS+1, SGLIB_NUMERIC_COMPARATOR);
  }
  while(! SGLIB_HEAP_IS_EMPTY(int, a, ai)) {
    cnt += SGLIB_HEAP_FIRST_ELEMENT(int, a, ai);
    SGLIB_HEAP_DELETE(int, a, ai, NUMELEMS+1, SGLIB_NUMERIC_COMPARATOR);
  }


  return cnt;
}

int
main (void)
{
  int i;

  initialise_board ();
  start_trigger ();

  for (i = 0; i < SCALE_FACTOR; i++)
    benchmark ();

  stop_trigger ();
  return 0;
}

