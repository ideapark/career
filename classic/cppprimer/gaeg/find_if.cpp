#include <algorithm>
#include <list>
#include <set>
#include <string>
#include <iostream>

using namespace std;

class OurFriends {
public:
    bool operator()(const string &str) {
        return friendset.count(str);
    }
    static void FriendSet(const string *fs, int count) {
        copy(fs, fs+count, inserter(friendset, friendset.end()));
    }
private:
    static set<string, less<string> > friendset; 
};

set<string, less<string> > OurFriends::friendset;

int main(int argc, char *argv[])
{
    string Pooh_friends[] = { "Piglet", "Tigger", "Eyeore", };
    string more_friends[] = { "Quasimodo", "Chip", "Piglet", };
    list<string> lf(more_friends, more_friends+3);

    OurFriends::FriendSet(Pooh_friends, 3);
    list<string>::iterator our_mutual_friend;
    our_mutual_friend = find_if(lf.begin(), lf.end(), OurFriends());

    if (our_mutual_friend != lf.end())
        cout << "Ah, imagine our friend "
            << *our_mutual_friend
            << " is also a friend of Pooh.\n";
    return 0;
}
