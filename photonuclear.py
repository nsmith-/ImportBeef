import ROOT

hist = ROOT.TH1F('hist', 'hist;Energy [MeV];#sigma [mb]', 100, 0, 15.)

# first, do ./build/runPhotoNuc > xs.txt

with open('xs.txt') as f :
    for line in f :
        if ',' in line :
            v = line.split(',')
            hist.Fill(float(v[0]), float(v[1]))

hist.Draw()
ROOT.gPad.Print('photonuclear.root')
