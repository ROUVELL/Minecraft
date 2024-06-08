#pragma once


inline constexpr int floordiv(int a, int b) noexcept
{
	return (a < 0) ? (a / b) - 1 : (a / b);
}

inline constexpr int modfloordiv(int a, int b) noexcept
{
	return (a < 0 && a % b) ? (a / b) - 1 : (a / b);
}

template <typename T>
inline constexpr T abs(T a) noexcept
{
	return (a < 0) ? -a : a;
}

template<typename T>
inline constexpr T min(T a, T b) noexcept
{
    return (a < b) ? a : b;
}

template<typename T>
inline constexpr T max(T a, T b) noexcept
{
    return (a > b) ? a : b;
}

template<typename T>
inline constexpr T clamp(T val, T min, T max) noexcept
{
    return (val < min) ? min : (val > max) ? max : val;
}