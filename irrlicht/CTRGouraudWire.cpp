
#include "CTRTextureGouraud.h"

namespace irr
{
	namespace video
	{
		class CTRGouraudWire : public CTRTextureGouraud
		{
		public:
			CTRGouraudWire(IZBuffer* zbuffer)
				: CTRTextureGouraud(zbuffer)
			{

			}

			virtual void drawIndexedTriangleList(S2DVertex * vertices, s32 vertexCount, const u16 * indexList, s32 triangleCount)
			{
				const S2DVertex* v1, *v2, *v3;
				f32 tmpDiv;
				f32 logest;
				s32 height;
				u16* targetSurface;
				s32 spanEnd;
				f32 leftDeltaXF;
				f32 rightDeltaaXF;
				s32 leftX, rightX;
				f32 leftXF, rightXF;
				s32 span;
				s32 leftR, leftG, leftB, rightR, rightG, rightB;
				s32 leftStepR, leftStepG, leftStepB, rightStepR, rightStepG, rightStepB;

				core::rectEx<s32> triangleRect;
				s32 leftZValue, rightZValue;
				s32 leftZStep, rightZStep;
				TZBufferType* zTarget;
				_lockedSurface = (u16*)_renderTarget->getData();
				_lockedZBuffer = _zbuffer->lock();
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
					logest = (v2->Pos.Y - v1->Pos.Y) / (f32)height * (v3->Pos.X - v1->Pos.X) + (v1->Pos.X - v2->Pos.X);
					spanEnd = v2->Pos.Y;
					span = v1->Pos.Y;
					leftXF = (f32)v1->Pos.X;
					rightXF = (f32)v1->Pos.X;
					leftZValue = v1->ZValue;
					rightZValue = v1->ZValue;

					leftR = rightR = video::getRed(v1->Color) << 11;
					leftG = rightG = video::getGreen(v1->Color) << 11;
					leftB = rightB = video::getBlue(v1->Color) << 11;

					targetSurface = _lockedSurface + span * _surfaceWidth;
					zTarget = _lockedZBuffer + span * _surfaceWidth;
					if (logest < 0.0)
					{
						tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
						rightDeltaaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
						rightZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
						rightStepR = (s32)(((s32)(video::getRed(v2->Color) << 11) - rightR) * tmpDiv);
						rightStepG = (s32)(((s32)(video::getGreen(v2->Color) << 11) - rightG) * tmpDiv);
						rightStepB = (s32)(((s32)(video::getBlue(v2->Color) << 11) - rightB) * tmpDiv);

						tmpDiv = 1.0f / (f32)height;
						leftDeltaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
						leftZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
						leftStepR = (s32)(((s32)(video::getRed(v3->Color) << 11) - leftR) * tmpDiv);
						leftStepG = (s32)(((s32)(video::getGreen(v3->Color) << 11) - leftG) * tmpDiv);
						leftStepB = (s32)(((s32)(video::getBlue(v3->Color) << 11) - leftB) * tmpDiv);

					}
					else
					{
						tmpDiv = 1.0f / (f32)height;
						rightDeltaaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
						rightZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
						rightStepR = (s32)(((s32)(video::getRed(v3->Color) << 11) - rightR) * tmpDiv);
						rightStepG = (s32)(((s32)(video::getGreen(v3->Color) << 11) - rightG) * tmpDiv);
						rightStepB = (s32)(((s32)(video::getBlue(v3->Color) << 11) - rightB) * tmpDiv);

						tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
						leftDeltaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
						leftZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
						leftStepR = (s32)(((s32)(video::getRed(v2->Color) << 11) - leftR) * tmpDiv);
						leftStepG = (s32)(((s32)(video::getGreen(v2->Color) << 11) - leftG) * tmpDiv);
						leftStepB = (s32)(((s32)(video::getBlue(v2->Color) << 11) - leftB) * tmpDiv);
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
							targetSurface += _surfaceWidth * leftX;
							zTarget += _surfaceWidth * leftX;
							leftZValue += leftZStep * leftX;
							rightZValue += rightZStep * leftX;

							leftR += leftStepR * leftX;
							leftG += leftStepG * leftX;
							leftB += leftStepB * leftX;
							rightR += rightStepR * leftX;
							rightG += rightStepG * leftX;
							rightB += rightStepB * leftX;
						}
						while (span < spanEnd)
						{
							leftX = (s32)(leftXF);
							rightX = (s32)(rightXF + 0.5f);
							if (leftX >= _viewPortRect._upperLeftCorner._x && 
								leftX <= _viewPortRect._lowerRightCorner._x)
							{
								if (leftZValue >* (zTarget+leftX))
								{
									*(zTarget + leftX) = leftZValue;
									*(targetSurface + leftX) = video::RGB16(leftR >> 8, leftG >> 8, leftB >> 8);
								}
							}

							if (rightX >= _viewPortRect._upperLeftCorner._x &&
								rightX <= _viewPortRect._lowerRightCorner._x)
							{
								if (rightZValue >* (zTarget + rightX))
								{
									*(zTarget + rightX) = rightZValue;
									*(targetSurface + rightX) = video::RGB16(rightR, rightG, rightB);
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

						}
						if (triangleHalf > 0)
						{
							break;
						}
						if (logest < 0.0f)
						{
							tmpDiv = 1.0f / (v3->Pos.Y - v2->Pos.Y);
							rightDeltaaXF = (v3->Pos.X - v2->Pos.X) * tmpDiv;
							rightXF = (f32)v2->Pos.X;
							rightZValue = v2->ZValue;
							rightZStep = (s32)((v3->ZValue - v2->ZValue) * tmpDiv);

							rightR = video::getRed(v2->Color) << 11;
							rightG = video::getGreen(v2->Color) << 11;
							rightB = video::getBlue(v2->Color) << 11;
							rightStepR = (s32)(((s32)(video::getRed(v3->Color) << 11) - rightR) * tmpDiv);
							rightStepG = (s32)(((s32)(video::getGreen(v3->Color) << 11) - rightG) * tmpDiv);
							rightStepB = (s32)(((s32)(video::getBlue(v3->Color) << 11) - rightB) * tmpDiv);


						}
						else
						{
							tmpDiv = 1.0f / (v3->Pos.Y - v2->Pos.Y);
							leftDeltaXF = (v3->Pos.X - v2->Pos.X) * tmpDiv;
							leftXF = (f32)v2->Pos.X;
							leftZValue = v2->ZValue;
							leftZStep = (s32)((v3->ZValue - v2->ZValue) * tmpDiv);

							leftR = video::getRed(v2->Color) << 11;
							leftG = video::getGreen(v2->Color) << 11;
							leftB = video::getBlue(v2->Color) << 11;
							leftStepR = (s32)(((s32)(video::getRed(v3->Color) << 11) - leftR) * tmpDiv);
							leftStepG = (s32)(((s32)(video::getGreen(v3->Color) << 11) - leftG) * tmpDiv);
							leftStepB = (s32)(((s32)(video::getBlue(v3->Color) << 11) - leftB) * tmpDiv);

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
		IK3DtriangleRenderer* createTriangleRendererGouraud(IZBuffer* zBuffer)
		{
#ifdef _IRR_COMPILE_WITH_SOFTWARE_
			return new CTRGouraudWire(zBuffer);
#else
			return 0;
#endif
		}
	}
}