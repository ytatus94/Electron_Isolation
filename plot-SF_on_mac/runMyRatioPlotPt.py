#!/usr/bin/python

import os

#Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
#Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose",
#       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"]
Menu =["TightLLHMC15_v8", "MediumLLHMC15_v8", "LooseAndBLayerLLHMC15_v8"]
Iso = ["isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]
       

for arg1 in Menu:
  for arg2 in Iso:
  #for arg3 in range(1, 21):
    for arg3 in [12, 15, 18, 19]:
      os.system('root -b -q myRatioPlotPt.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\",' + str(arg3) + ')"')
