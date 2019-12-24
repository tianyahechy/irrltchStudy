#pragma once
#include "IUnknown.h"
#include "ISceneNodeAnimator.h"
#include "SMaterial.h"
#include "irrstring.h"
#include "aabbox3d.h"
#include "matrix4.h"
#include "list.h"


namespace irr
{
	namespace scene
	{
		class ISceneManager;
		class ISceneNode : public IUnkown
		{
		public:
			core::matrix4& getAbsoluteTransformation()
			{
				return _absoluteTransformation;
			}
		protected:
			irr::core::string		_name;
			core::matrix4			_absoluteTransformation;
			core::matrix4			_relativeTransformation;
			core::matrix4			_animatedRelativeTransformation;
			ISceneNode*				_parent;
			core::list<ISceneNode*>	_children;
			core::list<ISceneNodeAnimator*>	_animator;
			bool					_isVisible;
			s32						_id;
			ISceneManager*			_sceneManager;

			void updateAbsolutePosition()
			{
				if (_parent)
				{
					_absoluteTransformation = _parent->getAbsoluteTransformation() * _animatedRelativeTransformation;
				}
				else
				{
					_absoluteTransformation = _animatedRelativeTransformation;
				}
			}
		public:
			virtual void addChild(ISceneNode* child)
			{
				if (child)
				{
					_children.push_back(child);
					child->grab();
				}
			}
			ISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id = -1,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& rotation = core::vector3df(0, 0, 0),
				const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f))
			{
				_isVisible = true;
				_id = id;
				_parent = parent;
				_sceneManager = mgr;

				if (_parent)
				{
					_parent->addChild(this);
				}
				_relativeTransformation.setRotationDegrees(rotation);
				_relativeTransformation.setTranslation(position);

				core::matrix4 mat;
				mat.setScale(scale);
				_relativeTransformation *= mat;

				_animatedRelativeTransformation = _relativeTransformation;
				updateAbsolutePosition();
			}
			virtual ~ISceneNode()
			{
				core::list<ISceneNode*>::Iterator it = _children.begin();
				for (; it != _children.end(); it++)
				{
					(*it)->drop();
				}

				core::list<ISceneNodeAnimator*>::Iterator ait = _animator.begin();
				for (; ait !=_animator.end(); ait++)
				{
					(*ait)->drop();
				}
			}
			virtual void OnPreRender()
			{
				if (_isVisible)
				{
					core::list<ISceneNode*>::Iterator it = _children.begin();
					for (; it != _children.end(); it++)
					{
						(*it)->OnPreRender();
					}
				}
			}
			virtual void OnPostRender(u32 timeMs)
			{
				_animatedRelativeTransformation = _relativeTransformation;
				if (!_isVisible)
				{
					return;
				}
				core::list<ISceneNodeAnimator*>::Iterator ait = _animator.begin();
				for (; ait != _animator.end(); ait++)
				{
					(*ait)->animateNode(this, timeMs);
				}
				updateAbsolutePosition();
				core::list<ISceneNode*>::Iterator it = _children.begin();
				for (; it != _children.end(); it++)
				{
					(*it)->OnPostRender(timeMs);
				}
			}
			virtual void render() = 0;
			virtual const wchar_t * getName() const
			{
				return _name.c_str();
			}
			virtual void setName(const wchar_t * name)
			{
				_name = name;
			}
			virtual const core::aabbox3d<f32>& getBoundingBox() const = 0;
			core::matrix4& getAbsoluteTransformation()
			{
				return _absoluteTransformation;
			}
			core::matrix4& getRelativeTransformation()
			{
				return _relativeTransformation;
			}
			core::matrix4& getAnimatedRelativeTransformation()
			{
				return _animatedRelativeTransformation;
			}
			virtual bool isVisible()
			{
				return _isVisible;
			}
			virtual void setVisible(bool isVisible)
			{
				_isVisible = isVisible;
			}
			virtual s32 getID()
			{
				return _id;
			}
			virtual void setID(s32 id)
			{
				_id = id;
			}
			virtual void addChild(ISceneNode* child)
			{
				if (child)
				{
					_children.push_back(child);
					_child->grab();
				}
			}
			virtual void removeChild(ISceneNode* child)
			{
				core::list<ISceneNode*>::Iterator it = _children.begin();
				for (; it != _children.end(); it++)
				{
					if ((*it) == child)
					{
						(*it)->drop();
						_children.erase(it);
						return;
					}
				}
			}
			virtual void remove()
			{
				if (_parent)
				{
					_parent->removeChild(this);
				}
			}
			virtual void addAnimator(ISceneNodeAnimator* animator)
			{
				if (animator)
				{
					_animator.push_back(animator);
					animator->grab();
				}
			}
			virtual void removeAnimator(ISceneNodeAnimator* animator)
			{
				core::list<ISceneNodeAnimator*>::Iterator it = _animator.begin();
				for (; it != _animator.end(); it++)
				{
					if ((*it) == animator)
					{
						(*it)->drop();
						_animator.erase(it);
						return;
					}
				}
			}
			virtual void removeAnimators()
			{
				core::list<ISceneNodeAnimator*>::Iterator it = _animator.begin();
				for (; it != _animator.end(); it++)
				{
					(*it)->drop();
				}
				_animator.clear();
			}
			virtual video::SMaterial& getMaterial(s32 i)
			{
				return *((video::SMaterial*)i);
			}
			virtual s32 getMaterialCount()
			{
				return 0;
			}
			void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newValue)
			{
				for (s32 i = 0; i < getMaterialCount(); i++)
				{
					getMaterial(i)._flags[flag] = newValue;
				}
			}
			void setMaterialTexture(s32 textureLayer, video::ITexture* texture)
			{
				if (textureLayer < 0 || textureLayer >= video::MATERIAL_MAX_TEXTURES)
				{
					return;
				}
				for (s32 i = 0; i < getMaterialCount(); i++)
				{
					getMaterial(i).Textures[textureLayer] = texture;
				}
			}
			void setMaterialType(video::E_MATERIAL_TYPE newType)
			{
				for (s32 i = 0; i < getMaterialCount(); i++)
				{
					getMaterial(i)._materialType = newType;
				}
			}
			virtual void setRelativePosition(const core::vector3df& position)
			{
				_relativeTransformation.setTranslation(position);
			}
			virtual void setScale(const core::vector3df& scale)
			{
				_relativeTransformation.setScale(scale);
			}
			virtual core::vector3df getRelativePosition() const
			{
				core::vector3df pos(0.0f, 0.0f, 0.0f);
				_relativeTransformation.transformVect(pos);
				return pos;
			}
			virtual core::vector3df getAbsolutePosition() const
			{
				core::vector3df pos(0.0f, 0.0f, 0.0f);
				_absoluteTransformation.transformVect(pos);
				return pos;
			}
		};
	}
}