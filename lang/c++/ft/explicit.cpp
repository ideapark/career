template <class T1, class T2, class T3>
T1 sum(T2 op1, T3 op2) {
	return T1();
}

void manipulate(int (*pf)(int, char)) {
	/* ... */
}

void manipulate(double (*pf)(float, float)) {
	/* ... */
}

int main() {
	//manipulate(&sum); // ambigious
	manipulate(&sum<double, float, float>); // explicit specification

	return 0;
}
