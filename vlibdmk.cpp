/**************************************************/
/*                 Pomy License v1                */
/*      (C)Violence (2024)                        */
/*Thou, the licensee, art granted                 */
/* the noble right to:                            */
/*                                                */
/*Engage in the act of copying                    */
/*Embark upon the journey of modification         */
/*Bestow the gift of redistribution               */
/*Safeguard with the assistance of a back up      */
/*Otherwise partake in the utilization of         */
/* this source code, whether in its entirety      */
/* or in part, provided thou dost assent to       */
/* the following stipulations:                    */
/*                                                */
/*To relinquish the author from all burden of     */
/* responsibility, be it great or small, for      */
/* any and all damages                            */
/*To disseminate derivative works along with a    */
/* faithful copy of this license, even should     */
/* the derivative work seek refuge under divergent*/
/* terms of licensing                             */
/**************************************************/

// vlibdmk.cpp

#include "include/vlibdmk.h"

uint8_t VLibDMK::get_bullet_data(uint64_t i_idx, uint8_t type){
	return bullet_array[SIZE * i_idx + type];
}

void VLibDMK::set_bullet_data(uint64_t i_idx, uint8_t data, uint8_t type){
	bullet_array[SIZE * i_idx + type] = data;
	return;
}

void VLibDMK::write_bullet(uint64_t i_idx, uint8_t xpos, uint8_t ypos, uint8_t xdec, uint8_t ydec, uint8_t xdir, uint8_t ydir, uint8_t angl, uint8_t flag, uint8_t sidx){
	set_bullet_data(i_idx, xpos, XPOS);
	set_bullet_data(i_idx, ypos, YPOS);
	set_bullet_data(i_idx, xdec, XDEC);
	set_bullet_data(i_idx, ydec, YDEC);
	set_bullet_data(i_idx, xdir, XDIR);
	set_bullet_data(i_idx, ydir, YDIR);
	set_bullet_data(i_idx, angl, ANGL);
	set_bullet_data(i_idx, flag, FLAG);
	set_bullet_data(i_idx, sidx, SIDX);
	return;
}

VLibDMK::VLibDMK(){
}
