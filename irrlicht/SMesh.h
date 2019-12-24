#pragma once
#include "IMesh.h"
#include "ImeshBuffer.h"

namespace irr
{
	namespace scene
	{
		struct SMesh : public IMesh
		{
			core::array<IMeshBuffer*> _meshBuffers;
			core::aabbox3d<f32> _boundingBox;
			SMesh()
			{
				setDebugName("SMesh");
			}
			~SMesh()
			{
				for (u32 i = 0; i < _meshBuffers.size(); i++)
				{
					_meshBuffers[i]->drop();
				}
			}

			virtual s32 getMeshBufferCount()
			{
				return _meshBuffers.size();
			}

			virtual IMeshBuffer* getMeshBuffer(s32 nr)
			{
				return _meshBuffers[nr];
			}
			virtual const core::aabbox3d<f32>& getBoundingBox() const
			{
				return _boundingBox;
			}
			void recalculateBoundingBox()
			{
				if (_meshBuffers.size())
				{
					_boundingBox = _meshBuffers[0]->getBoundingBox();
					for (u32 i = 0; i < _meshBuffers.size(); i++)
					{
						_boundingBox.addInternalBox(_meshBuffers[i]->getBoundingBox());
					}
				}
				else
				{
					_boundingBox.reset(0.0f, 0.0f, 0.0f);
				}
			}

			virtual void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newValue)
			{
				for (u32 i = 0; i < _meshBuffers.size(); i++)
				{
					_meshBuffers[i]->getMaterial()._flags[flag] = newValue;
				}
			}
		};
	}
}