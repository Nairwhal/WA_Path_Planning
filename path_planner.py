"""
    This module is your primary workspace. Add whatever helper functions, classes, data structures, imports... etc here.

    We expect most results will utilize more than just dumping code into the plan_paths()
        function, that just serves as a meaningful entry point.

    In order for the rest of the scoring to work, you need to make sure you have correctly
        populated the Destination.path for each result you produce.
"""
import typing
from queue import PriorityQueue

import numpy as np
from typing import Dict

from map_info import Coordinate, Destination, MapInfo

import ctypes

cPathPlan = ctypes.CDLL("./PathPlanner.so").planPath_c
cPathPlan.restype = ctypes.POINTER(ctypes.c_int)

class PathPlanner:
    def __init__(self, map_info: MapInfo, destinations: typing.List["Destination"]):
        self.map_info: MapInfo = map_info
        self.destinations: typing.List["Destination"] = destinations

    def plan_paths(self):
        width = self.map_info.risk_zones.ctypes.shape[0]
        height = self.map_info.risk_zones.ctypes.shape[1]
        data = self.map_info.risk_zones.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

        maxRange = self.map_info.maximum_range;
        startCoordX = self.map_info.start_coord[0];
        startCoordY = self.map_info.start_coord[1];
        """
        This is the function you should re-write. It is expected to mutate the list of
        destinations by calling each Destination's set_path() with the resulting
        path as an argument.

        The default construction shows this format, and should produce 10 invalid paths.
        """
        for site in self.destinations:
            path_coords_ptr = cPathPlan(width, height, data, maxRange, startCoordX, startCoordY, site.coord[0], site.coord[1])
            path_coords = []

            for i in range(path_coords_ptr[0]):
                path_coords.append(Coordinate(path_coords_ptr[1 + i * 2], path_coords_ptr[2 + i * 2]));

            # Once you have a solution for the site - populate it like this:
            site.set_path(path_coords)
