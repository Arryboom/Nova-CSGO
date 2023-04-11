#pragma once
#include "Vector.h"

class Matrix3x4 {
public:
	float mat[3][4];

	constexpr auto operator[](int i) const noexcept { return mat[i]; }

	constexpr auto origin() const noexcept {
		return Vector{ mat[0][3], mat[1][3], mat[2][3] };
	}
};

constexpr auto transform(const Vector& v, const Matrix3x4& mat) noexcept {
	return Vector{ v.dotProduct({ mat[0][0], mat[0][1], mat[0][2] }) + mat[0][3],
				   v.dotProduct({ mat[1][0], mat[1][1], mat[1][2] }) + mat[1][3],
				   v.dotProduct({ mat[2][0], mat[2][1], mat[2][2] }) + mat[2][3]
	};
}

struct Matrix4x4 {
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};

		float m[4][4];
	};
};