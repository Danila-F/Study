*******************************************************************************************************************************************
* Example of a batch file that runs AC analysis and saves images of the circuit, the analysis plot, two performance plots and a 3D plot.  *
* Load this batch1.bat file from the MC11 folder, select Run Script from the Analysis menu. Image files wil be placed in the DATA folder  *
*******************************************************************************************************************************************

BEGIN_COMMAND

	batch1.cir /a                                                                   ;Run AC analysis on batch1.cir
	/ic Page="Main" Output="batch1.jpg" 														  ;Save the Schematic Page Main as batch1.jpg
	/ia Page="a" Output="batch1_ac.jpg" 													     ;Save the AC analysis Page a as batch1_ac.jpg
	/ip Window="Peak_Y(RE(v(OUT)),1,1) vs Temperature" Output="batch1_acpf1.jpg"	  ;Save the Peak performance plot as batch1_acpf1.jpg
	/ip Window="Valley_Y(IM(v(OUT)),1,1) vs Temperature" Output="batch1_acpf2.jpg"  ;Save the Valley performance plot as batch1_acpf2.jpg
	/i3 Output="batch1_ac_3d.jpg" 														        ;Save the 3D plot as batch1_ac_3d.jpg. 
																											  ;Only one 3d Plot so no need to specify the Window
END_COMMAND



;$SpiceType=AMBIGUOUS
