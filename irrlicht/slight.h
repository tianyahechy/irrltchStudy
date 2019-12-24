#pragma once
#include "color.h"
#include "vector3d.h"

namespace irr
{
	namespace video
	{
		struct SLight
		{
			Colorf _ambientColor;
			Colorf _diffuseColor;
			Colorf _specularColor;
			core::vector3df _position;
			f32 _range;
			f32 _constantAttenuation;
			f32 _linearAttenuation;
			f32 _quadraticAttenuation;
			SLight()
			{
				_ambientColor = Colorf(0.0f, 0.0f, 0.0f);
				_diffuseColor = Colorf(1.0f, 1.0f, 1.0f);
				_specularColor = Colorf(0.0f, 0.0f, 0.0f);
				_position = core::vector3df(0.0f, 0.0f, 0.0f);
				_range = 100.0f;
				_constantAttenuation = 1.0f;
				_linearAttenuation = 0.0f;
				_quadraticAttenuation = 0.0f;
			}
		};
	}
}