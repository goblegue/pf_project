#include "raylib.h"

#include <cmath>

/**
 * @brief calculates the distance between two vectors
 * @param a the first vector
 * @param b the second vector
 * @returns the distance between the two vectors
 */
inline double Vector2Distance(const Vector2 &a, const Vector2 &b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

/**
 * @brief gives unit vector in the same direction
 * @param v the vector to normalize
 * @returns the normalized vector
 */
inline Vector2 Vector2Normalize(Vector2 v)
{
    float length = Vector2Distance({0, 0}, v); // Get length from origin
    if (length == 0)
    {
        return {0, 0}; // Avoid division by zero
    }
    return {v.x / length, v.y / length};
}

/**
 * @brief adds two vectors
 * @param v1 the first vector
 * @param v2 the second vector
 * @returns the sum of the two vectors
 */
inline Vector2 Vector2Add(Vector2 v1, Vector2 v2)
{
    return {v1.x + v2.x, v1.y + v2.y};
}

// Subtracts vector v2 from v1 (v1 - v2).
/**
 * @brief subtracts two vectors
 * @param v1 the first vector
 * @param v2 the second vector
 * @returns the difference of the two vectors
 */
inline Vector2 Vector2Subtract(Vector2 v1, Vector2 v2)
{
    return {v1.x - v2.x, v1.y - v2.y};
}

// Multiplies each component of a vector by a single float value (a "scalar").
/**
 * @brief scales a vector
 * @param v the vector to scale
 * @param scale the scale factor
 * @returns the scaled vector
 */
inline Vector2 Vector2Scale(Vector2 v, float scale)
{
    return {v.x * scale, v.y * scale};
}

// Calculates the length (or "magnitude") of a vector.
// This is the distance from the origin (0,0) to the vector's point.
/**
 * @brief calculates the length of a vector
 * @param v the vector
 * @returns the length of the vector
 */
inline float Vector2Length(Vector2 v)
{
    return sqrtf((v.x * v.x) + (v.y * v.y));
}
