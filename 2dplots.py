import ROOT

elec = ROOT.TFile.Open('build/meat-electrons.root')
xray = ROOT.TFile.Open('build/meat-xrays.root')

ROOT.gStyle.SetTitleSize(0.04, "XYZ")

eprofile = elec.Get('2dprofile')
eprofile.Scale(1.e3)
eprofile.UseCurrentStyle()
eprofile.GetXaxis().SetTitle('Depth [mm]')
eprofile.GetYaxis().SetTitle('Beam scan profile [mm]')
eprofile.GetZaxis().SetTitle('Electron energy deposit [keV/mm^2]')
xprofile = xray.Get('2dprofile')
xprofile.Scale(1.e6)
xprofile.UseCurrentStyle()
xprofile.GetXaxis().SetTitle('Depth [mm]')
xprofile.GetYaxis().SetTitle('Beam scan profile [mm]')
xprofile.GetZaxis().SetTitle('X-Ray energy deposit [eV/mm^2]')

pad = ROOT.TCanvas("comparison", "comparison", 1200,600)
pad.Divide(2,1)
lpane = pad.cd(1)
lpane.SetRightMargin(.15)
eprofile.Draw('colz')
rpane = pad.cd(2)
rpane.SetRightMargin(.15)
xprofile.Draw('colz')

pad.Print('energy_profile.root')
