istream& operator>>(istream &is, SmallInt &si) {
	int ix;
	is >> ix;
	si = ix; // SmallInt::operator=(int)
	return is;
}

int SmallInt::rangeCheck(int i) {
	if (i & ~0377) {
		cerr << "\en***SmallInt range error: "
		     << i << " ***" << endl;
		exit(-1);
	}
	return i;
}
