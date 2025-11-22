#include "raylib.h"

#include <cmath>

inline double Vector2Distance(const Vector2 &a, const Vector2 &b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

inline Vector2 Vector2Normalize(Vector2 v)
{
    float length = Vector2Distance({0, 0}, v); // Get length from origin
    if (length == 0)
    {
        return {0, 0}; // Avoid division by zero
    }
    return {v.x / length, v.y / length};
}
inline Vector2 Vector2Add(Vector2 v1, Vector2 v2)
{
    return {v1.x + v2.x, v1.y + v2.y};
}

// Subtracts vector v2 from v1 (v1 - v2).
inline Vector2 Vector2Subtract(Vector2 v1, Vector2 v2)
{
    return {v1.x - v2.x, v1.y - v2.y};
}

// Multiplies each component of a vector by a single float value (a "scalar").
inline Vector2 Vector2Scale(Vector2 v, float scale)
{
    return {v.x * scale, v.y * scale};
}

// Calculates the length (or "magnitude") of a vector.
// This is the distance from the origin (0,0) to the vector's point.
inline float Vector2Length(Vector2 v)
{
    return sqrtf((v.x * v.x) + (v.y * v.y));
}

inline Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistance)
{
    float dist = Vector2Distance(current, target);

    // If we are already at or very close to the target, just snap to it.
    if (dist <= maxDistance)
    {
        return target;
    }

    // Otherwise, move towards the target by maxDistance.
    Vector2 direction = Vector2Subtract(target, current);
    Vector2 normalizedDir = Vector2Normalize(direction);
    Vector2 movement = Vector2Scale(normalizedDir, maxDistance);

    return Vector2Add(current, movement);
}