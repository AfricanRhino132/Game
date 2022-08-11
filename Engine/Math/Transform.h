#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"
#include "MathUtils.h"
#include "Matrix3x3.h"

namespace neu
{
	struct Transform
	{
		Vector2 position;
		float rotation{ 0 };
		Vector2 scale{1, 1};

		Matrix3x3 matrix;

		void Update()
		{
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRotate = Matrix3x3::CreateRotation(math::DegToRad(rotation));
			Matrix3x3 mxTranslate = Matrix3x3::CreateTranslation(position);

			matrix = { mxTranslate * mxRotate * mxScale };
		}

		void Update(const Matrix3x3& parent)
		{
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRotate = Matrix3x3::CreateRotation(math::DegToRad(rotation));
			Matrix3x3 mxTranslate = Matrix3x3::CreateTranslation(position);

			matrix = { mxTranslate * mxRotate * mxScale };

			matrix = parent * matrix;
		}

		/*operator Matrix2x2 () const
		{
			Matrix2x2 mxScale = Matrix2x2::CreateScale(scale);
			Matrix2x2 mxRotate = Matrix2x2::CreateRotation(math::DegToRad(rotation));
			
			return { mxScale * mxRotate };
		}*/

		operator Matrix3x3 () const
		{
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRotate = Matrix3x3::CreateRotation(math::DegToRad(rotation));
			Matrix3x3 mxTranslate = Matrix3x3::CreateTranslation(position);

			return { mxTranslate * mxRotate * mxScale };
		}
	};
}