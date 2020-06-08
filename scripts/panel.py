#!/bin/python3

import os
import sys

# Get pcb file path/file-name
path_to_file=sys.argv[1]
project_path = os.path.abspath(os.path.split(path_to_file)[0])

# Determine version number
version = os.path.split(path_to_file)[-2]
version = version.split("/")[-2]

# Determine *.kicad_pcb file name
file_name = path_to_file.split("/")[-1]


# Mouse bite specifications
filletRadius = 1.2
holeDia = 0.3
holeInset = -holeDia / 2.0
holeInsetWord = "flush"
pitch = 1
tabWidth = 2.5

while(True):
    usrFilletRadius = input("Fillet Radius, currently {}mm: ".format(filletRadius))
    usrHoleDia = input("Hole Diameter, currently {}mm: ".format(holeDia))
    usrHoleInset = input("Hole Inset, currently {}. Enter inset, flush, or a custom number: ".format(holeInsetWord))
    usrHolePitch = input("Hole Pitch, currently {}mm: ".format(pitch))
    usrTabWidth = input("Tab Width, currently {}mm: ".format(tabWidth))

    if usrFilletRadius:
        filletRadius = float(usrFilletRadius)

    if usrHoleDia:
        holeDia = float(usrHoleDia)

    if usrHoleInset:
        holeInsetWord = usrHoleInset
        if usrHoleInset == "inset" or usrHoleInset == "i":
            holeInset = float(holeDia) / 2.0 + 0.05
        elif usrHoleInset == "flush" or usrHoleInset == 'f':
            holeInset = -float(holeDia) / 2.0
        else:
            holeInset = usrHoleInset
    else:
        holeInset = -float(holeDia) / 2.0

    if usrHolePitch:
        pitch = float(usrHolePitch)

    if usrTabWidth:
        tabWidth = float(usrTabWidth)

    # compose the command line string, may need to change dir for kicadutil.jar
    cmd = "java -jar scripts/kicadutil.jar pcb --file={} panel --fillet={} --hole={} --inset={} --pitch={} --width={}".format(path_to_file,filletRadius,holeDia,holeInset,pitch,tabWidth)

    # run the command
    os.system(cmd)
    os.system("pcbnew hardware/{}/panel/output.{}".format(version, file_name))

    print("\nLets do it again!\n")

