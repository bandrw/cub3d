#include "../includes/cub3d.h"

float	to_rad(float degrees)
{
	return (degrees * (float)M_PI / 180.f);
}

float	to_deg(float radians)
{
	return (radians * 180.f / (float)M_PI);
}
