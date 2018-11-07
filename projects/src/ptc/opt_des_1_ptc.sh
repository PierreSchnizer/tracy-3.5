#!/bin/sh

prm1=$1

#queue="ap-medium.q"
queue="ap-high.q"
#queue="test-medium.q"

t1="24:00:00"
t2="24:00:00"

#dir=`pwd`
dir=$HOME/git_repos/tracy-3.5_temp/projects/src/ptc

\rm opt_des_1_ptc.cmd.o*

qsub -l s_rt=$t1 -l h_rt=$t2 -q $queue -v lat_file=$prm1 $dir/opt_des_1_ptc.cmd
