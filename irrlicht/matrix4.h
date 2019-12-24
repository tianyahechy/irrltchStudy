
//ÒÑÍê³É
#pragma once
#include "irrtypes.h"
#include "vector3d.h"
namespace irr
{
	namespace core
	{
		class matrix4
		{
		private:
			f32 _m[16];
		public:
			matrix4();
			void makeIdentity();
			f32& operator() (s32 row, s32 col) { return _m[col * 4 + row]; }
			const f32& operator()  (s32 row, s32 col) const { return _m[col * 4 + row]; }
			matrix4& operator= (const matrix4& other);
			bool operator== (const matrix4& other) const;
			bool operator!= (const matrix4& other) const;
			matrix4& operator*= (const matrix4& other);
			matrix4 operator* (const matrix4& other) const;
			void setTranslation(const vector3df& translation);
			vector3df getTranslation() const;
			void setTranslation(const vector3df& translation);
			void setInverseTranslation(const vector3df& translation);
			void setScale(const vector3df& scale);
			void setRotationDegrees(const vector3df& rotation);
			void setRotationRadians(const vector3df& rotation);
			void setInverseRotationRadians(const vector3df& rotation);
			void makeIdentity();
			void inverseRotateVect(vector3df& vect) const;
			void transformVect(vector3df& vect) const;
			void transformVect(const vector3df& in, vector3df& out);
			void multiplyWith1x4Matrix(f32* matrix) const;
			void inverseTranslateVect(vector3df& vect) const;
			void translateVect(vector3df& vect) const;
			bool makeInverse();
			void buildProjectionMatrixPerspectiveFovRH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar);
			void buildProjectionMatrixPerspectiveFovLH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar);
			void buildProjectionMatrixOrthoLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);
			void buildProjectionMatrixOrthoRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);
			void buildProjectionMatrixPerspectiveRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);
			void buildProjectionMatrixPerspectiveLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);
			void buildCameraLookAtMatrixLH(const vector3df& position, const vector3df& target, const vector3df& upVector);
			void buildCameraLookAtMatrixRH(const vector3df& position, const vector3df& target, const vector3df& upVector);
		};

		inline void matrix4::makeIdentity()
		{
			for (s32 i = 0; i < 16; i++)
			{
				_m[i] = 0.0f;
			}
			_m[0] = _m[5] = _m[10] = _m[15] = 1;
		}
		inline matrix4::matrix4()
		{
			makeIdentity();
		}
		inline matrix4& matrix4::operator=(const matrix4& other)
		{
			for (s32 i = 0; i < 16; i++)
			{
				_m[i] = other._m[i];
			}
			return *this;
		}
		inline bool matrix4::operator== (const matrix4& other) const
		{
			for (s32 i = 0; i < 16; i++)
			{
				if (_m[i] != other._m[i])
				{
					return false;
				}
			}
			return true;
		}
		inline bool matrix4::operator!= (const matrix4& other) const
		{
			return !(*this == other);
		}
		inline matrix4& matrix4::operator*= (const matrix4& other)
		{
			f32 newMatrix[16];
			const f32* m1 = _m;
			const f32* m2 = other._m;
			newMatrix[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
			newMatrix[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
			newMatrix[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
			newMatrix[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

			newMatrix[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
			newMatrix[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
			newMatrix[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
			newMatrix[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

			newMatrix[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
			newMatrix[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
			newMatrix[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
			newMatrix[11] = m1[3] * m2[8] + m1[7] * m2[10] + m1[11] * m2[10] + m1[15] * m2[11];

			newMatrix[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
			newMatrix[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
			newMatrix[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
			newMatrix[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

			for (s32 i = 0; i < 16; i++)
			{
				_m[i] = newMatrix[i];
			}
			return *this;
		}
		inline matrix4 matrix4::operator* (const matrix4& other) const
		{
			matrix4 newMatrix;
			const f32* m1 = _m;
			const f32* m2 = other._m;
			float * m3 = newMatrix._m;
			m3[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
			m3[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
			m3[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
			m3[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

			m3[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
			m3[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
			m3[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
			m3[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

			m3[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
			m3[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
			m3[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
			m3[11] = m1[3] * m2[8] + m1[7] * m2[10] + m1[11] * m2[10] + m1[15] * m2[11];
			
			m3[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
			m3[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
			m3[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
			m3[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

			return newMatrix;
		}
		inline void matrix4::setTranslation(const vector3df& translation)
		{
			_m[12] = translation.X;
			_m[13] = translation.Y;
			_m[14] = translation.Z;
 		}
		inline vector3df matrix4::getTranslation() const
		{
			return vector3df(_m[12], _m[13], _m[14]);
		}
		inline void matrix4::setTranslation(const vector3df& translation)
		{
			_m[12] = translation.X;
			_m[13] = translation.Y;
			_m[14] = translation.Z;
		}
		inline void matrix4::setInverseTranslation(const vector3df& translation)
		{
			_m[12] = -translation.X;
			_m[13] = -translation.Y;
			_m[14] = -translation.Z;
		}
		inline void matrix4::setScale(const vector3df& scale)
		{
			_m[0] = scale.X;
			_m[5] = scale.Y;
			_m[10] = scale.Z;
		}

		void matrix4::setRotationRadians(const vector3df& rotation)
		{
			f64 cr = cos(rotation.X);
			f64	sr = sin(rotation.X);
			f64 cp = cos(rotation.Y);
			f64 sp = sin(rotation.Y);
			f64 cy = cos(rotation.Z);
			f64 sy = sin(rotation.Z);

			_m[0] = (f32)(cp * cy);
			_m[1] = (f32)(cp * sy);
			_m[2] = (f32)(-sp);

			f64 srsp = sr* sp;
			f64 crsp = cr * sp;
			
			_m[4] = (f32)(srsp *cy - cr * sy);
			_m[5] = (f32)(srsp * sy + cr * cy);
			_m[6] = (f32)(sr * cp);

			_m[8] = (f32)(crsp * cy + sr * sy);
			_m[9] = (f32)(crsp * sy - sr * cy);
			_m[10] = (f32)(cr * cp);
		}

		inline void matrix4::setRotationDegrees(const vector3df& rotation)
		{
			setRotationRadians(rotation * (f32) 3.1415926 / 180.0);
		}
		void matrix4::setInverseRotationRadians(const vector3df& rotation)
		{
			f64 cr = cos(rotation.X);
			f64	sr = sin(rotation.X);
			f64 cp = cos(rotation.Y);
			f64 sp = sin(rotation.Y);
			f64 cy = cos(rotation.Z);
			f64 sy = sin(rotation.Z);

			_m[0] = (f32)(cp * cy);
			_m[4] = (f32)(cp * sy);
			_m[8] = (f32)(-sp);

			f64 srsp = sr* sp;
			f64 crsp = cr * sp;

			_m[1] = (f32)(srsp *cy - cr * sy);
			_m[5] = (f32)(srsp * sy + cr * cy);
			_m[9] = (f32)(sr * cp);

			_m[2] = (f32)(crsp * cy + sr * sy);
			_m[6] = (f32)(crsp * sy - sr * cy);
			_m[10] = (f32)(cr * cp);
		}
		
		inline void matrix4::makeIdentity()
		{
			for ( s32 i = 0; i < 16; i++)
			{
				_m[i] = 0.0f;
			}
			_m[0] = _m[5] = _m[10] = _m[15] = 1;
		}
		inline void matrix4::inverseRotateVect(vector3df& vect) const
		{
			vect.X = vect.X * _m[0] + vect.Y * _m[1] + vect.Z * _m[2];
			vect.Y = vect.X * _m[4] + vect.Y * _m[5] + vect.Z * _m[6];
			vect.Z = vect.X * _m[8] + vect.Y * _m[9] + vect.Z * _m[10];
		}

		inline void matrix4::transformVect(vector3df& vect) const
		{
			f32 vector[3];
			vector[0] = vect.X * _m[0] + vect.Y * _m[4] + vect.Z * _m[8] + _m[12];
			vector[1] = vect.X * _m[1] + vect.Y * _m[5] + vect.Z * _m[9] + _m[13];
			vector[2] = vect.X * _m[2] + vect.Y * _m[6] + vect.Z * _m[10] + _m[14];
			vect.X = vector[0];
			vect.Y = vector[1];
			vect.Z = vector[2];
		}
		inline void matrix4::transformVect(const vector3df& in, vector3df& out) 
		{		
			out.X = in.X * _m[0] + in.Y * _m[4] + in.Z * _m[8] + _m[12];
			out.Y = in.X * _m[1] + in.Y * _m[5] + in.Z * _m[9] + _m[13];
			out.Z = in.X * _m[2] + in.Y * _m[6] + in.Z * _m[10] + _m[14];
			
		}

		inline void matrix4::multiplyWith1x4Matrix(f32* matrix) const
		{
			f32 mat[4];
			mat[0] = matrix[0];
			mat[1] = matrix[1];
			mat[2] = matrix[2];
			mat[3] = matrix[3];

			matrix[0] = _m[0] * mat[0] + _m[4] * mat[1] + _m[8] * mat[2] + _m[12] * mat[3];
			matrix[1] = _m[1] * mat[0] + _m[5] * mat[1] + _m[9] * mat[2] + _m[13] * mat[3];
			matrix[2] = _m[2] * mat[0] + _m[6] * mat[1] + _m[10] * mat[2] + _m[14] * mat[3];
			matrix[3] = _m[3] * mat[0] + _m[7] * mat[1] + _m[11] * mat[2] + _m[15] * mat[3];

		}
		inline void matrix4::inverseTranslateVect(vector3df& vect) const
		{
			vect.X = vect.X - _m[12];
			vect.Y = vect.Y - _m[13];
			vect.Z = vect.Z - _m[14];
		}
		inline void matrix4::translateVect(vector3df& vect) const
		{
			vect.X = vect.X + _m[12];
			vect.Y = vect.Y + _m[13];
			vect.Z = vect.Z + _m[14];
		}
		inline bool matrix4::makeInverse()
		{
			const matrix4& m = *this;

			f32 d = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * (m(2, 2) * m(3, 3) - m(3, 2) * m(2, 3)) - (m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1)) * (m(1, 2) * m(3, 3) - m(3, 2) * m(1, 3))
				+ (m(0, 0) * m(3, 1) - m(3, 0) * m(0, 1)) * (m(1, 2) * m(2, 3) - m(2, 2) * m(1, 3)) + (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * (m(0, 2) * m(3, 3) - m(3, 2) * m(0, 3))
				- (m(1, 0) * m(3, 1) - m(3, 0) * m(1, 1)) * (m(0, 2) * m(2, 3) - m(2, 2) * m(0, 3)) + (m(2, 0) * m(3, 1) - m(3, 0) * m(2, 1)) * (m(0, 2) * m(1, 3) - m(1, 2) * m(0, 3));
			
			if ( 0 == d)
			{
				return false;
			}
			else
			{
				d = 1.0f / d;
				matrix4 temp;
				temp(0, 0) = d * (m(1, 1) * (m(2, 2) * m(3, 3) - m(3, 2) * m(2, 3)) + m(2, 1) * (m(3, 2) * m(1, 3) - m(1, 2) * m(3, 3)) + m(3, 1) * (m(1, 2) * m(2, 3) - m(2, 2) * m(1, 3)));
				temp(1, 0) = d * (m(1, 2) * (m(2, 0) * m(3, 3) - m(3, 0) * m(2, 3)) + m(2, 2) * (m(3, 0) * m(1, 3) - m(1, 0) * m(3, 3)) + m(3, 2) * (m(1, 0) * m(2, 3) - m(2, 0) * m(1, 3)));
				temp(2, 0) = d * (m(1, 3) * (m(2, 0) * m(3, 1) - m(3, 0) * m(2, 1)) + m(2, 3) * (m(3, 0) * m(1, 1) - m(1, 0) * m(3, 1)) + m(3, 3) * (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)));
				temp(3, 0) = d * (m(1, 0) * (m(3, 1) * m(2, 2) - m(2, 1) * m(3, 2)) + m(2, 0) * (m(1, 1) * m(3, 2) - m(3, 1) * m(1, 2)) + m(3, 0) * (m(2, 1) * m(1, 2) - m(1, 1) * m(2, 2)));
				temp(0, 1) = d * (m(2, 1) * (m(0, 2) * m(3, 3) - m(3, 2) * m(0, 3)) + m(3, 1) * (m(2, 2) * m(0, 3) - m(0, 2) * m(2, 3)) + m(0, 1) * (m(3, 2) * m(2, 3) - m(2, 2) * m(3, 3)));
				temp(1, 1) = d * (m(2, 2) * (m(0, 0) * m(3, 3) - m(3, 0) * m(0, 3)) + m(3, 2) * (m(2, 0) * m(0, 3) - m(0, 0) * m(2, 3)) + m(0, 2) * (m(3, 0) * m(2, 3) - m(2, 0) * m(3, 3)));
				temp(2, 1) = d * (m(2, 3) * (m(0, 0) * m(3, 1) - m(3, 0) * m(0, 1)) + m(3, 3) * (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) + m(0, 3) * (m(3, 0) * m(2, 1) - m(2, 0) * m(3, 1)));
				temp(3, 1) = d * (m(2, 0) * (m(3, 1) * m(0, 2) - m(0, 1) * m(3, 2)) + m(3, 0) * (m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2)) + m(0, 0) * (m(2, 1) * m(3, 2) - m(3, 1) * m(2, 2)));
				temp(0, 2) = d * (m(3, 1) * (m(0, 2) * m(1, 3) - m(1, 2) * m(0, 3)) + m(0, 1) * (m(1, 2) * m(3, 3) - m(3, 2) * m(1, 3)) + m(1, 1) * (m(3, 2) * m(0, 3) - m(0, 2) * m(3, 3)));
				temp(1, 2) = d * (m(3, 2) * (m(0, 0) * m(1, 3) - m(1, 0) * m(0, 3)) + m(0, 2) * (m(1, 0) * m(3, 3) - m(3, 0) * m(1, 3)) + m(1, 2) * (m(3, 0) * m(0, 3) - m(0, 0) * m(3, 3)));
				temp(2, 2) = d * (m(3, 3) * (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) + m(0, 3) * (m(1, 0) * m(3, 1) - m(3, 0) * m(1, 1)) + m(1, 3) * (m(3, 0) * m(0, 1) - m(0, 0) * m(3, 1)));
				temp(3, 2) = d * (m(3, 0) * (m(1, 1) * m(0, 2) - m(0, 1) * m(1, 2)) + m(0, 0) * (m(3, 1) * m(1, 2) - m(1, 1) * m(3, 2)) + m(1, 0) * (m(0, 1) * m(3, 2) - m(3, 1) * m(0, 2)));
				temp(0, 3) = d * (m(0, 1) * (m(2, 2) * m(1, 3) - m(1, 2) * m(2, 3)) + m(1, 1) * (m(0, 2) * m(2, 3) - m(2, 2) * m(0, 3)) + m(2, 1) * (m(1, 2) * m(0, 3) - m(0, 2) * m(1, 3)));
				temp(1, 3) = d * (m(0, 2) * (m(2, 0) * m(1, 3) - m(1, 0) * m(2, 3)) + m(1, 2) * (m(0, 0) * m(2, 3) - m(2, 0) * m(0, 3)) + m(2, 2) * (m(1, 0) * m(0, 3) - m(0, 0) * m(1, 3)));
				temp(2, 3) = d * (m(0, 3) * (m(2, 0) * m(1, 1) - m(1, 0) * m(2, 1)) + m(1, 3) * (m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1)) + m(2, 3) * (m(1, 0) * m(0, 1) - m(0, 0) * m(1, 1)));
				temp(3, 3) = d * (m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) + m(1, 0) * (m(2, 1) * m(0, 2) - m(0, 1) * m(2, 2)) + m(2, 0) * (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2)));
				*this = temp;
				return true;
			}
		}
		inline matrix4& matrix4::operator= (const matrix4& other)
		{
			for (s32 i = 0; i < 16; i++)
			{
				_m[i] = other._m[i];
			}
			return *this;
		}
		inline void matrix4::buildProjectionMatrixPerspectiveFovRH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
		{
			f32 h = (f32)(cos(fieldOfViewRadians / 2) / sin(fieldOfViewRadians / 2));
			f32 w = h / aspectRatio;

			(*this)(0, 0) = 2 * zNear / w;
			(*this)(1, 0) = 0;
			(*this)(2, 0) = 0;
			(*this)(3, 0) = 0;

			(*this)(0, 1) = 0;
			(*this)(1, 1) = 2 * zNear / h;
			(*this)(2, 1) = 0;
			(*this)(3, 1) = 0;

			(*this)(0, 2) = 0;
			(*this)(1, 2) = 0;
			(*this)(2, 2) = zFar / (zFar - zNear);
			(*this)(3, 2) = -1;

			(*this)(0, 3) = 0;
			(*this)(1, 3) = 0;
			(*this)(2, 3) = zNear * zFar / ( zNear - zFar );
			(*this)(3, 3) = 0;

		}

		inline void matrix4::buildProjectionMatrixPerspectiveFovLH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
		{
			f32 h = (f32)(cos(fieldOfViewRadians / 2) / sin(fieldOfViewRadians / 2));
			f32 w = h / aspectRatio;

			(*this)(0, 0) = 2 * zNear / w;
			(*this)(1, 0) = 0;
			(*this)(2, 0) = 0;
			(*this)(3, 0) = 0;

			(*this)(0, 1) = 0;
			(*this)(1, 1) = 2 * zNear / h;
			(*this)(2, 1) = 0;
			(*this)(3, 1) = 0;

			(*this)(0, 2) = 0;
			(*this)(1, 2) = 0;
			(*this)(2, 2) = zFar / (zFar - zNear);
			(*this)(3, 2) = 1;

			(*this)(0, 3) = 0;
			(*this)(1, 3) = 0;
			(*this)(2, 3) = zNear * zFar / (zNear - zFar);
			(*this)(3, 3) = 0;

		}

		inline void matrix4::buildProjectionMatrixOrthoLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			(*this)(0, 0) = 2 / widthOfViewVolume;
			(*this)(1, 0) = 0;
			(*this)(2, 0) = 0;
			(*this)(3, 0) = 0;

			(*this)(0, 1) = 0;
			(*this)(1, 1) = 2 / heightOfViewVolume;
			(*this)(2, 1) = 0;
			(*this)(3, 1) = 0;

			(*this)(0, 2) = 0;
			(*this)(1, 2) = 0;
			(*this)(2, 2) = 1 / (zNear - zFar);
			(*this)(3, 2) = 0;

			(*this)(0, 3) = 0;
			(*this)(1, 3) = 0;
			(*this)(2, 3) = zNear / (zNear - zFar);
			(*this)(3, 3) = 1;
		}
		inline void matrix4::buildProjectionMatrixOrthoRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			(*this)(0, 0) = 2 / widthOfViewVolume;
			(*this)(1, 0) = 0;
			(*this)(2, 0) = 0;
			(*this)(3, 0) = 0;

			(*this)(0, 1) = 0;
			(*this)(1, 1) = 2 / heightOfViewVolume;
			(*this)(2, 1) = 0;
			(*this)(3, 1) = 0;

			(*this)(0, 2) = 0;
			(*this)(1, 2) = 0;
			(*this)(2, 2) = 1 / (zNear - zFar);
			(*this)(3, 2) = 0;

			(*this)(0, 3) = 0;
			(*this)(1, 3) = 0;
			(*this)(2, 3) = zNear / (zNear - zFar);
			(*this)(3, 3) = -1;
		}

		inline void matrix4::buildProjectionMatrixPerspectiveRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			(*this)(0, 0) = 2 * zNear / widthOfViewVolume;
			(*this)(1, 0) = 0;
			(*this)(2, 0) = 0;
			(*this)(3, 0) = 0;

			(*this)(0, 1) = 0;
			(*this)(1, 1) = 2 * zNear/ heightOfViewVolume;
			(*this)(2, 1) = 0;
			(*this)(3, 1) = 0;

			(*this)(0, 2) = 0;
			(*this)(1, 2) = 0;
			(*this)(2, 2) = zFar / (zNear - zFar);
			(*this)(3, 2) = -1;

			(*this)(0, 3) = 0;
			(*this)(1, 3) = 0;
			(*this)(2, 3) = zNear * zFar/ (zNear - zFar);
			(*this)(3, 3) = 0;
		}

		inline void matrix4::buildProjectionMatrixPerspectiveLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			(*this)(0, 0) = 2 * zNear / widthOfViewVolume;
			(*this)(1, 0) = 0;
			(*this)(2, 0) = 0;
			(*this)(3, 0) = 0;

			(*this)(0, 1) = 0;
			(*this)(1, 1) = 2 * zNear / heightOfViewVolume;
			(*this)(2, 1) = 0;
			(*this)(3, 1) = 0;

			(*this)(0, 2) = 0;
			(*this)(1, 2) = 0;
			(*this)(2, 2) = zFar / (zFar - zNear);
			(*this)(3, 2) = 1;

			(*this)(0, 3) = 0;
			(*this)(1, 3) = 0;
			(*this)(2, 3) = zNear * zFar / (zNear - zFar);
			(*this)(3, 3) = 0;
		}

		void matrix4::buildCameraLookAtMatrixLH(const vector3df& position, const vector3df& target, const vector3df& upVector)
		{
			vector3df zAxis = target - position;
			zAxis.normalize();
			vector3df xAxis = upVector.crossProduct(zAxis);
			xAxis.normalize();
			vector3df yAxis = zAxis.crossProduct(xAxis);

			(*this) (0, 0) = xAxis.X;
			(*this) (1, 0) = yAxis.X;
			(*this) (2, 0) = zAxis.X;
			(*this) (3, 0) = 0;

			(*this) (0, 1) = xAxis.Y;
			(*this) (1, 1) = yAxis.Y;
			(*this) (2, 1) = zAxis.Y;
			(*this) (3, 1) = 0;

			(*this) (0, 2) = xAxis.Z;
			(*this) (1, 2) = yAxis.Z;
			(*this) (2, 2) = zAxis.Z;
			(*this) (3, 2) = 0;

			(*this) (0, 3) = -xAxis.dotProduct(position);
			(*this) (1, 3) = -yAxis.dotProduct(position);
			(*this) (2, 3) = -zAxis.dotProduct(position);
			(*this) (3, 3) = 1.0f;

		}

		void matrix4::buildCameraLookAtMatrixRH(const vector3df& position, const vector3df& target, const vector3df& upVector)
		{
			vector3df zAxis = position - target;
			zAxis.normalize();
			vector3df xAxis = upVector.crossProduct(zAxis);
			xAxis.normalize();
			vector3df yAxis = zAxis.crossProduct(xAxis);

			(*this) (0, 0) = xAxis.X;
			(*this) (1, 0) = yAxis.X;
			(*this) (2, 0) = zAxis.X;
			(*this) (3, 0) = 0;

			(*this) (0, 1) = xAxis.Y;
			(*this) (1, 1) = yAxis.Y;
			(*this) (2, 1) = zAxis.Y;
			(*this) (3, 1) = 0;

			(*this) (0, 2) = xAxis.Z;
			(*this) (1, 2) = yAxis.Z;
			(*this) (2, 2) = zAxis.Z;
			(*this) (3, 2) = 0;

			(*this) (0, 3) = -xAxis.dotProduct(position);
			(*this) (1, 3) = -yAxis.dotProduct(position);
			(*this) (2, 3) = -zAxis.dotProduct(position);
			(*this) (3, 3) = 1.0f;

		}}
}