/*
 * img_enhance.c
 *
 * Part of a processor program for raw data from JL2005B/C/D cameras.
 * Based on previous work for several other cameras.
 *
 * Copyright (c) 2010 Theodore Kilgore <kilgota@auburn.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * A previous version of the white_balance() function intended for use in
 * libgphoto2/camlibs/aox is copyright (c) 2008 Amauri Magagna.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "gamma.h"
#include "gamma.c"
#include "bayer.h"
#include "img_enhance.h"



/*	===== White Balance / Color Enhance / Gamma adjust =====

	Get histogram for each color plane
	Expand to reach 0.5% of white dots in image

	Get new histogram for each color plane
	Expand to reach 0.5% of black dots in image

	Get new histogram
	Calculate and apply gamma correction

	If not a dark image:
	For each dot, increase the color separation

	========================================================== */

int
histogram (unsigned char *data, unsigned int size, int *htable_r,
						int *htable_g, int *htable_b)
{
	int x;
	/* Initializations */
	for (x = 0; x < 0x100; x++) {
		htable_r[x] = 0;
		htable_g[x] = 0;
		htable_b[x] = 0;
	}
	/* Building the histograms */
	for (x = 0; x < (size * 3); x += 3)
	{

		htable_r[data[x + 0]]++;	/* red histogram */
		htable_g[data[x + 1]]++;	/* green histogram */
		htable_b[data[x + 2]]++;	/* blue histogram */
	}
	return 0;
}

int
white_balance (unsigned char *data, unsigned int size, float saturation)
{
	int x, r, g, b, max, d;
	double r_factor, g_factor, b_factor, max_factor;
	int htable_r[0x100], htable_g[0x100], htable_b[0x100];
	BYTE gtable[0x100];
	double new_gamma, gamma = 1.0;

	/* ------------------- GAMMA CORRECTION ------------------- */

	histogram(data, size, htable_r, htable_g, htable_b);
	x = 1;
	for (r = 64; r < 192; r++)
	{
		x += htable_r[r];
		x += htable_g[r];
		x += htable_b[r];
	}
	new_gamma = sqrt((double) (x * 1.5) / (double) (size * 3));
	printf("Provisional gamma correction = %1.2f\n", new_gamma);
	/* Recalculate saturation factor for later use. */
	saturation = saturation * new_gamma * new_gamma;
	printf("saturation = %1.2f\n", saturation);
	gamma = new_gamma;
	if (new_gamma < .70)
		gamma = 0.70;
	if (new_gamma > 1.2)
		gamma = 1.2;
	printf("Gamma correction = %1.2f\n", gamma);
	gp_gamma_fill_table(gtable, gamma);
	gp_gamma_correct_single(gtable, data, size);
	if (saturation < .5 ) /* If so, exit now. */
		return 0;

	/* ---------------- BRIGHT DOTS ------------------- */
	max = size / 200;
	histogram(data, size, htable_r, htable_g, htable_b);

	for (r = 0xfe, x = 0; (r > 32) && (x < max); r--)
		x += htable_r[r];
	for (g = 0xfe, x = 0; (g > 32) && (x < max); g--)
		x += htable_g[g];
	for (b = 0xfe, x = 0; (b > 32) && (x < max); b--)
		x += htable_b[b];
	r_factor = (double) 0xfd / r;
	g_factor = (double) 0xfd / g;
	b_factor = (double) 0xfd / b;

	max_factor = r_factor;
	if (g_factor > max_factor) max_factor = g_factor;
	if (b_factor > max_factor) max_factor = b_factor;
	if (max_factor >= 4.0) {
	/*
	 * We need a little bit of control, here. If max_factor is big
	 * then the photo was very dark, after all.
	 */
		if (2.0 * b_factor < max_factor)
			b_factor = max_factor / 2.;
		if (2.0 * r_factor < max_factor)
			r_factor = max_factor / 2.;
		if (2.0 * g_factor < max_factor)
			g_factor = max_factor/2.;
		r_factor = (r_factor / max_factor) * 4.0;
		g_factor = (g_factor / max_factor) * 4.0;
		b_factor = (b_factor / max_factor) * 4.0;
	}

	if (max_factor > 1.5)
		saturation = 0;
	printf("White balance (bright): ");
	printf("r=%1d, g=%1d, b=%1d, fr=%1.3f, fg=%1.3f, fb=%1.3f\n",
			r, g, b, r_factor, g_factor, b_factor);
	if (max_factor <= 1.4) {
		for (x = 0; x < (size * 3); x += 3)
		{
			d = (data[x + 0] << 8) * r_factor + 8;
			d >>= 8;
			if (d > 0xff) { d = 0xff; }
			data[x + 0] = d;
			d = (data[x + 1] << 8) * g_factor + 8;
			d >>= 8;
			if (d > 0xff) { d = 0xff; }
			data[x + 1] = d;
			d = (data[x + 2] << 8) * b_factor + 8;
			d >>= 8;
			if (d > 0xff) { d = 0xff; }
			data[x + 2] = d;
		}
	}
	/* ---------------- DARK DOTS ------------------- */
	max = size / 200;  /*  1/200 = 0.5%  */
	histogram(data, size, htable_r, htable_g, htable_b);

	for (r = 0, x = 0; (r < 96) && (x < max); r++)
		x += htable_r[r];
	for (g = 0, x = 0; (g < 96) && (x < max); g++)
		x += htable_g[g];
	for (b = 0, x = 0; (b < 96) && (x < max); b++)
		x += htable_b[b];

	r_factor = (double) 0xfe / (0xff - r);
	g_factor = (double) 0xfe / (0xff - g);
	b_factor = (double) 0xfe / (0xff - b);

	printf("White balance (dark): ");
	printf("r=%1d, g=%1d, b=%1d, fr=%1.3f, fg=%1.3f, fb=%1.3f\n",
			r, g, b, r_factor, g_factor, b_factor);

	for (x = 0; x < (size * 3); x += 3)
	{
		d = (int) 0xff08 - (((0xff - data[x + 0]) << 8) * r_factor);
		d >>= 8;
		if (d < 0) { d = 0; }
		data[x + 0] = d;
		d = (int) 0xff08 - (((0xff - data[x + 1]) << 8) * g_factor);
		d >>= 8;
		if (d < 0) { d = 0; }
		data[x + 1] = d;
		d = (int) 0xff08 - (((0xff - data[x + 2]) << 8) * b_factor);
		d >>= 8;
		if (d < 0) { d = 0; }
		data[x + 2] = d;
	}

	/* ------------------ COLOR ENHANCE ------------------ */

	if(saturation > 0.0) {
		for (x = 0; x < (size * 3); x += 3)
		{
			r = data[x + 0]; g = data[x + 1]; b = data[x + 2];
			d = (int) (r + g + b) / 3.;
			if ( r > d )
				r = r + (int) ((r - d)
						* (0xff - r) / (0x100 - d)
							* saturation);
			else
				r = r + (int) ((r - d)
						* (0xff - d) / (0x100 - r)
							* saturation);
			if (g > d)
				g = g + (int) ((g - d)
						* (0xff - g) / (0x100 - d)
							* saturation);
			else
				g = g + (int) ((g - d)
						* (0xff - d) / (0x100 - g)
							* saturation);
			if (b > d)
				b = b + (int) ((b - d)
						* (0xff - b) / (0x100 - d)
							* saturation);
			else
				b = b + (int) ((b - d)
						* (0xff - d) / (0x100 - b)
							* saturation);
			data[x + 0] = CLAMP(r);
			data[x + 1] = CLAMP(g);
			data[x + 2] = CLAMP(b);
		}
	}
	return 0;
}
