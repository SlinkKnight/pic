/**
 * AUTO-GENERATED CCS Driver Header for IntelliSense
 * =================================================
 *
 * Mode: ONLY functions with pass-by-reference parameters
 * Files with existing .h headers were automatically skipped.
 * CCS pass-by-reference (int8 &hr) converted to pointers (uint8_t* hr)
 * Generated on: 2026-03-08 22:33:28 - Version: 5.123
 */

#ifdef __INTELLISENSE__

#include <stdbool.h>
#include <stdint.h>

/* From bq32000.c (no header found) */
extern void rtc_get_date(unsigned int8* day, unsigned int8* mth, unsigned int8* year, unsigned int8* dow);
extern void rtc_get_time(unsigned int8* hr, unsigned int8* min, unsigned int8* sec);

/* From ds1302.c (no header found) */
extern void rtc_get_date(unsigned int8* day, unsigned int8* mth, unsigned int8* year, unsigned int8* dow);
extern void rtc_get_time(unsigned int8* hr, unsigned int8* min, unsigned int8* sec);

/* From ds1305.c (no header found) */
extern void rtc_get_date(unsigned int8* day, unsigned int8* mth, unsigned int8* year, unsigned int8* dow);
extern void rtc_get_time(unsigned int8* hr, unsigned int8* min, unsigned int8* sec);

/* From ds1338.c (no header found) */
extern void rtc_get_date(unsigned int8* date, unsigned int8* mth, unsigned int8* year, unsigned int8* dow);
extern void rtc_get_time(unsigned int8* hr, unsigned int8* min, unsigned int8* sec);

/* From enc28j60.c (no header found) */
extern void enc_mac_control_reg_address(uint8_t* address);

/* From isl1209.c (no header found) */
extern void rtcc_get_time(uint8_t* sec, uint8_t* min, uint8_t* hour, uint8_t* day, uint8_t* mth, uint8_t* year, uint8_t* dow);
extern void rtcc_set_datetime(BYTE dow, BYTE year, BYTE mth, BYTE day, // Set date* time, BYTE min);

/* From mcp7940.c (no header found) */
extern void rtc_get_date(unsigned int8* day, unsigned int8* mth, unsigned int8* year, unsigned int8* dow);
extern void rtc_get_time(unsigned int8* hr, unsigned int8* min, unsigned int8* sec);

/* From mma8452q.c (no header found) */
extern void acc_read(int8 addr, uint16_t* x, uint16_t* y, uint16_t* z);

/* From n9085ud.c (no header found) */
extern uint8_t IR_decodeData(uint8_t* button, int16* width_buffer);
extern uint8_t readIRremote(uint8_t* button, int1 wait);

/* From nju6355.c (no header found) */
extern void rtc_get_date(unsigned int8* day, unsigned int8* mth, unsigned int8* year, unsigned int8* dow);
extern void rtc_get_time(unsigned int8* hr, unsigned int8* min, unsigned int8* sec);

/* From sim.c (no header found) */
extern uint8_t getNumber(phone_number* number, int8 slot);
extern void writeNumber(phone_number* number, unsigned int8 slot);

/* From wts701.c (no header found) */
extern uint8_t tts_continueAbbrTableRead(uint8_t* data);

#endif
/* Total: 21 functions from 12 files */