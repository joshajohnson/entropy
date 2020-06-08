# Board Release Process

* [ ] Ensure [Schematic Review](#schematic-review) is complete
* [ ] Ensure [Layout Review](#layout-review) is complete
* [ ] Component MPN / Supplier PN information added for all components
* [ ] PDF Schematic is exported from EESchema
* [ ] Rerun DRC and zone fills before exporting CAM files to ensure proper results
* [ ] Inspect layout in 3D viewer one last time
* [ ] Export gerber/drill, BOM, and PnP files by calling `make`
* [ ] Visually verify final CAM files to ensure no obvious misalignments, issues with paste and mask size / location

## Schematic Review
### General

* [ ] CAD ERC 100% clean. If some errors are invalid due to toolchain quirks, each exception must be inspected and signed
off as invalid
* [ ] Verify pin numbers of all schematic symbols against datasheet or external interface specification document (if not yet board proven)
* [ ] Schematic symbol matches chosen component package

#### Passive components
* [ ] Power/voltage/tolerance ratings specified as required
* [ ] Ceramic capacitors appropriately de-rated for C/V curve
* [ ] Polarized components specified in schematic if using electrolytic caps etc

### Power supply

* [ ] Fusing and/or reverse voltage protection at system power inlet

#### Regulators

* [ ] Verify estimated power usage per rail against regulator rating
* [ ] Linear regulators are stable with selected output cap ESR
* [ ] Confirm power rail sequencing against device datasheets

#### Decoupling
* [ ] Decoupling present for all ICs
* [ ] Decoupling meets/exceeds vendor recommendations if specified
* [ ] Bulk decoupling present at PSU

#### General
* [ ] All power inputs fed by correct voltage
* [ ] Check high-power discrete semiconductors and passives to confirm they can handle expected load
* [ ] Analog rails filtered/isolated from digital circuitry as needed

### Signals

#### Digital

* [ ] Signals are correct logic level for input pin
* [ ] Pullups on all open-drain outputs
* [ ] Termination on all high-speed signals
* [ ] TX/RX paired correctly for UART, SPI, MGT, etc
* [ ] Differential pair polarity / pairing correct
* [ ] Active high/low enable signal polarity correct

#### Clocks

* [ ] Correct load caps provided for discrete crystals
* [ ] Crystals only used if IC has an integrated crystal driver

#### Strap/init pins
* [ ] Pullup/pulldowns on all signals that need defined state at boot
* [ ] Strap pins connected to correct rail for desired state
* [ ] JTAG/ICSP connector provided for all programmable devices
* [ ] Reference resistors correct value and reference rail

#### External interface protection

* [ ] Power outputs (USB etc) current limited
* [ ] ESD protection on data lines going off board

#### Debugging / reworkability

* [ ] Use 0-ohm resistors vs direct hard-wiring for strap pins when possible
* [ ] Provide multiple ground clips/points for scope probes
* [ ] Dedicated ground in close proximity to analog test points
* [ ] Test points on all power rails
* [ ] Test points on interesting signals which may need probing for bringup/debug

### Thermal

* [ ] Power estimates for all large / high power ICs
* [ ] Thermal calculations for all large / high power ICs
* [ ] Specify heatsinks as needed


## Layout Review 

### General

* [ ] [Schematic review](#schematic-review) complete and signed off, including pin swaps done during layout
* [ ] Layout DRC 100% clean

### Decoupling

* [ ] Decoupling caps as close to power pins as possible
* [ ] Low inductance mounting used for decoupling (prefer ViP if available, otherwise "[]8" shaped side vias

### DFM / yield enhancement

* [ ] All design rules within manufacturer's capability
* [ ] Minimize use of vias/traces that push fab limits
* [ ] Layer number markers specified to ensure correct assembly
* [ ] Fiducials present (on both sides of board) if targeting automated assembly
* [ ] Fiducial pattern asymmetric to detect rotated or flipped boards
* [ ] Soldermask/copper clearance on fiducials respected
* [ ] Panelization completed if required
* [ ] Teardrops added to PTH components / vias

### Footprints

* [ ] Confirm components are available in the selected package
* [ ] Verify schematic symbol matches the selected package
* [ ] Confirm pinout diagram is from top vs bottom of package
* [ ] PCB printed 1:1 on paper and checked against physical parts OR
* [ ] 3D models obtained (if available) and checked against footprints
* [ ] Soldermask apertures on all SMT lands and PTH pads

### Differential pairs
* [ ] Routed differentially
* [ ] Skew matched if required
* [ ] Correct clearance to non-coupled nets

### High-speed signals

* [ ] Sufficient clearance to potential aggressors
* [ ] Length matched if required
* [ ] Minimize crossing reference plane splits/slots or changing layers, use caps/stitching vias if unavoidable
* [ ] Double-check pad width on connectors and add plane cutouts if needed to minimize impedance discontinuities

### Power
* [ ] Minimal slots in planes from via antipads
* [ ] Sufficient width for planes/traces for required current

### Mechanical
* [ ] Confirm all connectors to other systems comply with the appropriate mechanical standard (connector orientation, key position, etc)
* [ ] LEDs, buttons, and other UI elements on outward-facing side of board
* [ ] Keep-outs around PCB perimeter, card guides, panelization mouse-bites, etc respected
* [ ] Stress-sensitive components (MLCC) sufficiently clear from V-score or mouse bite locations, and oriented to reduce bending stress
* [ ] Clearance around large ICs for heatsinks/fans if required
* [ ] Clearance around pluggable connectors for mating cable/connector
* [ ] Clearance around mounting holes for screws
* [ ] Plane keepouts and clearance provided for shielded connectors, magnetics, etc
* [ ] Confirm PCB dimensions and mounting hole size/placement against enclosure or card rack design
* [ ] Verify mounting hole connection/isolation
* [ ] Components not physically overlapping/colliding
* [ ] STEP file exported and mechanical fit confirmed with mechanical CAD model

### Thermal

* [ ] Thermal reliefs used for plane connections (unless via is used for heatsinking)
* [ ] Solid connections used to planes if heatsinking
* [ ] Ensure thermal balance on SMT chip components to minimize risk of tombstoning

### Solder paste

* [ ] No uncapped vias in pads (except low-power QFNs where some voiding is acceptable)
* [ ] QFN paste prints segmented
* [ ] Small pads 100% size, larger pads reduced to avoid excessive solder volume

### Solder mask

* [ ] Adequate clearance around pads
* [ ] NOTE: Default in KiCad is far too large, decrease to between 0 and 50um

### Silkscreen

* [ ] Text size within fab limits
* [ ] Text not overlapping drills or component pads
* [ ] Text removed entirely in, or moved outside of, high component/via density areas
* [ ] Designer details / OSHW logo / project name / graphical assets on board
* [ ] Traceability markings (rev, date, name, etc) provided
* [ ] PCB Fab marking location denoted (if required)
* [ ] Silkscreen box provided for writing/sticking serial number
* [ ] Text mirrored properly on bottom layer

Huge thanks to [Andrew Zonenberg](https://github.com/azonenberg/pcb-checklist) whose PCB checklist was modified for use in this document. 