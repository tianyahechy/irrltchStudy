#pragma once
#include "color.h"
#include "ITexture.h"

namespace irr
{
	namespace video
	{
		const s32 MATERIAL_MAX_TEXTURES = 2;
		enum E_MATERIAL_TYPE
		{
			EMT_SOLID	= 0,
			EMT_TRANSPARENT_ADD_COLOR,
			EMT_TRANSPARENT_ALPHA_CHANNEL,
			EMT_LIGHTMAP,
			EMT_FORCE_32BIT	= 0x7fffffff

		};
		enum E_MATERIAL_FLAG
		{
			EMF_WIREFRAME = 0,
			EMT_GOURAUD_SHADING,
			EMF_LIGHTING,
			EMF_ZBUFFER,
			EMF_ZWRITE_ENABLE,
			EMF_BACK_FACE_CULLING,
			EMF_BILINEAR_FILTER,
			EMF_MATERIAL_FLAG_COUNT
		};

		struct SMaterial
		{
			E_MATERIAL_TYPE _materialType;
			Color _ambientColor;
			Color _diffuseColor;
			Color _emissiveColor;
			Color _specularColor;
			f32 _Shininess;
			union 
			{
				ITexture* Textures[MATERIAL_MAX_TEXTURES];
				struct
				{
					ITexture*	_texture1;
					ITexture*	_texture2;
				};
			};

			union 
			{
				struct 
				{
					bool _wireFrame;
					bool _gouraudShading;
					bool _lighting;
					bool _zbuffer;
					bool _zwriteEnable;
					bool _backfaceCulling;
					bool _bilinearFilter;
				};
				bool _flags[EMF_MATERIAL_FLAG_COUNT];
			};

			inline bool isTransparent()
			{
				return _materialType == EMT_TRANSPARENT_ADD_COLOR || _materialType == EMT_TRANSPARENT_ALPHA_CHANNEL;
			}
			SMaterial()
			{
				_ambientColor = Color(255, 255, 255, 255);
				_diffuseColor = Color(255, 255, 255, 255);
				_emissiveColor = Color(0, 0, 0, 0);
				_specularColor = Color(0, 0, 0, 0);
				_texture1 = 0;
				_texture2 = 0;
				_materialType = EMT_SOLID;
				_wireFrame = false;
				_lighting = true;
				_zbuffer = true;
				_zwriteEnable = true;
				_backfaceCulling = true;
				_gouraudShading = true;
				_Shininess = 0.0f;
				_bilinearFilter = true;
			}
				
		};

	}
}