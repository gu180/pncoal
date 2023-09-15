#!/bin/bash

SLURM_JOB_PARTITION=standby

source /cvmfs/oasis.opensciencegrid.org/osg-software/osg-wn-client/3.5/current/el7-x86_64/setup.sh
export X509_USER_PROXY=/home/gu180/x509up_u607484

datapath="/scratch/negishi/gu180/pncoal/data/${vtag}/"


vtag=$1
ijob=$2

ncore=1
#iJob=$SLURM_JOB_NAME
iJob=ijob

for i in `seq 0 1 ${ncore}`
do
        echo i ${i}
	iCore=$i
        sh core_pncoal.sh $vtag  $iJob $iCore &
        sleep 1
done

wait


workpath="/scratch/negishi/gu180/pncoal/data/slurmworkshop/job${iJob}/"
echo $workpath
rm -r $workpath

