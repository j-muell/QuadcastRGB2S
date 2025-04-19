/* quadcastrgb - set RGB lights of HyperX Quadcast S and DuoCast
 * File devio.h
 * Device input/output.
 * The device is microphone HyperX Quadcast S
 * distinguished by the VID & PID.
 *
 * <----- License notice ----->
 * Copyright (C) 2022, 2023, 2024 Ors1mer
 *
 * You may contact the author by email:
 * ors1mer [[at]] ors1mer dot xyz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License ONLY.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * <https://www.gnu.org/licenses/gpl-2.0.en.html>. For any questions
 * concerning the license, you can write to <licensing@fsf.org>.
 * Also, you may visit the Free Software Foundation at
 * 51 Franklin Street, Fifth Floor Boston, MA 02110 USA. 
 */
#ifndef DEVIO_SENTRY
#define DEVIO_SENTRY

#include <unistd.h> /* for usleep */
#include <libusb-1.0/libusb.h>
#include <fcntl.h> /* for daemonization */
#include <signal.h> /* for signal handling */
#include "locale_macros.h"
#include "rgbmodes.h" /* for datpack & byte_t types, count_color_pairs, defs */

/* Constants */
/* Vendor IDs */
#define DEV_VID_NA      0x0951
#define DEV_VID_EU      0x03f0
/* Product IDs */
#define DEV_PID_NA1     0x171f
#define DEV_PID_NA2     0x0d84
#define DEV_PID_NA3     0x02b5
#define DEV_PID_EU1     0x0f8b
#define DEV_PID_EU2     0x028c
#define DEV_PID_EU3     0x048c
#define DEV_PID_EU4     0x068c
#define DEV_PID_DUOCAST 0x098c

#define DEV_EPOUT 0x00 /* control endpoint OUT */
#define DEV_EPIN 0x80 /* control endpoint IN */
/* Packet info */
#define MAX_PCT_CNT 90
#define PACKET_SIZE 64 /* bytes */

#define HEADER_CODE 0x04
#define DISPLAY_CODE 0xf2
#define PACKET_CNT 0x01

#define INTR_EP_IN 0x82
#define INTR_LENGTH 8

#define TIMEOUT 1000 /* one second per packet */
#define BMREQUEST_TYPE_OUT 0x21
#define BREQUEST_OUT 0x09
#define BMREQUEST_TYPE_IN 0xa1
#define BREQUEST_IN 0x01
#define WVALUE 0x0300
#define WINDEX 0x0000

/* Messages */
#define DEVLIST_ERR_MSG _("Couldn't get the list of USB devices.\n")
#define NODEV_ERR_MSG _("HyperX Quadcast S isn't connected.\n")
#define OPEN_ERR_MSG _("Couldn't open the microphone.\n")
#define BUSY_ERR_MSG _("Another program is using the microphone already. " \
                       "Stopping.\n")
#define TRANSFER_ERR_MSG _("Couldn't transfer a packet! " \
                           "The device might be busy.\n")
#define FOOTER_ERR_MSG _("Footer packet error: %s\n")
#define HEADER_ERR_MSG _("Header packet error: %s\n")
#define SIZEPCK_ERR_MSG _("Size packet error: %s\n")
#define DATAPCK_ERR_MSG _("Data packet error: %s\n")
#define PID_MSG _("Started with pid %d\n")
/* Error codes */
enum {
    libusberr = 2,
    nodeverr,
    devopenerr,
    transfererr
};

/* Functions */
libusb_device_handle *open_micro(datpack *data_arr);
void send_packets(libusb_device_handle *handle, const datpack *data_arr,
                  int pck_cnt, int verbose);
#endif
