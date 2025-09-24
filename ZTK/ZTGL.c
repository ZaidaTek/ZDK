/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTGL_C_INCLUDED
#define ZTGL_C_INCLUDED

#include "ZTGL-RT.h"

void ZTGL_Size(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, rZTK_Host.rect.w, rZTK_Host.rect.h);
	gluOrtho2D(0.0, rZTK_Host.rect.w, 0.0, rZTK_Host.rect.h);
}
void ZTGL_Clear(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void ZTGL_ClearColor(ZT_COLOR iColor) {
	ZT_FLT lR = (ZT_FLT)ZTM_ColorR(iColor, rZTK_Host.user.palette) / 255.0;
	ZT_FLT lG = (ZT_FLT)ZTM_ColorG(iColor, rZTK_Host.user.palette) / 255.0;
	ZT_FLT lB = (ZT_FLT)ZTM_ColorB(iColor, rZTK_Host.user.palette) / 255.0;
	ZT_FLT lA = (ZT_FLT)ZTM_ColorA(iColor, rZTK_Host.user.palette) / 255.0;
	glClearColor(lR, lG, lB, lA);
}
void ZTGL_DrawPixels(const ZT_COLOR* iPixels, const ZT_POINT* iDimensions, const ZT_RECT* iTarget) {
	if (iDimensions->x && iDimensions->y) {glPixelZoom(iTarget->w / iDimensions->x, iTarget->h / iDimensions->y);} else {glPixelZoom(1.0, 1.0);} // hmmm...float for arbitrary zoom?
	glRasterPos2i(0, 0);
	glBitmap(0, 0, 0, 0, iTarget->x, rZTK_Host.rect.h - iTarget->y - iTarget->h, NULL);
	glDrawPixels(iDimensions->x, iDimensions->y, GL_RGBA, GL_UNSIGNED_BYTE, iPixels);
}
void ZTGL_DrawSurface(const ZT_SURFACE* iSurface, const ZT_RECT* iTarget) {
	ZTGL_DrawPixels(iSurface->pixels, &iSurface->block, iTarget);
}
void ZTGL_DrawSprite(const rZT_SPRITE* iSprite, const ZT_RECT* iTarget) {
	switch (iSprite->type) {
		case ZTK_SPRITE_TYPE_GLTEX: ZTGL_DrawTexture((ZT_FLAG)iSprite->data, iTarget); return;
		case ZTK_SPRITE_TYPE_GLPIXELS: ZTGL_DrawPixels(iSprite->data, &iSprite->block, iTarget); return;
		case ZTK_SPRITE_TYPE_PIXELS: ZTGL_DrawPixels(iSprite->data, &iSprite->block, iTarget); return;
		default: return;
	}
}
void ZTGL_DrawTexture(ZT_FLAG iID, const ZT_RECT* iTarget) {
	static ZT_I lLeft; static ZT_I lRight; static ZT_I lBottom; static ZT_I lTop;
	lRight = (lLeft = iTarget->x) + iTarget->w;
	lBottom = (lTop = rZTK_Host.rect.h - iTarget->y) - iTarget->h;
	glBindTexture(GL_TEXTURE_2D, (GLuint)iID);
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(lLeft, lBottom);
	glTexCoord2i(1, 0); glVertex2i(lRight, lBottom);
	glTexCoord2i(1, 1); glVertex2i(lRight, lTop);
	glTexCoord2i(0, 1); glVertex2i(lLeft, lTop);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);
}
void ZTGL_SpriteTextureFree(rZT_SPRITE* iSprite) {
	glDeleteTextures(1, (GLuint*)&iSprite->data);
}
rZT_SPRITE* ZTGL_Sprite(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette) {
	return ZTGL_SpriteTexture(iPixels, iBlock, iPalette);
	//return ZTGL_SpritePixel(iPixels, iBlock, iPalette);
}
rZT_SPRITE* ZTGL_SpritePixel(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette) {
	ZT_INDEX lLength;
	rZT_SPRITE* lSprite = ZTM8_New(sizeof(rZT_SPRITE));
	lSprite->type = ZTK_SPRITE_TYPE_GLPIXELS;
	lSprite->palette = rZTK_Host.system.palette;
	ZT_COLOR* lBuffer = ZTM32_New(lLength = (lSprite->block.x = iBlock->x) * (lSprite->block.y = iBlock->y));
	ZTM_PixelsFlipVertical(iPixels, lBuffer, iBlock);
	ZTM_PixelsConvert(lBuffer, lBuffer, lLength, iPalette, rZTK_Host.system.palette);
	lSprite->data = lBuffer;
	return lSprite;
}
rZT_SPRITE* ZTGL_SpriteTexture(const ZT_COLOR* iPixels, const ZT_POINT* iBlock, ZT_FLAG iPalette) {
	ZT_INDEX lLength;
	rZT_SPRITE* lSprite = ZTM8_New(sizeof(rZT_SPRITE));
	lSprite->type = ZTK_SPRITE_TYPE_GLTEX;
	lSprite->palette = rZTK_Host.system.palette;
	ZT_COLOR* lBuffer = ZTM32_New(lLength = (lSprite->block.x = iBlock->x) * (lSprite->block.y = iBlock->y));
	ZTM_PixelsFlipVertical(iPixels, lBuffer, iBlock);
	ZTM_PixelsConvert(lBuffer, lBuffer, lLength, iPalette, rZTK_Host.system.palette);
	glGenTextures(1, (GLuint*)&lSprite->data);
	glBindTexture(GL_TEXTURE_2D, (ZT_FLAG)lSprite->data);
	glTexImage2D(GL_TEXTURE_2D, ZTGL_MIPMAP_LEVEL, GL_RGBA, iBlock->x, iBlock->y, 0, GL_RGBA, GL_UNSIGNED_BYTE, lBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	ZTM32_Free(lBuffer);
	return lSprite;
}

#endif // ZTGL_C_INCLUDED
