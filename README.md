# Template Hardware Project

## Generate production files
`make`

* generates zipped gerbers, BOM, and iBOM PnP file

## Init Repo
* Due to GitHub template not supporting submodules yet, the below process is required upon first use to configure.
```
git clone git@github.com:joshajohnson/hardware-template.git
mv hardware-template project-name
cd project-name
make init
```

* Configure new git repo

## Begin a new project / board revision
`make new NAME="project-name" VERSION="version" DESIGNER="Your Name"`

* `NAME` is the file name of project and is required, no spaces allowed
* `VERSION` is optional and defaults to `0.1`, must be unique
* `DESIGNER` is optional and defaults to `Josh Johnson`

## Generate gerbers
`make gerb` 

* requires python3 and a small number of dependencies

## Generate BOM
`make bom`

* utilises custom BOM format found in `scripts/josh_bom.py`
* requires dependancy to be installed to global scope `pip3 install kicad_netlist_reader`

## Generate InteractiveHTMLBom
`make pnp`

* requires [InteractiveHTMLBom](https://github.com/openscopeproject/InteractiveHtmlBom) to be installed in `~/.kicad_plugins/`
* generates ibom according to settings from pcbnew

## Panelise a board
`make panel`

* Requires `*.kicad_pcb` file to be located at `hardware/version/panel`
* Utilises [kicad-util](https://gitlab.com/dren.dk/kicad-util), which requires java to be installed

## Generate gerbers for panel
`make panel-gerb` 

* Requires `output.project-name.kicad_pcb` file to be located at `hardware/version/panel`


