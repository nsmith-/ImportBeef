# Setup CMSSW environment for a newer software release
# This should give access to most HEP software needed

pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc472/cms/cmssw/CMSSW_6_2_6
cmsenv
popd

source /afs/hep.wisc.edu/cms/dasu/Geant4/geant4.10.00.p01-install/bin/geant4.sh
export Geant4_DIR=/afs/hep/cms/dasu/Geant4/geant4.10.00.p01-install/lib64/Geant4-10.0.1
export PATH=/cms/sw/git/bin:$PATH
