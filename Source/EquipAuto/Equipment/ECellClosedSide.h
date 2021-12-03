#pragma once

UENUM()
enum class ECellClosedSide : uint8
{
	None = 0,
	Top = 1 << 0,
	Bottom = 1 << 1,
	Left = 1 << 2,
	Right = 1 << 3,
};

ENUM_CLASS_FLAGS(ECellClosedSide);