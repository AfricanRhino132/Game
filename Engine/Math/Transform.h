#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"
#include "MathUtils.h"
#include "Matrix3x3.h"
#include "Serialization/Serializable.h"

namespace neu
{
	struct Transform : public ISerializable
	{
		Vector2 position;
		Vector2 scale{1, 1};
		float rotation{ 0 };

		Matrix3x3 matrix;

		Transform() = default;
		Transform(const Vector2& position, float rotation, const Vector2& scale) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

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