#include <iostream>
#include "strutil.h"

int main() {
	int aCnt = 0;
	int eCnt = 0;
	int iCnt = 0;
	int oCnt = 0;
	int uCnt = 0;

	int theCnt = 0;
	int itCnt = 0;
	int wdCnt = 0;
	int notVowel = 0;

	String buf;
	String the("the");
	String it("it");

	while (std::cin >> buf) {
		++wdCnt;
		std::cout << buf << ' ' << std::endl;

		if (wdCnt % 12 == 0)
			std::cout << std::endl;
		if (buf == the || buf == "The")
			++theCnt;
		else
			if (buf == it || buf == "It")
				++itCnt;
		for (int ix = 0; ix < buf.size(); ++ix) {
			switch (buf[ix]) {
			case 'a': case 'A': ++aCnt; break;
			case 'e': case 'E': ++eCnt; break;
			case 'i': case 'I': ++iCnt; break;
			case 'o': case 'O': ++oCnt; break;
			case 'u': case 'U': ++uCnt; break;
			default: ++notVowel; break;
			}
		}
	}

	std::cout << "\n\n"
		  << "Words read: " << wdCnt << "\n\n"
		  << "the/The: " << theCnt << '\n'
		  << "it/It: " << itCnt << "\n\n"
		  << "non-vowels read: " << notVowel << "\n\n"
		  << "a: " << aCnt << '\n'
		  << "e: " << eCnt << '\n'
		  << "i: " << iCnt << '\n'
		  << "o: " << oCnt << '\n'
		  << "u: " << uCnt << std::endl;

	return 0;
}
