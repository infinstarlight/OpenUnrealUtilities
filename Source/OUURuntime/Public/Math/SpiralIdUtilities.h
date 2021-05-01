﻿// Copyright (c) 2021 Jonas Reich

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpiralIdUtilities.generated.h"

/**
 * Utility functions for converting traditional XY coordinates to clockwise spiral IDs and vice versa.
 * Spiral IDs allow indexing a 2D grid with only positive numbers starting at the origin.
 * The resulting grid looks like this (notice flipped Y axis matching UE4 coordinate system when looking down):
 *
  *     -2   -1   +0   +1
 *    +----+----+----+----+
 * -2 | 15 | 04 | 05 | 06 |
 *    +----+----+----+----+
 * -1 | 14 | 03 | 00 | 07 |
 *    +----+----o----+----+
 * +0 | 13 | 02 | 01 | 08 |
 *    +----+----+----+----+
 * +1 | 12 | 11 | 10 | 09 |
 *    +----+----+----+----+
 *
 * Note that the spiral origin is somewhere between the 0 and -1 row/columns.
 * This can be explained by the fact that the grid coordinates describe the cells bottom left
 * corner. So when projected to a normalized coordinate system with cells of 1 unit width
 * you get a grid that looks like this:
 * 
 *   -2   -1    0   +1   +2
 * -2 +----+----+----+----+
 *    | 15 | 04 | 05 | 06 |
 * -1 +----+----+----+----+
 *    | 14 | 03 | 00 | 07 |
 *  0 +----+----o----+----+
 *    | 13 | 02 | 01 | 08 |
 * +1 +----+----+----+----+
 *    | 12 | 11 | 10 | 09 |
 * +2 +----+----+----+----+
 *
 * The grid size can of course also be different than 1, then we get slightly different numbers,
 * e.g. for a grid width of 150 units you would get a grid like this:
 *
 *    -300 -150   0  +150 +300
 * -300 +----+----+----+----+
 *      | 15 | 04 | 05 | 06 |
 * -150 +----+----+----+----+
 *      | 14 | 03 | 00 | 07 |
 *    0 +----+----o----+----+
 *      | 13 | 02 | 01 | 08 |
 * +150 +----+----+----+----+
 *      | 12 | 11 | 10 | 09 |
 * +300 +----+----+----+----+
 *
 * For all of the distance based conversions, the grid cells are assumed to be squares,
 * even though the grid to spiral ID conversion would work just as well with rectangular cells.
 */
UCLASS(BlueprintType)
class OUURUNTIME_API USpiralIdUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Convert grid coordinates to spiral coordinates.
	 * Note that this uses grid coordinates as in grid cells, so the world coordinates will likely be different from X and Y.
	 */
	UFUNCTION(BlueprintPure)
	static int32 ConvertCoordinatesToSpiralId(const int32 X, const int32 Y);

	/**
	 * Convert grid coordinates to spiral coordinates.
	 * Note that this uses grid coordinates as in grid cells, so the world coordinates will likely be different from X and Y.
	 */
	UFUNCTION(BlueprintPure)
	static int32 ConvertCoordinatePointToSpiralId(const FIntPoint& Point);

	/**
	 * Convert a world location in 2D coordinates to a spiral ID.
	 * 
	 * @param	Location	The location to convert
	 * @param	GridSize	Width of the grid cells
	 */
	UFUNCTION(BlueprintPure)
	static int32 ConvertWorldLocation2DToSpiralId(const FVector2D& Location, float GridSize);

	/**
	 * Convert a world location in 3D space into a spiral ID.
	 * The Z component is ignored for this conversion so this is merely a convenience function.
	 * 
	 * @param	Location	The location to convert
	 * @param	GridSize	Width of the grid cells
	 */
	UFUNCTION(BlueprintPure)
	static int32 ConvertWorldLocationToSpiralId(const FVector& Location, float GridSize);

	/**
	 * Convert a spiral ID to grid coordinates.
	 */
	UFUNCTION(BlueprintPure)
	static FIntPoint ConvertSpiralIdToCoordinates(const int32 SpiralId);

	/**
	 * Convert a spiral ID to the center location of a grid cell in world space.
	 * 
	 * @param	SpiralId	Spiral Id of the cell to convert
	 * @param	GridSize	Width of the grid cells
	 * @returns				Center location of the cell in world space
	 */
	UFUNCTION(BlueprintPure)
	static FVector2D ConvertSpiralIdToCenterLocation(const int32 SpiralId, float GridSize);

	/**
	 * Convert a spiral ID to the 2D bounds of a cell in world space.
	 * 
	 * @param	SpiralId	Spiral Id of the cell to convert
	 * @param	GridSize	Width of the grid cells
	 * @returns				Two dimensional bound of the cell
	 */
	UFUNCTION(BlueprintPure)
	static FBox2D ConvertSpiralIdToBounds(const int32 SpiralId, const float GridSize);

	/**
	 * Convert a spiral ID to the 3D bounds of a cell in world space.
	 * Because the spiral ID only describes the 2D location of the cell,
	 * the height and elevation have to be supplied by the function caller.
	 * 
	 * @param	SpiralId			Spiral Id of the cell to convert
	 * @param	GridSize			Width of the grid cells
	 * @param	BoundsHeight		Height of the grid cell
	 * @param	BoundsElevation		Distance between Z=0 and bottom surface of the grid cell
	 * @returns						Two dimensional bound of the cell
	 */
	UFUNCTION(BlueprintPure)
	static FBox ConvertSpiralIdToBounds3D(const int32 SpiralId, const float GridSize, const float BoundsHeight, const float BoundsElevation);
};
