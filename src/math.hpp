#pragma once

inline int floordiv(int a, int b) noexcept
{
	if (a < 0 && a % b)
		return (a / b) - 1;
	return a / b;
}

template <typename T>
inline T abs(T a) noexcept
{
	return (a < 0) ? -a : a;
}