/*
  $Id: eject.cpp,v 1.1 2005/11/07 07:53:40 rocky Exp $

  Copyright (C) 2005 Rocky Bernstein <rocky@panix.com>
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* Simple program to eject a CD-ROM drive door and then close it again.

   If a single argument is given, it is used as the CD-ROM device to 
   eject/close. Otherwise a CD-ROM drive will be scanned for.
*/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <cdio/cdio.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif

int
main(int argc, const char *argv[])
{
  driver_return_code_t ret;
  driver_id_t driver_id = DRIVER_DEVICE;
  char *psz_drive = NULL;
  
  if (argc > 1) 
    psz_drive = strdup(argv[1]);

  if (!psz_drive) {
    psz_drive = cdio_get_default_device_driver(&driver_id);
    if (!psz_drive) {
      printf("Can't find a CD-ROM to eject\n");
      exit(1);
    }
  }
  ret = cdio_eject_media_drive(psz_drive);
  switch(ret) {
  case DRIVER_OP_UNSUPPORTED:
    printf("Eject not supported for %s.\n", psz_drive);
    break;
  case DRIVER_OP_SUCCESS:
    printf("CD-ROM drive %s ejected.\n", psz_drive);
    break;
  default:
    printf("Eject of CD-ROM drive %s failed.\n", psz_drive);
    break;
  }
  
  if (DRIVER_OP_SUCCESS == cdio_close_tray(psz_drive, &driver_id)) {
    printf("Closed tray of CD-ROM drive %s.\n", psz_drive);
  } else {
    printf("Closing tray of CD-ROM drive %s failed.\n", psz_drive);
  }
  free(psz_drive);
  
  return 0;
}