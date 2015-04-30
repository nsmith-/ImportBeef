import ROOT

water = ROOT.TFile.Open('build/water.root')
meat  = ROOT.TFile.Open('build/meat.root')

wdepth = water.Get('1')
mdepth = meat.Get('1')
mdepth.SetLineColor(ROOT.kRed)

wrad = water.Get('9')
mrad = meat.Get('9')
mrad.SetLineColor(ROOT.kRed)

stack = ROOT.THStack()
stack.Add(wdepth, 'histex0')
stack.Add(mdepth, 'histex0')
stack.Draw('nostack')
ROOT.gPad.Print('depth_water_meat.root')

stack2 = ROOT.THStack()
stack2.Add(wrad, 'histex0')
stack2.Add(mrad, 'histex0')
stack2.Draw('nostack')
ROOT.gPad.Print('radius_water_meat.root')
