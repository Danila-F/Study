void main (void) {
	static int k, x, b;
	static int y[10];
	
	k = 3;
	b = 1;
	
	
	for (x = 0; x < 10; x++) {
		y[x] = k * x + b;
	}

}
