// StructureRef.cpp -- using structure references

#include <iostream>
#include <string>

struct FreeThrows {
	std::string Name;
	int Made;
	int Attempts;
	float Percent;
};

void Display(const FreeThrows &FT);
void SetPc(FreeThrows &FT);
FreeThrows& Accumulate(FreeThrows &Target, const FreeThrows &Source);

int main(void)
{
	// partial initializations - remaining members set to 0
	FreeThrows One = { "Ifelsa Branch", 13, 14 };
	FreeThrows Two = { "Andor Knott", 10, 16 };
	FreeThrows Three = { "Minnie Max", 7, 9 };
	FreeThrows Four = { "Whily Looper", 5, 9 };
	FreeThrows Five = { "Long Long", 6, 14 };
	FreeThrows Team = { "Throwgoods", 0, 0 };

	// no initialzation
	FreeThrows Dup;

	SetPc(One);
	Display(One);

	Accumulate(Team, One);
	Display(Team);

	// use return value as argument
	Display(Accumulate(Team, Two));
	Accumulate(Accumulate(Team, Three), Four);
	Display(Team);

	// use return value in assignment
	Dup = Accumulate(Team, Five);
	std::cout << "Displaying team:\n";
	Display(Team);
	std::cout << "Displaying dup after assignment:\n";
	Display(Dup);

	SetPc(Four);

	// ill-advised assignment
	Accumulate(Dup, Five) = Four;
	std::cout << "Displaying dup after ill-advised assignment:\n";
	Display(Dup);

	return 0;
}

void Display(const FreeThrows &FT)
{
	using namespace std;
	cout << "Name: " << FT.Name << '\n';
	cout << " Made: " << FT.Made << '\t';
	cout << "Attempts: " << FT.Attempts << '\t';
	cout << "Percent: " << FT.Percent << '\n';
}

void SetPc(FreeThrows &FT)
{
	if (FT.Attempts != 0)
		FT.Percent = 100.0f * float(FT.Made)/float(FT.Attempts);
	else
		FT.Percent = 0;
}

FreeThrows& Accumulate(FreeThrows &Target, const FreeThrows &Source)
{
	Target.Attempts += Source.Attempts;
	Target.Made += Source.Made;
	SetPc(Target);
	return Target;
}
