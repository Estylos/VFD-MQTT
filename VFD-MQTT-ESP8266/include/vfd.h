// Copyright (c) 2022 Esteban Cadic
// This code is licensed under MIT license (see LICENSE file for details)

#ifndef __VFD_H__
#define __VFD_H__

// Setup the screen
extern void vfdSetup(void);
// Write a byte to the screen (support Windows-1252 character percent-encoding)
extern void vfdWrite(unsigned char c);
// Clear the screen
extern void vfdClear(void);

#endif