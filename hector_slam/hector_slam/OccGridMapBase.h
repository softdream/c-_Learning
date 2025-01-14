//=================================================================================================
// Copyright (c) 2011, Stefan Kohlbrecher, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Simulation, Systems Optimization and Robotics
//       group, TU Darmstadt nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef __OCCGRIDMAPBASE_h_
#define __OCCGRIDMAPBASE_h_

#include "GridMapBase.h"

#include "DataPointContainer.h"
#include "UtilFunctions.h"

#include <Eigen/Geometry>

namespace hectorslam
{

template <typename ConcreteCellType, typename ConcreteGridFunctions>
class OccGridMapBase : public GridMapBase<ConcreteCellType>
{

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    OccGridMapBase(float mapResolution, const Eigen::Vector2i &size, const Eigen::Vector2f &offset)
        : GridMapBase<ConcreteCellType>(mapResolution, size, offset), currUpdateIndex(0), currMarkOccIndex(-1), currMarkFreeIndex(-1)
    {
    }

    virtual ~OccGridMapBase() {}

    void updateSetOccupied(int index)
    {
        concreteGridFunctions.updateSetOccupied(this->getCell(index));
    }

    void updateSetFree(int index)
    {
        concreteGridFunctions.updateSetFree(this->getCell(index));
    }

    void updateUnsetFree(int index)
    {
        concreteGridFunctions.updateUnsetFree(this->getCell(index));
    }

    float getGridProbabilityMap(int index) const
    {
        return concreteGridFunctions.getGridProbability(this->getCell(index));
    }

    bool isOccupied(int xMap, int yMap) const
    {
        return (this->getCell(xMap, yMap).isOccupied());
    }

    bool isFree(int xMap, int yMap) const
    {
        return (this->getCell(xMap, yMap).isFree());
    }

    bool isOccupied(int index) const
    {
        return (this->getCell(index).isOccupied());
    }

    bool isFree(int index) const
    {
        return (this->getCell(index).isFree());
    }

    float getObstacleThreshold() const
    {
        ConcreteCellType temp;
        temp.resetGridCell();
        return concreteGridFunctions.getGridProbability(temp);
    }

    void setUpdateFreeFactor(float factor)
    {
        concreteGridFunctions.setUpdateFreeFactor(factor);
    }

    void setUpdateOccupiedFactor(float factor)
    {
        concreteGridFunctions.setUpdateOccupiedFactor(factor);
    }

    /**
   * Updates the map using the given scan data and robot pose
   * @param dataContainer Contains the laser scan data
   * @param robotPoseWorld The 2D robot pose in world coordinates
   */
    void updateByScan(const DataContainer &dataContainer, const Eigen::Vector3f &robotPoseWorld)
    {
        currMarkFreeIndex = currUpdateIndex + 1;
        currMarkOccIndex = currUpdateIndex + 2;

        //Get pose in map coordinates from pose in world coordinates
        Eigen::Vector3f mapPose(this->getMapCoordsPose(robotPoseWorld));

        //Get a 2D homogenous transform that can be left-multiplied to a robot coordinates vector to get world coordinates of that vector
        Eigen::Affine2f poseTransform((Eigen::Translation2f(
                                           mapPose[0], mapPose[1]) *
                                       Eigen::Rotation2Df(mapPose[2])));

        //Get start point of all laser beams in map coordinates (same for alle beams, stored in robot coords in dataContainer)
        Eigen::Vector2f scanBeginMapf(poseTransform * dataContainer.getOrigo());

        //Get integer vector of laser beams start point
        Eigen::Vector2i scanBeginMapi(scanBeginMapf[0] + 0.5f, scanBeginMapf[1] + 0.5f);

        //Get number of valid beams in current scan
        int numValidElems = dataContainer.getSize();

        //std::cout << "\n maxD: " << maxDist << " num: " << numValidElems << "\n";

        //Iterate over all valid laser beams
        for (int i = 0; i < numValidElems; ++i)
        {

            //Get map coordinates of current beam endpoint
            Eigen::Vector2f scanEndMapf(poseTransform * (dataContainer.getVecEntry(i)));
            //std::cout << "\ns\n" << scanEndMapf << "\n";

            //add 0.5 to beam endpoint vector for following integer cast (to round, not truncate)
            scanEndMapf.array() += (0.5f);

            //Get integer map coordinates of current beam endpoint
            Eigen::Vector2i scanEndMapi(scanEndMapf.cast<int>());

            //Update map using a bresenham variant for drawing a line from beam start to beam endpoint in map coordinates
            if (scanBeginMapi != scanEndMapi)
            {
                updateLineBresenhami(scanBeginMapi, scanEndMapi);
            }
        }

        //Tell the map that it has been updated
        this->setUpdated();

        //Increase update index (used for updating grid cells only once per incoming scan)
        currUpdateIndex += 3;
    }

    /**
   * Updates the map using the given scan data and robot pose
   * @param dataContainer Contains the laser scan data
   * @param robotPoseWorld The 2D robot pose in world coordinates
   */
    void updateByScanJustOnce(const DataContainer &dataContainer, const Eigen::Vector3f &robotPoseWorld)
    {
        currMarkFreeIndex = currUpdateIndex + 1;
        currMarkOccIndex = currUpdateIndex + 2;

        //Get pose in map coordinates from pose in world coordinates
        // Eigen::Vector3f mapPose(this->getMapCoordsPose(robotPoseWorld));
        Eigen::Vector3f mapPose(800, 800, 0);
        //Get a 2D homogenous transform that can be left-multiplied to a robot coordinates vector to get world coordinates of that vector
        Eigen::Affine2f poseTransform((Eigen::Translation2f(
                                           mapPose[0], mapPose[1]) *
                                       Eigen::Rotation2Df(mapPose[2])));

        //Get start point of all laser beams in map coordinates (same for alle beams, stored in robot coords in dataContainer)
        Eigen::Vector2f scanBeginMapf(poseTransform * dataContainer.getOrigo());

        //Get integer vector of laser beams start point
        Eigen::Vector2i scanBeginMapi(scanBeginMapf[0] + 0.5f, scanBeginMapf[1] + 0.5f);

        //Get number of valid beams in current scan
        int numValidElems = dataContainer.getSize();

        //Iterate over all valid laser beams
        for (int i = 0; i < numValidElems; ++i)
        {
            //Get integer map coordinates of current beam endpoint
            Eigen::Vector2i scanEndMapi;
            scanEndMapi[0] = scanBeginMapi[0] + (int)round(dataContainer.getVecEntry(i)[0] / 0.05);
            scanEndMapi[1] = scanBeginMapi[1] + (int)round(dataContainer.getVecEntry(i)[1] / 0.05);

            //Update map using a bresenham variant for drawing a line from beam start to beam endpoint in map coordinates
            if (scanBeginMapi != scanEndMapi)
            {
                updateLineBresenhami(scanBeginMapi, scanEndMapi);
            }
        }

        //Tell the map that it has been updated
        this->setUpdated();

        //Increase update index (used for updating grid cells only once per incoming scan)
        currUpdateIndex += 3;
    }

    // 设置画线的起点与终点
    inline void updateLineBresenhami(const Eigen::Vector2i &beginMap, const Eigen::Vector2i &endMap, unsigned int max_length = UINT_MAX)
    {
        int x0 = beginMap[0];
        int y0 = beginMap[1];

        //check if beam start point is inside map, cancel update if this is not the case
        if ((x0 < 0) || (x0 >= this->getSizeX()) || (y0 < 0) || (y0 >= this->getSizeY()))
        {
            return;
        }

        int x1 = endMap[0];
        int y1 = endMap[1];

        //check if beam end point is inside map, cancel update if this is not the case
        if ((x1 < 0) || (x1 >= this->getSizeX()) || (y1 < 0) || (y1 >= this->getSizeY()))
        {
            return;
        }

        int dx = x1 - x0;
        int dy = y1 - y0;

        unsigned int abs_dx = abs(dx);
        unsigned int abs_dy = abs(dy);

        int offset_dx = util::sign(dx);
        int offset_dy = util::sign(dy) * this->sizeX;

        unsigned int startOffset = beginMap.y() * this->sizeX + beginMap.x();

        //if x is dominant
        if (abs_dx >= abs_dy)
        {
            int error_y = abs_dx / 2;
            bresenham2D(abs_dx, abs_dy, error_y, offset_dx, offset_dy, startOffset);
        }
        else
        {
            //otherwise y is dominant
            int error_x = abs_dy / 2;
            bresenham2D(abs_dy, abs_dx, error_x, offset_dy, offset_dx, startOffset);
        }

        // 将终点单独拿出来，设置占用
        unsigned int endOffset = endMap.y() * this->sizeX + endMap.x();
        this->bresenhamCellOcc(endOffset);
    }

    // 进行bresenham画线
    inline void bresenham2D(unsigned int abs_da, unsigned int abs_db, int error_b, 
                            int offset_a, int offset_b, 
                            unsigned int offset)
    {

        // 先把起点格子设置成free
        this->bresenhamCellFree(offset);

        unsigned int end = abs_da - 1;

        for (unsigned int i = 0; i < end; ++i)
        {
            offset += offset_a;

            // 对应 Sub += dy/dx, 这里的实现是对 左右两边同乘 dx 后的结果
            error_b += abs_db;  

            // 判断 Sub > 0 
            if ((unsigned int)error_b >= abs_da)
            {
                offset += offset_b;

                // 对应Sub += dy/dx - 1, dy/dx 在之前加过了，所以这里只减 1 ，再左右两边同乘 dx
                error_b -= abs_da;  
            }
            // 再将路径上的其他点设置成free
            this->bresenhamCellFree(offset);
        }
    }

    
    inline void bresenhamCellFree(unsigned int offset)// 更新这个格子为空闲格子，只更新这一个格子
    {
        ConcreteCellType &cell(this->getCell(offset));

        // 每一轮画线，每个格子只更新一次free
        if (cell.updateIndex < currMarkFreeIndex)
        {
            concreteGridFunctions.updateSetFree(cell);
            cell.updateIndex = currMarkFreeIndex;
        }
    }

    // 更新这个格子为占用格子，只更新这一个格子
    inline void bresenhamCellOcc(unsigned int offset)
    {
        ConcreteCellType &cell(this->getCell(offset));

        // 每一轮画线，每个格子只更新一次占用
        if (cell.updateIndex < currMarkOccIndex)
        {
            // 如果这个格子被设置成free了，先取消free，再设置占用
            if (cell.updateIndex == currMarkFreeIndex)
            {
                concreteGridFunctions.updateUnsetFree(cell);
            }
            concreteGridFunctions.updateSetOccupied(cell);
            cell.updateIndex = currMarkOccIndex;
        }
    }

protected:
    ConcreteGridFunctions concreteGridFunctions;
    int currUpdateIndex;
    int currMarkOccIndex;
    int currMarkFreeIndex;
};

} // namespace hectorslam

#endif
