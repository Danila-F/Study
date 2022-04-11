********************************************************************************************************
* Example of a batch file that runs AC analysis and saves images of the circuit and the analysis plot  *
* Load this batch.bat file from the MC11 folder, select Run Script from the Analysis menu. Image files *
* and numeric output files will be placed in the DATA folder                                           *
********************************************************************************************************
BEGIN_COMMAND
	batch.cir                            ; Loads batch.cir.
	/ic Page="Main" Output="batch1.jpg"  ; Creates circuit image as batch1.jpg. 												    
   /a /def "ind 1" /NOF "batch1.out"    ; Runs AC with IND=1. Numeric output is in batch1.out
	/ia Page="a"  Output="batch1_ac.jpg" ; Creates AC plot image as batch1_ac.jpg. 												    
END_COMMAND

BEGIN_COMMAND
	batch.cir                            ; Loads batch.cir.
	/a /def "ind 2" /NOF "batch2.out"    ; Runs AC with IND=2. Numeric output is in batch2.out
	/ia Page="a"  Output="batch2_ac.jpg" ; Creates AC plot image as batch2_ac.jpg. 								       
END_COMMAND

BEGIN_COMMAND
	batch.cir                            ; Loads batch.cir.
	/a /def "ind 3" /NOF "batch3.out"    ; Runs AC with IND=3. Numeric output is in batch3.out
	/ia Page="a"  Output="batch3_ac.jpg" ; Creates AC plot image as batch3_ac.jpg. 								       
END_COMMAND




;$SpiceType=AMBIGUOUS
