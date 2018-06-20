#!/usr/bin/env python2
 
# Random placement helpers because I'm tired of using spreadsheets for doing this
#
# Kevin Cuzner
 
import math
from pcbnew import *
 
def place_circle(refdes, cdes, start_angle, center, radius, component_offset=0, hide_ref=True, lock=False):
    """
    Places components in a circle
    refdes: List of component references
    start_angle: Starting angle
    center: Tuple of (x, y) mils of circle center
    radius: Radius of the circle in mils
    component_offset: Offset in degrees for each component to add to angle
    hide_ref: Hides the reference if true, leaves it be if None
    lock: Locks the footprint if true
    """
    pcb = GetBoard()
    deg_per_idx = 360 / len(refdes)
    for idx, rd in enumerate(refdes):
        part = pcb.FindModuleByReference(rd)
        angle = (deg_per_idx * idx + start_angle) % 360
        print "{0}: {1}".format(rd, angle)
        xmils = center[0] + math.cos(math.radians(angle)) * radius
        ymils = center[1] + math.sin(math.radians(angle)) * radius
        part.SetPosition(wxPoint(FromMils(xmils), FromMils(ymils)))
        part.SetOrientation((angle - 90) * -10)
        #part.Flip(wxPoint(FromMils(xmils), FromMils(ymils)))
        if hide_ref is not None:
            part.Reference().SetVisible(not hide_ref)
            part.Value().SetVisible(not hide_ref)

        part = pcb.FindModuleByReference(cdes[idx])
        cxmils = xmils + math.cos(math.radians(angle)) * 175
        cymils = ymils + math.sin(math.radians(angle)) * 175
        part.SetPosition(wxPoint(FromMils(cxmils), FromMils(cymils)))
        part.SetOrientation((angle -90) * -10)
        #part.Flip(wxPoint(FromMils(cxmils), FromMils(cymils)))
        if hide_ref is not None:
            part.Reference().SetVisible(not hide_ref)
            part.Value().SetVisible(not hide_ref)
    print "Placement finished. Press F11 to refresh."

def clock(start_angle=270, center=(4000, 3000)):

    middle_LED = "U32"
    middle_C = "C37"
    pcb = GetBoard()
    part = pcb.FindModuleByReference(middle_LED)
    part.SetPosition(wxPoint(FromMils(center[0]), FromMils(center[1])))
    part.SetOrientation(-1800)
    part = pcb.FindModuleByReference(middle_C)
    part.SetPosition(wxPoint(FromMils(center[0] + 200), FromMils(center[1])))
    part.SetOrientation(-900)

    hours_LED = ["U" + str(c) for c in range(31,19,-1)]
    mins_LED = ["U" + str(c) for c in range(19, 7, -1)]
    mkrs_LED = ["U" + str(c) for c in range(7,3,-1)]

    hours_C = ["C" + str(c) for c in range(36,24,-1)]
    mins_C = ["C" + str(c) for c in range(24, 12, -1)]
    mkrs_C = ["C" + str(c) for c in range(12,8,-1)]

    place_circle(hours_LED, hours_C, start_angle, center, 800)
    place_circle(mins_LED, mins_C, start_angle, center, 1150)
    place_circle(mkrs_LED, mkrs_C, start_angle, center, 1500)

