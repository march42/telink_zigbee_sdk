/********************************************************************************************************
 * @file    random.h
 *
 * @brief   This is the header file for B85
 *
 * @author  Driver & Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *			All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/

#pragma once


/**
 * @brief     This function performs to initials random generator post.
 * @param[in] none.
 * @return    none.
 */
void random_generator_init(void);

/**
 * @brief     This function performs to get one random number
 * @param[in] none.
 * @return    the value of one random number.
 */
unsigned int telink_rand(void);



