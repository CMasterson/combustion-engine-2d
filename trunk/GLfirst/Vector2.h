#ifndef VECTOR2_H
#define VECTOR2_H


class Vector2
{
	private:

	public:
	
	float X;
	float Y;

	Vector2();
	Vector2(float x, float y);
	~Vector2(void);


	inline Vector2 operator - ( Vector2 & v )
	{
		float newX = X - v.X;
		float newY = Y - v.Y;

		return Vector2(newX, newY);
	}
	inline Vector2 operator + ( Vector2 & v )
	{
		float newX = X + v.X;
		float newY = Y + v.Y;

		return Vector2(newX, newY);
	}
	inline Vector2 operator * (float value)
	{
		float newX = X * value;
		float newY = Y * value;

		return Vector2 (newX, newY);
	}
	inline Vector2 operator * (Vector2 value)
	{
		return Vector2 (X * value.X, Y * value.Y);
	}
	inline Vector2 operator / (float  value)
	{
		float newX = X / value;
		float newY = Y / value;

		return Vector2 (newX, newY);
	}
	inline Vector2 operator / (Vector2 value)
	{
		return Vector2(X / value.X, Y / value.Y);
	}
	inline bool operator == (Vector2 & value)
	{
		return ((X == value.X) && (Y == value.Y));
	}
	inline bool operator != (Vector2 & value)
	{
		return !(*this == value);
	}
	inline bool isEmpty()
	{
		return !X && !Y;
	}
	

	// returns the length of the vector
	float Length();
	// make unit length
	void Normalise();
	float Distance(Vector2 destination);
	static float Distance(Vector2 source, Vector2 destination);
	Vector2 Rotate(float byRadians);
	Vector2 Rotate(Vector2 aboutPoint, float byRadians);

	float AngleRad();//Returns angle in radians
	float AngleDeg();//Returns angle in degrees
};

#endif