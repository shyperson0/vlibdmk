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

// vlibdmk.h

#ifndef VLIBDMK_H
#define VLIBDMK_H

#define RUNTIME_BULLETS 150000
#define BULLET_ACTIVE 1
#define BULLET_MOVING 2

#include <cstdint>

/**************************************/
/*This structure represents a bullet***/
/**************************************/
/*XPOS: X position*********************/
/*YPOS: Y position*********************/
/*XDIR: X direction********************/
/*YDIR: Y direction********************/
/*FLAG: Flags**************************/
/*SIDX: Sprite Index*******************/
/**************************************/
/**************************************/
/**************************************/
/**************************************/

#define XPOS 0
#define YPOS 1
#define XDEC 3
#define YDEC 4
#define XDIR 5
#define YDIR 6
#define ANGL 7
#define FLAG 8
#define SIDX 9
#define SIZE 10

class VLibDMK {
private:
	uint64_t bullet_idx = 0;
	static const uint64_t BULLET_SIZE = RUNTIME_BULLETS * SIZE;
public:
	uint8_t bullet_array[BULLET_SIZE];
	uint8_t get_bullet_data(uint64_t i_idx, uint8_t type);
	void set_bullet_data(uint64_t i_idx, uint8_t b_bullet, uint8_t type);
	
	void write_bullet(uint64_t i_idx, uint8_t xpos, uint8_t ypos, uint8_t xdec, uint8_t ydec, uint8_t xdir, uint8_t ydir, uint8_t angl, uint8_t flag, uint8_t sidx);
	
	uint64_t test();
	
	VLibDMK();
};

#endif // VLIBDMK_H
