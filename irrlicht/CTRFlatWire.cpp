
#include "CTRTextureGouraud.h"

namespace irr
{
	namespace video
	{
		class CTRFlatWire : public CTRTextureGouraud
		{
		public:
			CTRFlatWire(IZBuffer* zbuffer)
				: CTRTextureGouraud(zbuffer)
			{

			}

			virtual void drawIndexedTriangleList(S2DVertex * vertices, s32 vertexCount, const u16 * indexList, s32 triangleCount)
			{
				const S2DVertex* v1, *v2, *v3;

				u16 color;

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
				u16* hSpanBegin, *hSpanEnd;

				core::rectEx<s32> triangleRect;
				s32 leftZValue, rightZValue;
				s32 leftZStep, rightZStep;
				TZBufferType* zTarget;
				_lockedZBuffer = (u16*)_renderTarget->getData();
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

					color = v1->Color;
					targetSurface = _lockedSurface + span * _surfaceWidth;
					zTarget = _lockedZBuffer + span * _surfaceWidth;
					if (logest < 0.0)
					{
						tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
						rightDeltaaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
						rightZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);

						tmpDiv = 1.0f / (f32)height;
						leftDeltaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
						leftZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);
					}
					else
					{
						tmpDiv = 1.0f / (f32)height;
						rightDeltaaXF = (v3->Pos.X - v1->Pos.X) * tmpDiv;
						rightZStep = (s32)((v3->ZValue - v1->ZValue) * tmpDiv);

						tmpDiv = 1.0f / (f32)(v2->Pos.Y - v1->Pos.Y);
						leftDeltaXF = (v2->Pos.X - v1->Pos.X) * tmpDiv;
						leftZStep = (s32)((v2->ZValue - v1->ZValue) * tmpDiv);
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

						}
						while (span < spanEnd)
						{
							leftX = (s32)(leftXF);
							rightX = (s32)(rightXF + 0.5f);
							if (leftX >= _viewPortRect._upperLeftCorner._x &&leftX <= _viewPortRect._lowerRightCorner._x)
							{
								if (leftZValue > * (zTarget + leftX ))
								{
									*(zTarget + leftX) = leftZValue;
									*(targetSurface + leftX) = color;
								}
							}
							if (rightX >= _viewPortRect._upperLeftCorner._x &&rightX <= _viewPortRect._lowerRightCorner._x)
							{
								if (rightZValue > * (zTarget + rightX))
								{
									*(zTarget + rightX) = rightZValue;
									*(targetSurface + rightX) = color;
								}
							}
	
							leftXF += leftDeltaXF;
							rightXF += rightDeltaaXF;
							++span;
							targetSurface += _surfaceWidth;
							zTarget += _surfaceWidth;
							leftZValue += leftZStep;
							rightZValue += rightZStep;

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

						}
						else
						{
							tmpDiv = 1.0f / (v3->Pos.Y - v2->Pos.Y);
							leftDeltaXF = (v3->Pos.X - v2->Pos.X) * tmpDiv;
							leftXF = (f32)v2->Pos.X;
							leftZValue = v2->ZValue;
							leftZStep = (s32)((v3->ZValue - v2->ZValue) * tmpDiv);


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
		IK3DtriangleRenderer* createTriangleRendererFlatWire(IZBuffer* zBuffer)
		{
#ifdef _IRR_COMPILE_WITH_SOFTWARE_
			return new CTRFlatWire(zBuffer);
#else
			return 0;
#endif
		}
	}
}