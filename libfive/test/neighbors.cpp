/*
libfive: a CAD kernel for modeling with implicit functions
Copyright (C) 2017  Matt Keeter

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "catch.hpp"

#include "libfive/render/brep/neighbors.hpp"

using namespace Kernel;


/*
These test cases are hand-constructed by drawing them out.
Neighbor numbers are as follows (it makes sense in ternary)
   -------------
   | 3 | 5 | 4 |
   -------------
   | 6 | X | 7 |
   -------------
   | 0 | 2 | 1 |
   -------------

And XTree nnumbers are as follows (based on counting in binary):
  ---------
  | 2 | 3 |
  ---------
  | 0 | 1 |
  ---------
*/

TEST_CASE("Neighbors<2>::withinTreeIndex")
{
    // These test cases are hand-constructed by drawing them out on paper
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 0) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 1) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 2) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 3) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 4) == 3);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 5) == 2);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 6) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(0, 7) == 1);

    REQUIRE(Neighbors<2>::withinTreeIndex(1, 0) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 1) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 2) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 3) == 2);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 4) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 5) == 3);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 6) == 0);
    REQUIRE(Neighbors<2>::withinTreeIndex(1, 7) == -1);

    REQUIRE(Neighbors<2>::withinTreeIndex(2, 0) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 1) == 1);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 2) == 0);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 3) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 4) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 5) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 6) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(2, 7) == 3);

    REQUIRE(Neighbors<2>::withinTreeIndex(3, 0) == 0);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 1) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 2) == 1);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 3) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 4) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 5) == -1);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 6) == 2);
    REQUIRE(Neighbors<2>::withinTreeIndex(3, 7) == -1);
}

TEST_CASE("Neighbors<2>::neighborTargetIndex")
{
    REQUIRE(Neighbors<2>::neighborTargetIndex(0, 0) == std::make_pair(0,3));
    REQUIRE(Neighbors<2>::neighborTargetIndex(0, 1) == std::make_pair(2,3));
    REQUIRE(Neighbors<2>::neighborTargetIndex(0, 2) == std::make_pair(2,2));
    REQUIRE(Neighbors<2>::neighborTargetIndex(0, 3) == std::make_pair(6,3));
    REQUIRE(Neighbors<2>::neighborTargetIndex(0, 6) == std::make_pair(6,1));

    REQUIRE(Neighbors<2>::neighborTargetIndex(1, 0) == std::make_pair(2,2));
    REQUIRE(Neighbors<2>::neighborTargetIndex(1, 1) == std::make_pair(1,2));
    REQUIRE(Neighbors<2>::neighborTargetIndex(1, 2) == std::make_pair(2,3));
    REQUIRE(Neighbors<2>::neighborTargetIndex(1, 4) == std::make_pair(7,2));
    REQUIRE(Neighbors<2>::neighborTargetIndex(1, 7) == std::make_pair(7,0));

    REQUIRE(Neighbors<2>::neighborTargetIndex(2, 0) == std::make_pair(6,1));
    REQUIRE(Neighbors<2>::neighborTargetIndex(2, 3) == std::make_pair(3,1));
    REQUIRE(Neighbors<2>::neighborTargetIndex(2, 4) == std::make_pair(5,1));
    REQUIRE(Neighbors<2>::neighborTargetIndex(2, 5) == std::make_pair(5,0));
    REQUIRE(Neighbors<2>::neighborTargetIndex(2, 6) == std::make_pair(6,3));

    REQUIRE(Neighbors<2>::neighborTargetIndex(3, 1) == std::make_pair(7,0));
    REQUIRE(Neighbors<2>::neighborTargetIndex(3, 3) == std::make_pair(5,0));
    REQUIRE(Neighbors<2>::neighborTargetIndex(3, 4) == std::make_pair(4,0));
    REQUIRE(Neighbors<2>::neighborTargetIndex(3, 5) == std::make_pair(5,1));
    REQUIRE(Neighbors<2>::neighborTargetIndex(3, 7) == std::make_pair(7,2));
}
