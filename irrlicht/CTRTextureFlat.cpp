
#include "CTRTextureGouraud.h"

namespace irr
{
	namespace video
	{
		class CTRTextureFlat : public CTRTextureGouraud
		{
		public:
			CTRTextureFlat(IZBuffer* zbuffer)
				: CTRTextureGouraud(zbuffer)
			{

			}


			virtual void drawIndexedTriangleList(S2DVertex * vertices, s32 vertexCount, const u16 * indexList, s32 triangleCount)
			{
				const S2DVertex* v1, *v2, *v3;
				f32 tmpDiv;
				f32 longest;
				s32 height;
				u16* targetSurface;
				s32 spanEnd;
				f32 leftDeltaXF;
				f32 rightDeltaXF;
				s32 leftX, rightX;
				f32 leftXF, rightXF;
				s32 span;
				u16* hSpanBegin, *hSpanEnd;
				s32 leftTX, rightTX, leftTY, rightTY;
				s32 leftTXStep, rightTXStep, leftTYStep, rightTYStep;
				s32 spanTX, spanTY, spanTXStep, spanTYStep;
				core::rectEx<s32> triangleRect;

				s32 leftZValue, rightZValue;
				s32 leftZStep, rightZStep;
				s32 spanZValue, spanZStep;
				TZBufferType* zTarget, *spanZTarget;
				_lockedSurface = (u16*)_renderTarget->getData();
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

					if ((v1->Pos.X - v3->Pos.X) == 0)
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

					leftTX = rightTX = v1->TCoords.X;
					leftTY = rightTY = v1->TCoords.Y;

					targetSurface = _lockedSurface + span * _surfaceWidth;
					zTarget = _lockedZBuffer + span * _surfaceWidth;
					if (longest < 0.0)
					{
						tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
						rightDeltaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
						rightZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
						rightTXStep = (s32)((v2->TCoords.X - rightTX) * tmpDiv);
						rightTYStep = (s32)((v2->TCoords.Y - rightTY) * tmpDiv);

						tmpDiv = 1.0f / (f32)height;
						leftDeltaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
						leftZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
						leftTXStep = (s32)((v3->TCoords.X - leftTX) * tmpDiv);
						leftTYStep = (s32)((v3->TCoords.Y - leftTY) * tmpDiv);

					}
					else
					{
						tmpDiv = 1.0f / (f32)height;
						rightDeltaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
						rightZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
						rightTXStep = (s32)((v3->TCoords.X - rightTX) * tmpDiv);
						rightTYStep = (s32)((v3->TCoords.Y - rightTY) * tmpDiv);

						tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
						leftDeltaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
						leftZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
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
							rightXF += rightDeltaXF * leftX;
							targetSurface += _surfaceHeight * leftX;
							zTarget += _surfaceWidth * leftX;
							leftZValue += leftZStep * leftX;
							rightZValue += rightZStep * leftX;

							leftTX += leftTXStep * leftX;
							leftTY += leftTYStep * leftX;
							rightTX += rightTXStep * leftX;
							rightTY += rightTYStep * leftX;
						}
						while (span < spanEnd)
						{
							leftX = (s32)(leftXF);
							rightX = (s32)(rightXF + 0.5f);
							if (leftX < _viewPortRect._upperLeftCorner._x)
							{
								leftX = _viewPortRect._upperLeftCorner._x ;
							}
							else
								if (leftX > _viewPortRect._lowerRightCorner._x)
								{
									leftX = _viewPortRect._lowerRightCorner._x ;
								}

							if (rightX < _viewPortRect._upperLeftCorner._x)
							{
								rightX = _viewPortRect._upperLeftCorner._x;
							}
							else if (rightX > _viewPortRect._lowerRightCorner._x)
							{
								rightX = _viewPortRect._lowerRightCorner._x ;
							}
							if (rightX - leftX != 0)
							{
								tmpDiv = 1.0f / (f32)(rightX - leftX);
								spanZValue = leftZValue;
								spanZStep = (s32)((rightZValue - leftZValue) * tmpDiv);

								hSpanBegin = targetSurface + leftX;
								spanZTarget = zTarget + leftX;
								hSpanEnd = targetSurface + rightX;

								spanTX = leftTX ;
								spanTY = leftTY ;
								spanTXStep = (s32)((rightTX - leftTX) * tmpDiv);
								spanTYStep = (s32)((rightTY - leftTY) * tmpDiv);

								while (hSpanBegin < hSpanEnd)
								{
									if (spanZValue > *spanZTarget)
									{
										*spanZTarget = spanZValue;
										*hSpanBegin = _lockedTexture[((spanTY >> 8) & _textureYMask) * _lockedTextureWidth + ((spanTX >> 8) & _textureXMask)];
									}
									spanTX += spanTXStep;
									spanTY += spanTYStep;

									spanZValue += spanZStep;
									++hSpanBegin;
									++spanZTarget;
								}
							}
							leftXF += leftDeltaXF;
							rightXF += rightDeltaXF;
							++span;
							targetSurface += _surfaceWidth;
							zTarget += _surfaceWidth;
							leftZValue += leftZStep;
							rightZValue += rightZStep;

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
							rightDeltaXF = (v3->Pos.X - v2->Pos.X) * tmpDiv;
							rightXF = (f32)v2->Pos.X;
							rightZValue = v2->ZValue;
							rightZStep = (s32)((v3->ZValue - v2->ZValue) * tmpDiv);

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
		};
	}
}
namespace irr
{
	namespace video
	{
		IK3DtriangleRenderer* createTriangleRendererTextureFlat(IZBuffer* zBuffer)
		{
			return new CTRTextureFlat(zBuffer);
		}
	}
}