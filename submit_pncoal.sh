#!/bin/bash

vtag=v18sp0sn1
sigmap=0
sigman=1


njob=2
logpath="/scratch/negishi/gu180/pncoal/data/submitlog/${vtag}/"
codepath="/scratch/negishi/gu180/pncoal/data/slurmcodecopy/${vtag}/"
sourcepath="/scratch/negishi/gu180/pncoal/pncoal/"


mkdir -p $codepath
cp ${sourcepath}loader.C ${codepath}
cp ${sourcepath}filename_pncoal.h ${codepath}
cp ${sourcepath}Wigner.h ${codepath}
cp ${sourcepath}Particle.h ${codepath}
cp ${sourcepath}GetPN.h ${codepath}
cp ${sourcepath}GetDeuteron.h ${codepath}
cp ${sourcepath}GetTriton.h ${codepath}
cp ${sourcepath}GetInfo.h ${codepath}
cp ${sourcepath}RunCoalSingleVtag_template.C ${codepath}
cp ${codepath}RunCoalSingleVtag_template.C ${codepath}RunCoalSingleVtag.C

sed -i -e  "s@INSERTVTAG@"${vtag}@g ${codepath}RunCoalSingleVtag.C
sed -i -e  "s@INSERTNSP@"${sigmap}@g ${codepath}RunCoalSingleVtag.C
sed -i -e  "s@INSERTNSN@"${sigman}@g ${codepath}RunCoalSingleVtag.C



mkdir -p $logpath


for ijob in `seq 1 1  $njob`
do
	echo $ijob
	jobname=pncoal_${vtag}_job${ijob}
	echo $jobname
	#sbatch --job-name=$jobname -N 1 -n 1 -t 1:00:00 -A standby -o ${logpath}${jobname}.log -e ${logpath}${jobname}.err ./job_pncoal.sh $vtag  $ijob
	#sbatch --job-name=$jobname --nodes=1 -A standby -o ${logpath}${jobname}.log -e ${logpath}${jobname}.err ./job_pncoal.sh $vtag  $ijob
	sbatch --nodes=1 -A standby ./job_pncoal.sh $vtag  $ijob
done


