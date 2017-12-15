#pragma once

//
// Created by adun on 2017. 11. 20..
//

#include <string>
#include <GL\freeglut.h>
#include "log.h"
#include <FreeImage.h>

namespace AdunGL
{
	namespace utils
	{
		static BYTE* load_image(const char* fileName, GLsizei* width, GLsizei* height, unsigned int* bits)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

			FIBITMAP* dib = nullptr;

			fif = FreeImage_GetFileType(fileName, 0);

			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(fileName);

			if (fif == FIF_UNKNOWN)
				return nullptr;

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, fileName);

			if (!dib)
			{
				ADUNGL_FATAL("[imageload.h 35] Could not load image: '%s'", fileName);
				return nullptr;
			}

			BYTE* pixels = FreeImage_GetBits(dib);

			*width = FreeImage_GetWidth(dib);

			*height = FreeImage_GetHeight(dib);

			*bits = FreeImage_GetBPP(dib);

			int size = *width * *height * (*bits / 8);

			BYTE* result = new BYTE[size];

			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			ADUNGL_INFO("[imageload.h 56] Load image success: '%s'", fileName);

			return result;
		}
	}
}