#include "CTRTextureGouraud.h"

namespace irr
{
	namespace video
	{
		CTRTextureGouraud::CTRTextureGouraud(IZBuffer * zbuffer)
		{
			_renderTarget = 0;
			_zbuffer = zbuffer;
			_surfaceWidth = 0;
			_surfaceHeight = 0;
			_backFaceCullingEnabled = true;
			_lockedZBuffer = 0;
			_lockedSurface = 0;
			_lockedTexture = 0;
			_lockedTextureWidth = 0;
			_textureXMask = 0;
			_textureYMask = 0;
			_texture = 0;
			if (zbuffer)
			{
				zbuffer->grab();
			}
		}
		CTRTextureGouraud::~CTRTextureGouraud()
		{
			if (_renderTarget)
			{
				_renderTarget->drop();
			}
			if (_zbuffer)
			{
				_zbuffer->drop();
			}
			if (_texture)
			{
				_texture->drop();
			}
		}
		void CTRTextureGouraud::setRenderTarget(video::ISurface * surface, const core::rectEx<s32>& viewPort)
		{
			if (_renderTarget)
			{
				_renderTarget->drop();
			}
			_renderTarget = surface;
			if (_renderTarget)
			{
				_surfaceWidth = _renderTarget->getDimension()._width;
				_surfaceHeight = _renderTarget->getDimension()._height;
				_renderTarget->grab;
				_viewPortRect = viewPort;
			}
		}
		void CTRTextureGouraud::setBackfaceCulling(bool enable)
		{
			_backFaceCullingEnabled = enable;
		}
		void CTRTextureGouraud::setTexture(video::ISurface * texture)
		{
			if (_texture)
			{
				_texture->drop();
			}
			if (_texture)
			{
				_texture->grab();
				_lockedTextureWidth = _texture->getDimension()._width;
				_textureXMask = _lockedTextureWidth - 1;
				_textureYMask = _texture->getDimension()._height - 1;
			}
		}

		void CTRTextureGouraud::drawIndexedTriangleList(S2DVertex * vertices, s32 vertexCount, const u16 * indexList, s32 triangleCount)
		{
			const S2DVertex* v1, *v2, *v3;
			f32 tmpDiv;
			f32 longest;
			s32 height;
			u16* targetSurface;
			s32 spanEnd;
			f32 leftDeltaXF;
			f32 rightDeltaaXF;
			s32 leftX, rightX;
			f32 leftXF, rightXF;
			s32 span;
			u16* hSpanBegin, *hSpanEnd;
			s32 leftR, leftG, leftB, rightR, rightG, rightB;
			s32 leftStepR, leftStepG, leftStepB, rightStepR, rightStepG, rightStepB;
			s32 spanR, spanG, spanB, spanStepR, spanStepG, spanStepB;
			s32 leftTX, rightTX, leftTY, rightTY;
			s32 leftTXStep, rightTXStep, leftTYStep, rightTYStep;
			s32 spanTX, spanTY, spanTXStep, spanTYStep;
			core::rectEx<s32> triangleRect;
			s32 leftZValue, rightZValue;
			s32 leftZStep, rightZStep;
			s32 spanZValue, spanZStep;
			TZBufferType* zTarget, *spanZTarget;
			_lockedZBuffer = (u16*)_renderTarget->getData();
			_lockedZBuffer = _zbuffer->lock();
			_lockedTexture = (u16*)_texture->getData();
			for (s32 i = 0; i < triangleCount; i++)
			{
				v1 = &vertices[*indexList];
				++indexList;
				v2 = &vertices[*indexList];
				++indexList;
				v3 = &vertices[*indexList];
				++indexList;
				if (_backFaceCullingEnabled)
				{
					s32 z = ((v3->Pos.X - v1->Pos.X) * (v3->Pos.Y - v2->Pos.Y)) -
						((v3->Pos.Y - v1->Pos.Y) * (v3->Pos.X - v2->Pos.X));
					if (z < 0)
					{
						continue;
					}
				}
				if (v1->ZValue < 0 && v2->ZValue < 0 && v3->ZValue < 0)
				{
					continue;
				}

				if (v1->Pos.X > v2->Pos.X)
				{
					swapVertices(&v1, &v2);
				}
				if (v1->Pos.X > v3->Pos.X)
				{
					swapVertices(&v1, &v3);
				}
				if (v2->Pos.X > v3->Pos.X)
				{
					swapVertices(&v2, &v3);
				}

				if ((v1->Pos.X - v3->Pos.X) == 0 )
				{
					continue;
				}
				triangleRect._upperLeftCorner._x = v1->Pos.X;
				triangleRect._lowerRightCorner._x = v3->Pos.X;

				if (v1->Pos.Y > v2->Pos.Y)
				{
					swapVertices(&v1, &v2);
				}
				if (v1->Pos.Y > v3->Pos.Y)
				{
					swapVertices(&v1, &v3);
				}
				if (v2->Pos.Y > v3->Pos.Y)
				{
					swapVertices(&v2, &v3);
				}

				triangleRect._upperLeftCorner._y = v1->Pos.Y;
				triangleRect._lowerRightCorner._y = v3->Pos.Y;

				if (!triangleRect.isRectCollide(_viewPortRect))
				{
					continue;
				}
				height = v3->Pos.Y - v1->Pos.Y;
				if (!height)
				{
					continue;
				}
				longest = (v2->Pos.Y - v1->Pos.Y) / (f32)height * (v3->Pos.X - v1->Pos.X) + (v1->Pos.X - v2->Pos.X);
				spanEnd = v2->Pos.Y;
				span = v1->Pos.Y;
				leftXF = (f32)v1->Pos.X;
				rightXF = (f32)v1->Pos.X;
				leftZValue = v1->ZValue;
				rightZValue = v1->ZValue;

				leftR = rightR = video::getRed(v1->Color) << 8;
				leftG = rightG = video::getGreen(v1->Color) << 8;
				leftB = rightB = video::getBlue(v1->Color) << 8;
				leftTX = rightTX = v1->TCoords.X;
				leftTY = rightTY = v1->TCoords.Y;

				targetSurface = _lockedSurface + span * _surfaceWidth;
				zTarget = _lockedZBuffer + span * _surfaceWidth;
				if (longest < 0.0)
				{
					tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
					rightDeltaaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
					rightZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
					rightStepR = (s32)(((s32)(video::getRed(v2->Color) << 8) - rightR) * tmpDiv);
					rightStepG = (s32)(((s32)(video::getGreen(v2->Color) << 8) - rightG) * tmpDiv);
					rightStepB = (s32)(((s32)(video::getBlue(v2->Color) << 8) - rightB) * tmpDiv);
					rightTXStep = (s32)((v2->TCoords.X - rightTX) * tmpDiv);
					rightTYStep = (s32)((v2->TCoords.Y - rightTY) * tmpDiv);

					tmpDiv = 1.0f / (f32)height;
					leftDeltaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
					leftZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
					leftStepR = (s32)(((s32)(video::getRed(v3->Color) << 8) - leftR) * tmpDiv);
					leftStepG = (s32)(((s32)(video::getGreen(v3->Color) << 8) - leftG) * tmpDiv);
					leftStepB = (s32)(((s32)(video::getBlue(v3->Color) << 8) - leftB) * tmpDiv);
					leftTXStep = (s32)((v3->TCoords.X - leftTX) * tmpDiv);
					leftTYStep = (s32)((v3->TCoords.Y - leftTY) * tmpDiv);

				}
				else
				{
					tmpDiv = 1.0f / (f32)height;
					rightDeltaaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
					rightZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
					rightStepR = (s32)(((s32)(video::getRed(v3->Color) << 8) - rightR) * tmpDiv);
					rightStepG = (s32)(((s32)(video::getGreen(v3->Color) << 8) - rightG) * tmpDiv);
					rightStepB = (s32)(((s32)(video::getBlue(v3->Color) << 8) - rightB) * tmpDiv);
					rightTXStep = (s32)((v3->TCoords.X - rightTX) * tmpDiv);
					rightTYStep = (s32)((v3->TCoords.Y - rightTY) * tmpDiv);

					tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
					leftDeltaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
					leftZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
					leftStepR = (s32)(((s32)(video::getRed(v2->Color) << 8) - leftR) * tmpDiv);
					leftStepG = (s32)(((s32)(video::getGreen(v2->Color) << 8) - leftG) * tmpDiv);
					leftStepB = (s32)(((s32)(video::getBlue(v2->Color) << 8) - leftB) * tmpDiv);
					leftTXStep = (s32)((v2->TCoords.X - leftTX) * tmpDiv);
					leftTYStep = (s32)((v2->TCoords.Y - leftTY) * tmpDiv);
				}
				for (s32 triangleHalf = 0; triangleHalf < 2; triangleHalf++)
				{
					if (spanEnd > _viewPortRect._lowerRightCorner._y)
					{
						spanEnd = _viewPortRect._lowerRightCorner._y;
					}
					if (span < _viewPortRect._upperLeftCorner._y)
					{
						if (spanEnd < _viewPortRect._upperLeftCorner._y)
						{
							leftX = spanEnd - span;
							span = spanEnd;
						}
						else
						{
							leftX = _viewPortRect._upperLeftCorner._y - span;
							span = _viewPortRect._upperLeftCorner._y;
						}
						leftXF += leftDeltaXF * leftX;
						rightXF += rightDeltaaXF * leftX;
						targetSurface += _surfaceHeight * leftX;
						zTarget += _surfaceWidth * leftX;
						leftZValue += leftZStep * leftX;
						rightZValue += rightZStep * leftX;

						leftR += leftStepR * leftX;
						leftG += leftStepG * leftX;
						leftB += leftStepB * leftX;
						rightR += rightStepR * leftX;
						rightG += rightStepG * leftX;
						rightB += rightStepB * leftX;

						leftTX += leftTXStep * leftX;
						leftTY += leftTYStep * leftX;
						rightTX += rightTXStep * leftX;
						rightTY += rightTYStep * leftX;
					}
					while (span < spanEnd)
					{
						leftX = (s32)(leftXF);
						rightX = (s32)(rightXF + 0.5f);
						s32 tDiffLeft = 0, tDiffRight = 0;
						if (leftX < _viewPortRect._upperLeftCorner._x)
						{
							tDiffLeft = _viewPortRect._upperLeftCorner._x - leftX;
						}
						else
						if (leftX > _viewPortRect._lowerRightCorner._x)
						{
							tDiffLeft = _viewPortRect._lowerRightCorner._x - leftX;
						}

						if (rightX < _viewPortRect._upperLeftCorner._x)
						{
							tDiffRight = _viewPortRect._upperLeftCorner._x - rightX;
						}
						else if (rightX > _viewPortRect._lowerRightCorner._x)
						{
							tDiffRight = _viewPortRect._lowerRightCorner._x - rightX;
						}
						if (rightX + tDiffRight - leftX - tDiffLeft)
						{
							tmpDiv = 1.0f / (f32)(rightX - leftX);
							spanZStep = (s32)((rightZValue - leftZValue) * tmpDiv);
							spanZValue = leftZValue _ tDiffLeft * spanZStep;

							spanStepR = (s32)((rightR - leftR) * tmpDiv);
							spanR = leftR + tDiffLeft * spanStepR;
							spanStepG = (s32)((rightG - leftG) * tmpDiv);
							spanG = leftG + tDiffLeft * spanStepG;
							spanStepB = (s32)((rightB - leftB) * tmpDiv);
							spanB = leftB + tDiffLeft * spanStepB;

							spanTXStep = (s32)((rightTX - leftTX) * tmpDiv);
							spanTX = leftTX + tDiffLeft * spanTXStep;
							spanTYStep = (s32)((rightTY - leftTY) * tmpDiv);
							spanTY = leftTY + tDiffLeft * spanTYStep;

							hSpanBegin = targetSurface + leftX + tDiffLeft;
							spanZTarget = zTarget + leftX + tDiffLeft;
							hSpanEnd = targetSurface + rightX + tDiffRight;
							while (hSpanBegin < hSpanEnd)
							{
								if (spanZValue > *spanZTarget)
								{
									*spanZTarget = spanZValue;
									u16 color = _lockedTexture[((spanTY >> 8) & _textureYMask) * _lockedTextureWidth + ((spanTX >> 8) & _textureXMask)];
									*hSpanBegin = video::RGB16(video::getRed(color) * (spanR >> 8) >> 2,
										video::getGreen(color) * (spanG >> 8) >> 2,
										video::getBlue(color) * (spanB >> 8) >> 2);
								}
								spanR += spanStepR;
								spanG += spanStepG;
								spanB += spanStepB;

								spanTX += spanTXStep;
								spanTY += spanTYStep;

								spanZValue += spanZStep;
								++spanZTarget;
							}
						}
						leftXF += leftDeltaXF;
						rightXF += rightDeltaaXF;
						++span;
						targetSurface += _surfaceWidth;
						zTarget += _surfaceWidth;
						leftZValue += leftZStep;
						rightZValue += rightZStep;

						leftR += leftStepR;
						leftG += leftStepG;
						leftB += leftStepB;
						rightR += rightStepR;
						rightG += rightStepG;
						rightB += rightStepB;

						leftTX += leftTXStep;
						leftTY += leftTYStep;
						rightTX += rightTXStep;
						rightTY += rightTYStep;

					}
					if (triangleHalf > 0)
					{
						break;
					}
					if (longest < 0.0f)
					{
						tmpDiv = 1.0f / (v3->Pos.Y - v2->Pos.Y);
						rightDeltaaXF = (v3->Pos.X - v2->Pos.X) * tmpDiv;
						rightXF = (f32)v2->Pos.X;
						rightZValue = v2->ZValue;
						rightZStep = (s32)((v3->ZValue - v2->ZValue) * tmpDiv);

						rightR = video::getRed(v2->Color) << 8;
						rightG = video::getGreen(v2->Color) << 8;
						rightB = video::getBlue(v2->Color) << 8;
						rightStepR = (s32)(((s32)(video::getRed(v3->Color) << 8) - rightR) * tmpDiv);
						rightStepG = (s32)(((s32)(video::getGreen(v3->Color) << 8) - rightG) * tmpDiv);
						rightStepB = (s32)(((s32)(video::getBlue(v3->Color) << 8) - rightB) * tmpDiv);
						rightTX = v2->TCoords.X;
						rightTY = v2->TCoords.Y;
						rightTXStep = (s32)((v3->TCoords.X - rightTX) * tmpDiv);
						rightTYStep = (s32)((v3->TCoords.Y - rightTY) * tmpDiv);

						
					}
					else
					{
						tmpDiv = 1.0f / (v3->Pos.Y - v2->Pos.Y);
						leftDeltaXF = (v3->Pos.X - v2->Pos.X) * tmpDiv;
						leftXF = (f32)v2->Pos.X;
						leftZValue = v2->ZValue;
						leftZStep = (s32)((v3->ZValue - v2->ZValue) * tmpDiv);
						
						leftR = video::getRed(v2->Color) << 8;
						leftG = video::getGreen(v2->Color) << 8;
						leftB = video::getBlue(v2->Color) << 8;
						leftStepR = (s32)(((s32)(video::getRed(v3->Color) << 8) - leftR) * tmpDiv);
						leftStepG = (s32)(((s32)(video::getGreen(v3->Color) << 8) - leftG) * tmpDiv);
						leftStepB = (s32)(((s32)(video::getBlue(v3->Color) << 8) - leftB) * tmpDiv);
						leftTX = v2->TCoords.X;
						leftTY = v2->TCoords.Y;
						leftTXStep = (s32)((v3->TCoords.X - leftTX) * tmpDiv);
						leftTYStep = (s32)((v3->TCoords.Y - leftTY) * tmpDiv);

					}
					spanEnd = v3->Pos.Y;
				}
			}

			_zbuffer->unlock();

		}
	
	}
}
namespace irr
{
	namespace video
	{
		IK3DtriangleRenderer* createTriangleRendererTextureGouraud(IZBuffer* zBuffer)
		{
			return new CTRTextureGouraud(zBuffer);
		}
	}
}