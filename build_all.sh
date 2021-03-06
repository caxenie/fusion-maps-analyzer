#!/bin/sh
echo "Building Interacting Maps for Sensor Fusion Demo \n"
rm fusion-analyzer-data.log
cd core
echo "Building core ...\n"
make clean 
make
cd -
cd gui
echo "Building visualizer ...\n"
make clean 
make
cd -
echo "Build finished!\n"
echo "Starting demo ...\n"
mv gui/fusion_maps_gui .
mv core/fusion_maps_core .
./fusion_maps_gui
cd core/ && make clean 
cd - && cd gui/ && make clean && cd -
rm fusion_maps_gui fusion_maps_core


