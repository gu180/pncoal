#!/bin/bash

vtag=$1
iJob=$2
iCore=$3

sourcepath="/scratch/negishi/gu180/pncoal/data/slurmcodecopy/${vtag}/"
workpath="/scratch/negishi/gu180/pncoal/data/slurmworkshop/job${iJob}/core${iCore}/"

mkdir -p $workpath

cp ${sourcepath}loader.C ${workpath}
cp ${sourcepath}filename_pncoal.h ${workpath}
cp ${sourcepath}Wigner.h ${workpath}
cp ${sourcepath}Particle.h ${workpath}
cp ${sourcepath}GetPN.h ${workpath}
cp ${sourcepath}GetDeuteron.h ${workpath}
cp ${sourcepath}GetTriton.h ${workpath}
cp ${sourcepath}GetInfo.h ${workpath}
cp ${sourcepath}RunCoalSingleVtag.C ${workpath}


datapath="/scratch/negishi/gu180/pncoal/data/${vtag}/"
mkdir -p ${datapath}nucleon
mkdir -p ${datapath}deuteron
mkdir -p ${datapath}triton

cp ${workpath}nucleon_${vtag}.root ${datapath}/nucleon/nucleon_${vtag}_${iJob}_${iCore}.root
cp ${workpath}deuteron_${vtag}.root ${datapath}/deuteron/deuteron_${vtag}_${iJob}_${iCore}.root
cp ${workpath}triton_${vtag}.root ${datapath}/triton/triton_${vtag}_${iJob}_${iCore}.root



