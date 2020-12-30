//
// Created by gareth on 29/12/2020.
//

#ifndef ELECTRONICLOAD_CLOCK_TREE_H
#define ELECTRONICLOAD_CLOCK_TREE_H

#include "stm32g0xx.h"

/* Clock source :- HSI (16MHz)
 * AHB Prescaler :- 1
 * APB Prescaler :- 1
 * Clock source :- HSI (No PLL)
 *
 * */

void init_clock_tree(void);

#endif //ELECTRONICLOAD_CLOCK_TREE_H
