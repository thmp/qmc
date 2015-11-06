#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

int N;					// walkers
double *x;				// walker positions
double delta;			// step size

double frand() {
	return rand() / double(RAND_MAX);
}

double norm() {
	static int iset = 0;
	static double gset;
	double fac, rsq, v1, v2;
	if (iset == 0) {
		do {
			v1 = 2.0*frand()-1.0;
			v2 = 2.0*frand()-1.0;
			rsq = v1*v1 + v2*v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac = sqrt(-2.0*log(rsq)/rsq);
		gset = v1*fac;
		iset = 1;
		return v2*fac;
	} else {
		iset = 0;
		return gset;
	}
}

void init() {
	srand(time(NULL));

	N = 300;

	x = new double[N];
	for (int i = 0; i < N; i++) {
		x[i] = frand() - .5;
	}

	delta = 1;

}

double trial(double x, double alpha) { 
	return exp(-2 * alpha * x*x);
}

double weight(double xTrial, double x, double alpha) {
	return trial(xTrial, alpha) / trial(x, alpha);
}

double energy(double x, double alpha) {
	return alpha + x*x * (0.5 - 2*alpha*alpha);
}

void step_metropolis() {
	double alpha = 0.5;

	int n = int(frand()*N);
	double xTrial = x[n] + delta * norm();

	if (weight(xTrial, x[n], alpha) > frand()) {
		x[n] = xTrial;

	}
}

void step_montecarlo() {
	for (int i = 0; i < N; i++) {
		step_metropolis();
	}
}

int main(int argc, char* argv[]) {

	init();
	for (int i = 0; i < 1e4; i++) {
		step_montecarlo();
		if (i % 1000 == 0) {
			cout << i << endl;
		}
	}

	return 0;
}