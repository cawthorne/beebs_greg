/* BEEBS arraysort benchmark

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
#include "sglib.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

// Alter iteration size to selected data size
#ifdef SMALL_D
  #define SIZE 35
#elif defined(LARGE_D)
  #define SIZE 800
#else
  //medium
  #define SIZE 100
#endif

#ifdef SMALL_D
  int array[SIZE] = {390, 55, 401, 290, 414, 549, 502, 254, 629, 560, 583, 528, 233, 178, 445, 458, 487, 126, 256, 798, 237, 530, 218, 706, 6, 618, 588, 205, 758, 90, 387, 336, 665, 320, 1, 185, 605, 692, 548, 7, 454, 708, 591, 362, 432, 658, 759, 655, 788, 314, 518, 622, 503, 97, 690, 483, 134, 722, 143, 724, 217, 308, 601, 173, 786, 539, 717, 333, 711, 389, 417, 453, 38, 476, 556, 94, 728, 742, 633, 418, 573, 545, 46, 441, 231, 64, 59, 234, 572, 9, 608, 193, 18, 45, 216, 151, 246, 66, 731, 656, 10, 627, 577, 2, 211, 202, 140, 125, 364, 468, 347, 236, 21, 632, 410, 226, 378, 393, 339, 210, 505, 416, 720, 355, 312, 686, 172, 136, 455, 351, 533, 685, 230, 150, 738, 239, 345, 411, 550, 642, 424, 162, 307, 794, 73, 437, 283, 194, 301, 377, 426, 337, 649, 795, 65, 127, 771, 155, 493, 647, 353, 776, 714, 24, 120, 28, 141, 317, 599, 682, 177, 291, 147, 757, 4, 489, 212, 198, 51, 268, 5, 415, 63, 660, 403, 199, 796, 422, 584, 137, 499, 709, 224, 131, 695, 531, 558, 278, 504, 324, 356, 228, 15, 672, 755, 326, 321, 119, 309, 130, 300, 265, 142, 766, 53, 349, 800, 592, 735, 249, 374, 689, 78, 779, 43, 27, 99, 753, 240, 768, 219, 749, 82, 289, 438, 551, 589, 429, 498, 764, 334, 305, 490, 507, 652, 582, 242, 168, 470, 148, 272, 359, 247, 679, 306, 215, 543, 395, 311, 154, 434, 710, 92, 705, 169, 367, 612, 760, 89, 594, 48, 95, 252, 670, 167, 75, 399, 251, 69, 361, 536, 392, 676, 547, 481, 34, 282, 576, 366, 76, 636, 293, 304, 699, 456, 213, 799, 179, 569, 486, 602, 330, 107, 201, 104, 567, 497, 180, 110, 730, 207, 145, 220, 620, 264, 474, 783, 527, 553, 294, 637, 780, 271, 657, 452, 223, 719, 371, 382, 350, 118, 54, 68, 373, 158, 425, 383, 694, 232, 440, 135, 41, 322, 159, 559, 700, 171, 565, 615, 450, 368, 781, 260, 31, 448, 323, 164, 111, 275, 461, 544, 684, 581, 109, 328, 229, 575, 623, 762, 664, 44, 138, 580, 163, 191, 733, 358, 726, 259, 25, 363, 587, 667, 763, 778, 313, 385, 478, 640, 494, 736, 96, 288, 523, 11, 797, 712, 761, 513, 115, 238, 568, 606, 739, 77, 609, 459, 610, 329, 102, 423, 634, 466, 105, 225, 287, 537, 773, 661, 106, 203, 335, 32, 98, 566, 613, 235, 469, 250, 492, 122, 639, 166, 491, 716, 175, 574, 245, 791, 561, 279, 112, 33, 208, 743, 604, 555, 270, 698, 532, 449, 666, 352, 645, 770, 17, 365, 585, 57, 70, 394, 36, 475, 607, 767, 101, 732, 480, 777, 13, 325, 60, 406, 160, 651, 80, 611, 600, 29, 534, 595, 280, 319, 341, 510, 522, 557, 195, 49, 538, 263, 772, 357, 619, 391, 267, 713, 227, 338, 299, 519, 435, 161, 488, 460, 677, 30, 603, 315, 123, 79, 650, 209, 257, 697, 734, 529, 638, 84, 707, 421, 477, 409, 683, 436, 784, 61, 400, 261, 346, 520, 396, 281, 598, 221, 586, 715, 675, 128, 87, 58, 464, 442, 579, 687, 62, 467, 187, 745, 419, 196, 496, 727, 641, 241, 769, 792, 139, 47, 524, 500, 525, 472, 512, 243, 108, 673, 86, 702, 206, 782, 506, 116, 176, 170, 407, 8, 258, 412, 662, 624, 471, 35, 663, 482, 546, 157, 540, 431, 542, 297, 590, 552, 360, 628, 648, 327, 186, 516, 404, 564, 737, 3, 277, 184, 188, 526, 681, 298, 696, 674, 570, 133, 189, 22, 81, 430, 668, 521, 285, 340, 444, 292, 114, 381, 214, 562, 554, 420, 276, 479, 644, 144, 701, 100, 369, 787, 181, 790, 750, 748, 348, 669, 659, 625, 433, 443, 729, 631, 42, 244, 331, 413, 718, 204, 501, 725, 721, 332, 617, 789, 318, 262, 93, 40, 302, 428, 751, 621, 12, 635, 463, 439, 83, 37, 375, 616, 20, 91, 344, 266, 152, 273, 593, 72, 785, 14, 597, 756, 386, 354, 316, 269, 398, 248, 723, 303, 146, 653, 509, 747, 514, 446, 517, 626, 296, 691, 88, 447, 376, 752, 693, 113, 465, 379, 71, 85, 183, 614, 744, 74, 284, 462, 153, 343, 754, 793, 746, 117, 485, 156, 286, 774, 671, 103, 402, 457, 200, 16, 380, 190, 26, 646, 596, 427, 197, 704, 149, 397, 39, 384, 563, 703, 535, 451, 515, 495, 192, 222, 67, 253, 370, 508, 310, 165, 255, 541, 23, 19, 765, 578, 484, 630, 571, 174, 654, 511, 121, 372, 408, 132, 678, 52, 295, 688, 473, 274, 124, 388, 182, 643, 342, 775, 405, 50, 56, 741, 740, 129, 680};
#elif defined(LARGE_D)
  int array[SIZE] = {390, 55, 401, 290, 414, 549, 502, 254, 629, 560, 583, 528, 233, 178, 445, 458, 487, 126, 256, 798, 237, 530, 218, 706, 6, 618, 588, 205, 758, 90, 387, 336, 665, 320, 1, 185, 605, 692, 548, 7, 454, 708, 591, 362, 432, 658, 759, 655, 788, 314, 518, 622, 503, 97, 690, 483, 134, 722, 143, 724, 217, 308, 601, 173, 786, 539, 717, 333, 711, 389, 417, 453, 38, 476, 556, 94, 728, 742, 633, 418, 573, 545, 46, 441, 231, 64, 59, 234, 572, 9, 608, 193, 18, 45, 216, 151, 246, 66, 731, 656, 10, 627, 577, 2, 211, 202, 140, 125, 364, 468, 347, 236, 21, 632, 410, 226, 378, 393, 339, 210, 505, 416, 720, 355, 312, 686, 172, 136, 455, 351, 533, 685, 230, 150, 738, 239, 345, 411, 550, 642, 424, 162, 307, 794, 73, 437, 283, 194, 301, 377, 426, 337, 649, 795, 65, 127, 771, 155, 493, 647, 353, 776, 714, 24, 120, 28, 141, 317, 599, 682, 177, 291, 147, 757, 4, 489, 212, 198, 51, 268, 5, 415, 63, 660, 403, 199, 796, 422, 584, 137, 499, 709, 224, 131, 695, 531, 558, 278, 504, 324, 356, 228, 15, 672, 755, 326, 321, 119, 309, 130, 300, 265, 142, 766, 53, 349, 800, 592, 735, 249, 374, 689, 78, 779, 43, 27, 99, 753, 240, 768, 219, 749, 82, 289, 438, 551, 589, 429, 498, 764, 334, 305, 490, 507, 652, 582, 242, 168, 470, 148, 272, 359, 247, 679, 306, 215, 543, 395, 311, 154, 434, 710, 92, 705, 169, 367, 612, 760, 89, 594, 48, 95, 252, 670, 167, 75, 399, 251, 69, 361, 536, 392, 676, 547, 481, 34, 282, 576, 366, 76, 636, 293, 304, 699, 456, 213, 799, 179, 569, 486, 602, 330, 107, 201, 104, 567, 497, 180, 110, 730, 207, 145, 220, 620, 264, 474, 783, 527, 553, 294, 637, 780, 271, 657, 452, 223, 719, 371, 382, 350, 118, 54, 68, 373, 158, 425, 383, 694, 232, 440, 135, 41, 322, 159, 559, 700, 171, 565, 615, 450, 368, 781, 260, 31, 448, 323, 164, 111, 275, 461, 544, 684, 581, 109, 328, 229, 575, 623, 762, 664, 44, 138, 580, 163, 191, 733, 358, 726, 259, 25, 363, 587, 667, 763, 778, 313, 385, 478, 640, 494, 736, 96, 288, 523, 11, 797, 712, 761, 513, 115, 238, 568, 606, 739, 77, 609, 459, 610, 329, 102, 423, 634, 466, 105, 225, 287, 537, 773, 661, 106, 203, 335, 32, 98, 566, 613, 235, 469, 250, 492, 122, 639, 166, 491, 716, 175, 574, 245, 791, 561, 279, 112, 33, 208, 743, 604, 555, 270, 698, 532, 449, 666, 352, 645, 770, 17, 365, 585, 57, 70, 394, 36, 475, 607, 767, 101, 732, 480, 777, 13, 325, 60, 406, 160, 651, 80, 611, 600, 29, 534, 595, 280, 319, 341, 510, 522, 557, 195, 49, 538, 263, 772, 357, 619, 391, 267, 713, 227, 338, 299, 519, 435, 161, 488, 460, 677, 30, 603, 315, 123, 79, 650, 209, 257, 697, 734, 529, 638, 84, 707, 421, 477, 409, 683, 436, 784, 61, 400, 261, 346, 520, 396, 281, 598, 221, 586, 715, 675, 128, 87, 58, 464, 442, 579, 687, 62, 467, 187, 745, 419, 196, 496, 727, 641, 241, 769, 792, 139, 47, 524, 500, 525, 472, 512, 243, 108, 673, 86, 702, 206, 782, 506, 116, 176, 170, 407, 8, 258, 412, 662, 624, 471, 35, 663, 482, 546, 157, 540, 431, 542, 297, 590, 552, 360, 628, 648, 327, 186, 516, 404, 564, 737, 3, 277, 184, 188, 526, 681, 298, 696, 674, 570, 133, 189, 22, 81, 430, 668, 521, 285, 340, 444, 292, 114, 381, 214, 562, 554, 420, 276, 479, 644, 144, 701, 100, 369, 787, 181, 790, 750, 748, 348, 669, 659, 625, 433, 443, 729, 631, 42, 244, 331, 413, 718, 204, 501, 725, 721, 332, 617, 789, 318, 262, 93, 40, 302, 428, 751, 621, 12, 635, 463, 439, 83, 37, 375, 616, 20, 91, 344, 266, 152, 273, 593, 72, 785, 14, 597, 756, 386, 354, 316, 269, 398, 248, 723, 303, 146, 653, 509, 747, 514, 446, 517, 626, 296, 691, 88, 447, 376, 752, 693, 113, 465, 379, 71, 85, 183, 614, 744, 74, 284, 462, 153, 343, 754, 793, 746, 117, 485, 156, 286, 774, 671, 103, 402, 457, 200, 16, 380, 190, 26, 646, 596, 427, 197, 704, 149, 397, 39, 384, 563, 703, 535, 451, 515, 495, 192, 222, 67, 253, 370, 508, 310, 165, 255, 541, 23, 19, 765, 578, 484, 630, 571, 174, 654, 511, 121, 372, 408, 132, 678, 52, 295, 688, 473, 274, 124, 388, 182, 643, 342, 775, 405, 50, 56, 741, 740, 129, 680};
#else
  int array[SIZE] = {14, 66, 12, 41, 86, 69, 19, 77, 68, 38, 26, 42, 37, 23, 17, 29, 55, 13,
   90, 92, 76, 99, 10, 54, 57, 83, 40, 44, 75, 33, 24, 28, 80, 18, 78, 32, 93, 89, 52, 11,
   21, 96, 50, 15, 48, 63, 87, 20, 8, 85, 43, 16, 94, 88, 53, 84, 74, 91, 67, 36, 95, 61,
   64, 5, 30, 82, 72, 46, 59, 9, 7, 3, 39, 31, 4, 73, 70, 60, 58, 81, 56, 51, 45, 1, 6, 49,
   27, 47, 34, 35, 62, 97, 2, 79, 98, 25, 22, 65, 71, 0};
#endif

int array2[SIZE];

int benchmark()
{
  volatile int cnt=0;
  int tmp, found, index, i;

  for(i = 0 ;i<100; ++i)
    array2[i] = array[i];

  SGLIB_ARRAY_SINGLE_QUICK_SORT(int, array2, 100, SGLIB_NUMERIC_COMPARATOR);

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
