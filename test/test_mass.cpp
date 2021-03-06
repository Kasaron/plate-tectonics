/******************************************************************************
 *  plate-tectonics, a plate tectonics simulation library
 *  Copyright (C) 2012-2013 Lauri Viitanen
 *  Copyright (C) 2014-2015 Federico Tomassetti, Bret Curtis
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see http://www.gnu.org/licenses/
 *****************************************************************************/

#include "mass.hpp"
#include "gtest/gtest.h"

TEST(MassBuilder, ConstructorFromHeightmap)
{
    float heightmap[20] = {0.0f, 0.0f, 0.0f, 0.0f, 10.3f,
                           5.0f, 0.0f, 0.0f, 0.0f,  0.0f,
                           0.2f, 0.0f, 0.0f, 0.0f,  0.0f,
                           1.0f, 1.0f, 0.0f, 0.0f,  0.0f};
    Dimension dim(5, 4);
    MassBuilder mb(heightmap, dim);
    EXPECT_FLOAT_EQ(17.5f, mb.build().getMass());
    EXPECT_FLOAT_EQ(2.4114285714285715f, mb.build().getCx());
    EXPECT_FLOAT_EQ(0.6514285714285715f, mb.build().getCy());
}

TEST(MassBuilder, AddPoint)
{
    MassBuilder mb;
    EXPECT_FLOAT_EQ(0.0f, mb.build().getMass());

    mb.addPoint(10, 10, 123.0);
    EXPECT_FLOAT_EQ(123.0f, mb.build().getMass());
    EXPECT_FLOAT_EQ(10.0f, mb.build().getCx());
    EXPECT_FLOAT_EQ(10.0f, mb.build().getCy());

    mb.addPoint(0, 5, 123.0);
    EXPECT_FLOAT_EQ(246.0f, mb.build().getMass());
    EXPECT_FLOAT_EQ(5.0f, mb.build().getCx());
    EXPECT_FLOAT_EQ(7.5f, mb.build().getCy());
}

TEST(Mass, Constructor)
{
    Mass mass1(0.0f, 7.5f, 8.5f);
    EXPECT_FLOAT_EQ(0.0f, mass1.getMass());

    Mass mass2(8.5f, 7.6f, 27.5f);
    EXPECT_FLOAT_EQ(8.5f, mass2.getMass());
    EXPECT_FLOAT_EQ(7.6f, mass2.getCx());
    EXPECT_FLOAT_EQ(27.5f, mass2.getCy());
}

TEST(Mass, Null)
{
    Mass mass1(0.0f, 7.5f, 8.5f);
    ASSERT_EQ(true, mass1.null());

    Mass mass2(8.5f, 7.6f, 27.5f);
    ASSERT_EQ(false, mass2.null());
}

TEST(Mass, IncMass)
{
    Mass mass(8.5f, 7.6f, 27.5f);
    EXPECT_FLOAT_EQ(8.5f, mass.getMass());
    EXPECT_FLOAT_EQ(7.6f, mass.getCx());
    EXPECT_FLOAT_EQ(27.5f, mass.getCy());

    mass.incMass(10.0f);
    EXPECT_FLOAT_EQ(18.5f, mass.getMass());
    EXPECT_FLOAT_EQ(7.6f, mass.getCx());
    EXPECT_FLOAT_EQ(27.5f, mass.getCy());

    mass.incMass(-18.0f);
    EXPECT_FLOAT_EQ(0.5f, mass.getMass());
    EXPECT_FLOAT_EQ(7.6f, mass.getCx());
    EXPECT_FLOAT_EQ(27.5f, mass.getCy());
}
