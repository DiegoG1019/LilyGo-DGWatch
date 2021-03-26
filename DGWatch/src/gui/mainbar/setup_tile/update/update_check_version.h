/****************************************************************************
 *   July 28 00:23:05 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _UPDATE_CHECK_VERSION_H
    #define _UPDATE_CHECK_VERSION_H

    #include <TTGO.h>

    /**
     * @brief   get firmware discription file
     * 
     * @param   firmware discription file url
     * 
     * @return  0 if failed or version number
     */
    int64_t update_check_new_version( char *url );
    /**
     * @brief   get binary firmware file
     * 
     * @return  NULL if failed or pointer to the firmware file
     */
    const char* update_get_url( void );
    /**
     * @brief   get md5 hash of the firmware file
     * 
     * @return  NULL if failed or pointer to the md5 hash
     */
    const char* update_get_md5( void );
    /**
     * @brief   get comment from firmware discription
     * 
     * @return  NULL if failed or pointer to the discription
     */
    const char* update_get_comment( void );
    /**
     * @brief   get uncompressed firmware size
     * 
     * @return  <= 0 if unknown or size in bytes
     */
    int32_t update_get_size( void );

#endif // _UPDATE_CHECK_VERSION_H