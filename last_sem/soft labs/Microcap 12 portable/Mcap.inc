***Micro-Cap***
Global User Defines...available to all circuits
.MODEL PULSE22 PUL (VZERO=7 VONE=5 P1=100N P2=100N P3=500N P4=500N P5=1U)
*Diode power dissipation
.define DPWR(D) I(D)*V(D)
*BJT power dissipation
.define BPWR(Q) IC(Q)*VCE(Q)+IB(Q)*VBE(Q)
*FET power dissipation...for MOSFETS, JFETS, GaAsFets
.define FPWR(M) ID(M)*VDS(M)

*Diode power dissipation warning
.define HOTD(D,MAX) IF((V(D)*I(D)>MAX),1,0)
*BJT power dissipation warning
.define HOTB(Q,MAX) IF((VCE(Q)*IC(Q)+IB(Q)*VBE(Q)>MAX),1,0)
*FET power dissipation warning
.define HOTF(M,MAX) IF((VDS(M)*ID(M)>MAX),1,0)
**************

*Placement of performance limit templates for PCI
.define Low3Min import(Low3Min.out,Low3Thres)
.define High3Max import(High3Max.out,High3Thres)

*Placement of threshold limits for LVDS designs
.define LowLVDS import(LowLVDS.out,LowLimit)
.define HiLVDS import(HiLVDS.out,HiLimit)
.define LimtLVDS import(LimtLVDS.out,LVDSLimits)


*MODELING SKIN EFFECT

*Some miscellaneous information
*Soft annealed copper resistivity is 1.75745E-8 Ohm*meter @20C; add 3.7% for medium hard drawn wire
*Aluminum resistivity is ~2.83E-8 Ohm*meter
*Resistance of 1 meter #22 AWG copper wire at 25C is 0.056193 ohms.
*TCR of copper is ~0.0039 per degree Centigrade.
*For American Wire Gage (AWG), the ratio of the next larger gage wire diameter to any given wire size is 1.1229322.
*For two gages larger, the square of the ratio is ~1.25
*For six gages larger, ~2.0
*For 10 gages larger, ~10
*The cross sectional area, weight, and DC restance are approximately doubled or halved for every three gage numbers.
*The wire diameter is approximately doubled or halved for every six gage numbers.
*The cross sectional area, weight, and DC resistance are approximately 10:1 or 1:10 for every 10 gage numbers.
*The weight in pounds of 1000 feet of a given wire size is approximate equal to the diameter in mils of a wire twice the original gage.
  *For example, #8 AWG doubled is #16 AWG, which has a 50.8-mil diameter.  1000 feet #8 AWG actually weighs 50 pounds.

*For AC Analysis using round wires:
.define SkinAC(DCres,resistivity,RelPerm,radius) ((PI*radius*radius)/((PI*radius*radius)-PI*(radius-SkinDepthAC(resistivity,RelPerm))**2))*DCres
.define SkinDepthAC(resistivity,RelPerm) 503.3*(sqrt(resistivity/(RelPerm*F)))

*For Transient Analysis:
.define SkinTR(DCres,resistivity,RelPerm,radius,Freq) ((PI*radius*radius)/((PI*radius*radius)-PI*(radius-SkinDepthTR(resistivity,RelPerm,Freq))**2))*DCres
.define SkinDepthTR(resistivity,RelPerm,Freq) 503.3*(sqrt(resistivity/(RelPerm*Freq)))
