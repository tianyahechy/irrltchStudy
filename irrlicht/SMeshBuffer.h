#pragma once
#include "array.h"
#include "ImeshBuffer.h"

namespace irr
{
	namespace scene
	{
		struct SMeshBuffer : public IMeshBuffer
		{
			video::SMaterial _material;
			core::array<video::S3DVertex> _vertices;
			core::array<u16> _indices;
			core::aabbox3d<f32> _boundingBox;
			SMeshBuffer()
			{
				setDebugName("SMeshBuffer");
			}
			~SMeshBuffer() {}
			virtual const video::SMaterial& getMaterial() const
			{
				return _material;
			}

			virtual video::SMaterial& getMaterial()
			{
				return _material;
			}

			virtual const void * getVertices() const
			{
				return _vertices.const_pointer();
			}

			virtual void * getVertices()
			{
				return _vertices.pointer();
			}
			virtual s32 getVertexCount() const
			{
				return _vertices.size();
			}
			virtual const u16* getIndices() const
			{
				return _indices.const_pointer();
			}
			virtual s32 getIndexCount() const
			{
				return _indices.size();
			}
			virtual const core::aabbox3d<f32>& getBoundingBox() const
			{
				return _boundingBox;
			}
			void recalculateBoundingBox()
			{
				if (_vertices.empty())
				{
					_boundingBox.reset(0, 0, 0);
				}
				else
				{
					_boundingBox.reset(_vertices[0]._pos);
					for (u32 i = 1; i < _vertices.size(); i++)
					{
						_boundingBox.addInternalPoint(_vertices[i]._pos);
					}
				}
			}
			virtual video::E_VERTEX_TYPE getVertexType() const
			{
				return video::EVT_STANDARD;
			}
		};
	}
}