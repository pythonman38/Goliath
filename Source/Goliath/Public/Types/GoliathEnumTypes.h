// Midnight Madness, Inc.

#pragma once

UENUM()
enum class EGoliathConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EGoliathValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EGoliathSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EGoliathCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EGoliathCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};