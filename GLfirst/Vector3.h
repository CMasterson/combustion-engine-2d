#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
private:

	public:
	
	float X;
	float Y;
	float Z;

	Vector3();
	Vector3(float x, float y, float z);
	~Vector3(void);


	inline Vector3 operator - ( Vector3 & v )
	{
		float newX = X - v.X;
		float newY = Y - v.Y;
		float newZ = Z - v.Z;

		return Vector3(newX, newY, newZ);
	}
	inline Vector3 operator + ( Vector3 & v )
	{
		float newX = X + v.X;
		float newY = Y + v.Y;
		float newZ = Z + v.Z;

		return Vector3(newX, newY, newZ);
	}
	// returns the length of the vector
	float Length();
	// make unit length
	void Normalise();
	float Distance(Vector3 destination);
	static float Distance(Vector3 source, Vector3 destination);
};

#endif
