/**
 ******************************************************************************
 *
 * @file       alllayersoftype.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   OPMapWidget
 * @{
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include "alllayersoftype.h"

namespace core {
AllLayersOfType::AllLayersOfType()
{}
QVector<MapType::Types> AllLayersOfType::GetAllLayersOfType(const MapType::Types &type)
{
    QVector<MapType::Types> types;
	// santypilot 2024-2-21 google not accessible
	types.append(MapType::BingMap);
	/*
    {
        switch (type) {
        case MapType::GoogleHybrid:
        {
            types.append(MapType::GoogleSatellite);
            types.append(MapType::GoogleLabels);
        }
        break;

        case MapType::GoogleHybridChina:
        {
            types.append(MapType::GoogleSatelliteChina);
            types.append(MapType::GoogleLabelsChina);
        }
        break;

        case MapType::GoogleHybridKorea:
        {
            types.append(MapType::GoogleSatelliteKorea);
            types.append(MapType::GoogleLabelsKorea);
        }
        break;

        case MapType::OpenStreetMapSurferTerrain:
        {
            types.append(MapType::OpenStreetMapSurfer);
            types.append(MapType::OpenStreetMapSurferTerrain);
        }
        break;

        default:
        {
            types.append(type);
        }
        break;
        }
    }
	*/

    return types;
}
}
