#include <gtest/gtest.h>

#include "../../src/util/Direction.hpp"

TEST(OppositeDirection, NoDirection)
{
    ASSERT_EQ(NO_DIRECTION, opp_dir(NO_DIRECTION));
}

TEST(OppositeDirection, East)
{
    ASSERT_EQ(WEST, opp_dir(EAST));
}

TEST(OppositeDirection, North)
{
    ASSERT_EQ(SOUTH, opp_dir(NORTH));
}

TEST(OppositeDirection, West)
{
    ASSERT_EQ(EAST, opp_dir(WEST));
}

TEST(OppositeDirection, South)
{
    ASSERT_EQ(NORTH, opp_dir(SOUTH));
}

TEST(OppositeDirection, NorthEast)
{
    ASSERT_EQ(SOUTH_WEST, opp_dir(NORTH_EAST));
}

TEST(OppositeDirection, NorthWest)
{
    ASSERT_EQ(SOUTH_EAST, opp_dir(NORTH_WEST));
}

TEST(OppositeDirection, SouthEast)
{
    ASSERT_EQ(NORTH_WEST, opp_dir(SOUTH_EAST));
}

TEST(OppositeDirection, SouthWest)
{
    ASSERT_EQ(NORTH_EAST, opp_dir(SOUTH_WEST));
}

bool not_in_array(int val, int array[NUM_DIRS])
{
    for (int i = 0; i < NUM_DIRS; i++) {
        if (val == array[i])
            return false;
    }

    return true;
}

TEST(IndexValue, Uniqueness)
{
    int found[NUM_DIRS] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int new_index_val;
    int found_ind = 0;

    new_index_val = index_value(NO_DIRECTION);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(EAST);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(NORTH);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(WEST);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(SOUTH);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(NORTH_EAST);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(NORTH_WEST);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(SOUTH_WEST);
    ASSERT_TRUE(not_in_array(new_index_val, found));
    found[found_ind++] = new_index_val;

    new_index_val = index_value(SOUTH_EAST);
    ASSERT_TRUE(not_in_array(new_index_val, found));
}

void ASSERT_VALID_INDEX(int index_val)
{
    ASSERT_LE(0, index_val);
    ASSERT_GT(NUM_DIRS, index_val);
}

TEST(IndexValue, ValidNoDirection)
{
    ASSERT_VALID_INDEX(index_value(NO_DIRECTION));
}

TEST(IndexValue, ValidEast)
{
    ASSERT_VALID_INDEX(index_value(EAST));
}

TEST(IndexValue, ValidNorth)
{
    ASSERT_VALID_INDEX(index_value(NORTH));
}

TEST(IndexValue, ValidWest)
{
    ASSERT_VALID_INDEX(index_value(WEST));
}

TEST(IndexValue, ValidSouth)
{
    ASSERT_VALID_INDEX(index_value(SOUTH));
}

TEST(IndexValue, ValidNorthEast)
{
    ASSERT_VALID_INDEX(index_value(NORTH_EAST));
}

TEST(IndexValue, ValidNorthWest)
{
    ASSERT_VALID_INDEX(index_value(NORTH_WEST));
}

TEST(IndexValue, ValidSouthEast)
{
    ASSERT_VALID_INDEX(index_value(SOUTH_EAST));
}

TEST(IndexValue, ValidSouthWest)
{
    ASSERT_VALID_INDEX(index_value(SOUTH_WEST));
}

TEST(HasDirection, NoDirection)
{
    ASSERT_TRUE(has_direction(NO_DIRECTION, NO_DIRECTION));

    ASSERT_FALSE(has_direction(NO_DIRECTION, EAST));
    ASSERT_FALSE(has_direction(NO_DIRECTION, WEST));
    ASSERT_FALSE(has_direction(NO_DIRECTION, SOUTH));
    ASSERT_FALSE(has_direction(NO_DIRECTION, NORTH));
    ASSERT_FALSE(has_direction(NO_DIRECTION, NORTH_WEST));
    ASSERT_FALSE(has_direction(NO_DIRECTION, SOUTH_WEST));
    ASSERT_FALSE(has_direction(NO_DIRECTION, NORTH_EAST));
    ASSERT_FALSE(has_direction(NO_DIRECTION, SOUTH_EAST));
}

TEST(HasDirection, East)
{
    ASSERT_TRUE(has_direction(EAST, NO_DIRECTION));
    ASSERT_TRUE(has_direction(EAST, EAST));

    ASSERT_FALSE(has_direction(EAST, WEST));
    ASSERT_FALSE(has_direction(EAST, SOUTH));
    ASSERT_FALSE(has_direction(EAST, NORTH));
    ASSERT_FALSE(has_direction(EAST, NORTH_WEST));
    ASSERT_FALSE(has_direction(EAST, SOUTH_WEST));
    ASSERT_FALSE(has_direction(EAST, NORTH_EAST));
    ASSERT_FALSE(has_direction(EAST, SOUTH_EAST));
}

TEST(HasDirection, North)
{
    ASSERT_TRUE(has_direction(NORTH, NO_DIRECTION));
    ASSERT_TRUE(has_direction(NORTH, NORTH));

    ASSERT_FALSE(has_direction(NORTH, WEST));
    ASSERT_FALSE(has_direction(NORTH, SOUTH));
    ASSERT_FALSE(has_direction(NORTH, EAST));
    ASSERT_FALSE(has_direction(NORTH, NORTH_WEST));
    ASSERT_FALSE(has_direction(NORTH, SOUTH_WEST));
    ASSERT_FALSE(has_direction(NORTH, NORTH_EAST));
    ASSERT_FALSE(has_direction(NORTH, SOUTH_EAST));
}

TEST(HasDirection, West)
{
    ASSERT_TRUE(has_direction(WEST, NO_DIRECTION));
    ASSERT_TRUE(has_direction(WEST, WEST));

    ASSERT_FALSE(has_direction(WEST, NORTH));
    ASSERT_FALSE(has_direction(WEST, SOUTH));
    ASSERT_FALSE(has_direction(WEST, EAST));
    ASSERT_FALSE(has_direction(WEST, NORTH_WEST));
    ASSERT_FALSE(has_direction(WEST, SOUTH_WEST));
    ASSERT_FALSE(has_direction(WEST, NORTH_EAST));
    ASSERT_FALSE(has_direction(WEST, SOUTH_EAST));
}

TEST(HasDirection, South)
{
    ASSERT_TRUE(has_direction(SOUTH, NO_DIRECTION));
    ASSERT_TRUE(has_direction(SOUTH, SOUTH));

    ASSERT_FALSE(has_direction(SOUTH, NORTH));
    ASSERT_FALSE(has_direction(SOUTH, WEST));
    ASSERT_FALSE(has_direction(SOUTH, EAST));
    ASSERT_FALSE(has_direction(SOUTH, NORTH_WEST));
    ASSERT_FALSE(has_direction(SOUTH, SOUTH_WEST));
    ASSERT_FALSE(has_direction(SOUTH, NORTH_EAST));
    ASSERT_FALSE(has_direction(SOUTH, SOUTH_EAST));
}

TEST(HasDirection, NorthWest)
{
    ASSERT_TRUE(has_direction(NORTH_WEST, NO_DIRECTION));
    ASSERT_TRUE(has_direction(NORTH_WEST, NORTH_WEST));
    ASSERT_TRUE(has_direction(NORTH_WEST, NORTH));
    ASSERT_TRUE(has_direction(NORTH_WEST, WEST));

    ASSERT_FALSE(has_direction(NORTH_WEST, SOUTH));
    ASSERT_FALSE(has_direction(NORTH_WEST, EAST));
    ASSERT_FALSE(has_direction(NORTH_WEST, SOUTH_WEST));
    ASSERT_FALSE(has_direction(NORTH_WEST, NORTH_EAST));
    ASSERT_FALSE(has_direction(NORTH_WEST, SOUTH_EAST));
}

TEST(HasDirection, NorthEast)
{
    ASSERT_TRUE(has_direction(NORTH_EAST, NO_DIRECTION));
    ASSERT_TRUE(has_direction(NORTH_EAST, NORTH_EAST));
    ASSERT_TRUE(has_direction(NORTH_EAST, NORTH));
    ASSERT_TRUE(has_direction(NORTH_EAST, EAST));

    ASSERT_FALSE(has_direction(NORTH_EAST, SOUTH));
    ASSERT_FALSE(has_direction(NORTH_EAST, WEST));
    ASSERT_FALSE(has_direction(NORTH_EAST, SOUTH_WEST));
    ASSERT_FALSE(has_direction(NORTH_EAST, NORTH_WEST));
    ASSERT_FALSE(has_direction(NORTH_EAST, SOUTH_EAST));
}

TEST(HasDirection, SouthWest)
{
    ASSERT_TRUE(has_direction(SOUTH_WEST, NO_DIRECTION));
    ASSERT_TRUE(has_direction(SOUTH_WEST, SOUTH_WEST));
    ASSERT_TRUE(has_direction(SOUTH_WEST, SOUTH));
    ASSERT_TRUE(has_direction(SOUTH_WEST, WEST));

    ASSERT_FALSE(has_direction(SOUTH_WEST, NORTH));
    ASSERT_FALSE(has_direction(SOUTH_WEST, EAST));
    ASSERT_FALSE(has_direction(SOUTH_WEST, NORTH_WEST));
    ASSERT_FALSE(has_direction(SOUTH_WEST, NORTH_EAST));
    ASSERT_FALSE(has_direction(SOUTH_WEST, SOUTH_EAST));
}

TEST(HasDirection, SouthEast)
{
    ASSERT_TRUE(has_direction(SOUTH_EAST, NO_DIRECTION));
    ASSERT_TRUE(has_direction(SOUTH_EAST, SOUTH_EAST));
    ASSERT_TRUE(has_direction(SOUTH_EAST, SOUTH));
    ASSERT_TRUE(has_direction(SOUTH_EAST, EAST));

    ASSERT_FALSE(has_direction(SOUTH_EAST, NORTH));
    ASSERT_FALSE(has_direction(SOUTH_EAST, WEST));
    ASSERT_FALSE(has_direction(SOUTH_EAST, SOUTH_WEST));
    ASSERT_FALSE(has_direction(SOUTH_EAST, NORTH_WEST));
    ASSERT_FALSE(has_direction(SOUTH_EAST, NORTH_EAST));
}

TEST(IsCardinalDir, NoDirection)
{
    ASSERT_FALSE(is_cardinal_dir(NO_DIRECTION));
}

TEST(IsCardinalDir, East)
{
    ASSERT_TRUE(is_cardinal_dir(EAST));
}

TEST(IsCardinalDir, North)
{
    ASSERT_TRUE(is_cardinal_dir(NORTH));
}

TEST(IsCardinalDir, West)
{
    ASSERT_TRUE(is_cardinal_dir(WEST));
}

TEST(IsCardinalDir, South)
{
    ASSERT_TRUE(is_cardinal_dir(SOUTH));
}

TEST(IsCardinalDir, NorthEast)
{
    ASSERT_FALSE(is_cardinal_dir(NORTH_EAST));
}

TEST(IsCardinalDir, NorthWest)
{
    ASSERT_FALSE(is_cardinal_dir(SOUTH_EAST));
}

TEST(IsCardinalDir, SouthWest)
{
    ASSERT_FALSE(is_cardinal_dir(SOUTH_WEST));
}

TEST(IsCardinalDir, SouthEast)
{
    ASSERT_FALSE(is_cardinal_dir(SOUTH_EAST));
}

TEST(IsHorizDir, NoDirection)
{
    ASSERT_FALSE(is_horiz_dir(NO_DIRECTION));
}

TEST(IsHorizDir, East)
{
    ASSERT_TRUE(is_horiz_dir(EAST));
}

TEST(IsHorizDir, North)
{
    ASSERT_FALSE(is_horiz_dir(NORTH));
}

TEST(IsHorizDir, West)
{
    ASSERT_TRUE(is_horiz_dir(WEST));
}

TEST(IsHorizDir, South)
{
    ASSERT_FALSE(is_horiz_dir(SOUTH));
}

TEST(IsHorizDir, NorthEast)
{
    ASSERT_FALSE(is_horiz_dir(NORTH_EAST));
}

TEST(IsHorizDir, NorthWest)
{
    ASSERT_FALSE(is_horiz_dir(SOUTH_EAST));
}

TEST(IsHorizDir, SouthWest)
{
    ASSERT_FALSE(is_horiz_dir(SOUTH_WEST));
}

TEST(IsHorizDir, SouthEast)
{
    ASSERT_FALSE(is_horiz_dir(SOUTH_EAST));
}

TEST(MergeDirections, NoDirection)
{
    ASSERT_EQ(NO_DIRECTION, merge_directions(NO_DIRECTION, NO_DIRECTION));
    ASSERT_EQ(EAST, merge_directions(NO_DIRECTION, EAST));
    ASSERT_EQ(NORTH, merge_directions(NO_DIRECTION, NORTH));
    ASSERT_EQ(WEST, merge_directions(NO_DIRECTION, WEST));
    ASSERT_EQ(SOUTH, merge_directions(NO_DIRECTION, SOUTH));
    ASSERT_EQ(NORTH_EAST, merge_directions(NO_DIRECTION, NORTH_EAST));
    ASSERT_EQ(NORTH_WEST, merge_directions(NO_DIRECTION, NORTH_WEST));
    ASSERT_EQ(SOUTH_WEST, merge_directions(NO_DIRECTION, SOUTH_WEST));
    ASSERT_EQ(SOUTH_EAST, merge_directions(NO_DIRECTION, SOUTH_EAST));
}

TEST(MergeDirections, East)
{
    ASSERT_EQ(EAST, merge_directions(EAST, NO_DIRECTION));
    ASSERT_EQ(EAST, merge_directions(EAST, EAST));
    ASSERT_EQ(NORTH_EAST, merge_directions(EAST, NORTH));
    ASSERT_EQ(NO_DIRECTION, merge_directions(EAST, WEST));
    ASSERT_EQ(SOUTH_EAST, merge_directions(EAST, SOUTH));
    ASSERT_EQ(NORTH_EAST, merge_directions(EAST, NORTH_EAST));
    ASSERT_EQ(NORTH, merge_directions(EAST, NORTH_WEST));
    ASSERT_EQ(SOUTH, merge_directions(EAST, SOUTH_WEST));
    ASSERT_EQ(SOUTH_EAST, merge_directions(EAST, SOUTH_EAST));
}

TEST(MergeDirections, North)
{
    ASSERT_EQ(NORTH, merge_directions(NORTH, NO_DIRECTION));
    ASSERT_EQ(NORTH_EAST, merge_directions(NORTH, EAST));
    ASSERT_EQ(NORTH, merge_directions(NORTH, NORTH));
    ASSERT_EQ(NORTH_WEST, merge_directions(NORTH, WEST));
    ASSERT_EQ(NO_DIRECTION, merge_directions(NORTH, SOUTH));
    ASSERT_EQ(NORTH_EAST, merge_directions(NORTH, NORTH_EAST));
    ASSERT_EQ(NORTH_WEST, merge_directions(NORTH, NORTH_WEST));
    ASSERT_EQ(WEST, merge_directions(NORTH, SOUTH_WEST));
    ASSERT_EQ(EAST, merge_directions(NORTH, SOUTH_EAST));
}

TEST(MergeDirections, West)
{
    ASSERT_EQ(WEST, merge_directions(WEST, NO_DIRECTION));
    ASSERT_EQ(NO_DIRECTION, merge_directions(WEST, EAST));
    ASSERT_EQ(NORTH_WEST, merge_directions(WEST, NORTH));
    ASSERT_EQ(WEST, merge_directions(WEST, WEST));
    ASSERT_EQ(SOUTH_WEST, merge_directions(WEST, SOUTH));
    ASSERT_EQ(NORTH, merge_directions(WEST, NORTH_EAST));
    ASSERT_EQ(NORTH_WEST, merge_directions(WEST, NORTH_WEST));
    ASSERT_EQ(SOUTH_WEST, merge_directions(WEST, SOUTH_WEST));
    ASSERT_EQ(SOUTH, merge_directions(WEST, SOUTH_EAST));
}

TEST(MergeDirections, South)
{
    ASSERT_EQ(SOUTH, merge_directions(SOUTH, NO_DIRECTION));
    ASSERT_EQ(SOUTH_EAST, merge_directions(SOUTH, EAST));
    ASSERT_EQ(NO_DIRECTION, merge_directions(SOUTH, NORTH));
    ASSERT_EQ(SOUTH_WEST, merge_directions(SOUTH, WEST));
    ASSERT_EQ(SOUTH, merge_directions(SOUTH, SOUTH));
    ASSERT_EQ(EAST, merge_directions(SOUTH, NORTH_EAST));
    ASSERT_EQ(WEST, merge_directions(SOUTH, NORTH_WEST));
    ASSERT_EQ(SOUTH_WEST, merge_directions(SOUTH, SOUTH_WEST));
    ASSERT_EQ(SOUTH_EAST, merge_directions(SOUTH, SOUTH_EAST));
}

TEST(MergeDirections, NorthEast)
{
    ASSERT_EQ(NORTH_EAST, merge_directions(NORTH_EAST, NO_DIRECTION));
    ASSERT_EQ(NORTH_EAST, merge_directions(NORTH_EAST, EAST));
    ASSERT_EQ(NORTH_EAST, merge_directions(NORTH_EAST, NORTH));
    ASSERT_EQ(NORTH, merge_directions(NORTH_EAST, WEST));
    ASSERT_EQ(EAST, merge_directions(NORTH_EAST, SOUTH));
    ASSERT_EQ(NORTH_EAST, merge_directions(NORTH_EAST, NORTH_EAST));
    ASSERT_EQ(NORTH, merge_directions(NORTH_EAST, NORTH_WEST));
    ASSERT_EQ(NO_DIRECTION, merge_directions(NORTH_EAST, SOUTH_WEST));
    ASSERT_EQ(EAST, merge_directions(NORTH_EAST, SOUTH_EAST));
}

TEST(MergeDirections, NorthWest)
{
    ASSERT_EQ(NORTH_WEST, merge_directions(NORTH_WEST, NO_DIRECTION));
    ASSERT_EQ(NORTH, merge_directions(NORTH_WEST, EAST));
    ASSERT_EQ(NORTH_WEST, merge_directions(NORTH_WEST, NORTH));
    ASSERT_EQ(NORTH_WEST, merge_directions(NORTH_WEST, WEST));
    ASSERT_EQ(WEST, merge_directions(NORTH_WEST, SOUTH));
    ASSERT_EQ(NORTH, merge_directions(NORTH_WEST, NORTH_EAST));
    ASSERT_EQ(NORTH_WEST, merge_directions(NORTH_WEST, NORTH_WEST));
    ASSERT_EQ(WEST, merge_directions(NORTH_WEST, SOUTH_WEST));
    ASSERT_EQ(NO_DIRECTION, merge_directions(NORTH_WEST, SOUTH_EAST));
}

TEST(MergeDirections, SouthWest)
{
    ASSERT_EQ(SOUTH_WEST, merge_directions(SOUTH_WEST, NO_DIRECTION));
    ASSERT_EQ(SOUTH, merge_directions(SOUTH_WEST, EAST));
    ASSERT_EQ(WEST, merge_directions(SOUTH_WEST, NORTH));
    ASSERT_EQ(SOUTH_WEST, merge_directions(SOUTH_WEST, WEST));
    ASSERT_EQ(SOUTH_WEST, merge_directions(SOUTH_WEST, SOUTH));
    ASSERT_EQ(NO_DIRECTION, merge_directions(SOUTH_WEST, NORTH_EAST));
    ASSERT_EQ(WEST, merge_directions(SOUTH_WEST, NORTH_WEST));
    ASSERT_EQ(SOUTH_WEST, merge_directions(SOUTH_WEST, SOUTH_WEST));
    ASSERT_EQ(SOUTH, merge_directions(SOUTH_WEST, SOUTH_EAST));
}

TEST(MergeDirections, SouthEast)
{
    ASSERT_EQ(SOUTH_EAST, merge_directions(SOUTH_EAST, NO_DIRECTION));
    ASSERT_EQ(SOUTH_EAST, merge_directions(SOUTH_EAST, EAST));
    ASSERT_EQ(EAST, merge_directions(SOUTH_EAST, NORTH));
    ASSERT_EQ(SOUTH, merge_directions(SOUTH_EAST, WEST));
    ASSERT_EQ(SOUTH_EAST, merge_directions(SOUTH_EAST, SOUTH));
    ASSERT_EQ(EAST, merge_directions(SOUTH_EAST, NORTH_EAST));
    ASSERT_EQ(NO_DIRECTION, merge_directions(SOUTH_EAST, NORTH_WEST));
    ASSERT_EQ(SOUTH, merge_directions(SOUTH_EAST, SOUTH_WEST));
    ASSERT_EQ(SOUTH_EAST, merge_directions(SOUTH_EAST, SOUTH_EAST));
}

TEST(RemoveDirection, NoDirection)
{
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, NO_DIRECTION));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, EAST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, NORTH));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, SOUTH));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, NORTH_EAST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, NORTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, SOUTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NO_DIRECTION, SOUTH_EAST));
}

TEST(RemoveDirection, East)
{
    ASSERT_EQ(EAST, remove_direction(EAST, NO_DIRECTION));
    ASSERT_EQ(NO_DIRECTION, remove_direction(EAST, EAST));
    ASSERT_EQ(EAST, remove_direction(EAST, NORTH));
    ASSERT_EQ(EAST, remove_direction(EAST, WEST));
    ASSERT_EQ(EAST, remove_direction(EAST, SOUTH));
    ASSERT_EQ(NO_DIRECTION, remove_direction(EAST, NORTH_EAST));
    ASSERT_EQ(EAST, remove_direction(EAST, NORTH_WEST));
    ASSERT_EQ(EAST, remove_direction(EAST, SOUTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(EAST, SOUTH_EAST));
}

TEST(RemoveDirection, North)
{
    ASSERT_EQ(NORTH, remove_direction(NORTH, NO_DIRECTION));
    ASSERT_EQ(NORTH, remove_direction(NORTH, EAST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NORTH, NORTH));
    ASSERT_EQ(NORTH, remove_direction(NORTH, WEST));
    ASSERT_EQ(NORTH, remove_direction(NORTH, SOUTH));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NORTH, NORTH_EAST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NORTH, NORTH_WEST));
    ASSERT_EQ(NORTH, remove_direction(NORTH, SOUTH_WEST));
    ASSERT_EQ(NORTH, remove_direction(NORTH, SOUTH_EAST));
}

TEST(RemoveDirection, West)
{
    ASSERT_EQ(WEST, remove_direction(WEST, NO_DIRECTION));
    ASSERT_EQ(WEST, remove_direction(WEST, EAST));
    ASSERT_EQ(WEST, remove_direction(WEST, NORTH));
    ASSERT_EQ(NO_DIRECTION, remove_direction(WEST, WEST));
    ASSERT_EQ(WEST, remove_direction(WEST, SOUTH));
    ASSERT_EQ(WEST, remove_direction(WEST, NORTH_EAST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(WEST, NORTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(WEST, SOUTH_WEST));
    ASSERT_EQ(WEST, remove_direction(WEST, SOUTH_EAST));
}

TEST(RemoveDirection, South)
{
    ASSERT_EQ(SOUTH, remove_direction(SOUTH, NO_DIRECTION));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH, EAST));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH, NORTH));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH, WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(SOUTH, SOUTH));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH, NORTH_EAST));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH, NORTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(SOUTH, SOUTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(SOUTH, SOUTH_EAST));
}

TEST(RemoveDirection, NorthEast)
{
    ASSERT_EQ(NORTH_EAST, remove_direction(NORTH_EAST, NO_DIRECTION));
    ASSERT_EQ(NORTH, remove_direction(NORTH_EAST, EAST));
    ASSERT_EQ(EAST, remove_direction(NORTH_EAST, NORTH));
    ASSERT_EQ(NORTH_EAST, remove_direction(NORTH_EAST, WEST));
    ASSERT_EQ(NORTH_EAST, remove_direction(NORTH_EAST, SOUTH));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NORTH_EAST, NORTH_EAST));
    ASSERT_EQ(EAST, remove_direction(NORTH_EAST, NORTH_WEST));
    ASSERT_EQ(NORTH_EAST, remove_direction(NORTH_EAST, SOUTH_WEST));
    ASSERT_EQ(NORTH, remove_direction(NORTH_EAST, SOUTH_EAST));
}

TEST(RemoveDirection, NorthWest)
{
    ASSERT_EQ(NORTH_WEST, remove_direction(NORTH_WEST, NO_DIRECTION));
    ASSERT_EQ(NORTH_WEST, remove_direction(NORTH_WEST, EAST));
    ASSERT_EQ(WEST, remove_direction(NORTH_WEST, NORTH));
    ASSERT_EQ(NORTH, remove_direction(NORTH_WEST, WEST));
    ASSERT_EQ(NORTH_WEST, remove_direction(NORTH_WEST, SOUTH));
    ASSERT_EQ(WEST, remove_direction(NORTH_WEST, NORTH_EAST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(NORTH_WEST, NORTH_WEST));
    ASSERT_EQ(NORTH, remove_direction(NORTH_WEST, SOUTH_WEST));
    ASSERT_EQ(NORTH_WEST, remove_direction(NORTH_WEST, SOUTH_EAST));
}

TEST(RemoveDirection, SouthWest)
{
    ASSERT_EQ(SOUTH_WEST, remove_direction(SOUTH_WEST, NO_DIRECTION));
    ASSERT_EQ(SOUTH_WEST, remove_direction(SOUTH_WEST, EAST));
    ASSERT_EQ(SOUTH_WEST, remove_direction(SOUTH_WEST, NORTH));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH_WEST, WEST));
    ASSERT_EQ(WEST, remove_direction(SOUTH_WEST, SOUTH));
    ASSERT_EQ(SOUTH_WEST, remove_direction(SOUTH_WEST, NORTH_EAST));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH_WEST, NORTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(SOUTH_WEST, SOUTH_WEST));
    ASSERT_EQ(WEST, remove_direction(SOUTH_WEST, SOUTH_EAST));
}

TEST(RemoveDirection, SouthEast)
{
    ASSERT_EQ(SOUTH_EAST, remove_direction(SOUTH_EAST, NO_DIRECTION));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH_EAST, EAST));
    ASSERT_EQ(SOUTH_EAST, remove_direction(SOUTH_EAST, NORTH));
    ASSERT_EQ(SOUTH_EAST, remove_direction(SOUTH_EAST, WEST));
    ASSERT_EQ(EAST, remove_direction(SOUTH_EAST, SOUTH));
    ASSERT_EQ(SOUTH, remove_direction(SOUTH_EAST, NORTH_EAST));
    ASSERT_EQ(SOUTH_EAST, remove_direction(SOUTH_EAST, NORTH_WEST));
    ASSERT_EQ(EAST, remove_direction(SOUTH_EAST, SOUTH_WEST));
    ASSERT_EQ(NO_DIRECTION, remove_direction(SOUTH_EAST, SOUTH_EAST));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
