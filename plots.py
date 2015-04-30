import ROOT

water = ROOT.TFile.Open('build/water.root')
meat  = ROOT.TFile.Open('build/meat.root')

wdepth = water.Get('1')
mdepth = meat.Get('1')

stack = ROOT.THStack()
stack.Add(wdepth, 'histex0')
stack.Add(mdepth, 'histex0')

stack.Draw('nostack')
