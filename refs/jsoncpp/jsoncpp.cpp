#include <string>
#include <fstream>
#include <iostream>

#include <json/json.h>

using namespace std;

int main(void)
{
	Json::Value root;
	Json::Reader reader;

	ifstream ifs("input.json");

	if (!reader.parse(ifs, root)) {
		cout << reader.getFormattedErrorMessages();
		ifs.close();
		return -1;
	}
	ifs.close();

	string encoding = root.get("encoding", "UTF-8").asString();
	cout << encoding << endl;

	const Json::Value plugins = root["plug-ins"];
	for (unsigned int index = 0; index < plugins.size(); ++index)
		cout << plugins[index].asString() << endl;

	cout << root["indent"].get("length", 3).asInt() << endl;
	cout << root["indent"].get("use_space", true).asBool() << endl;

	root["encoding"] = "ANSI";
	root["indent"]["length"] = 9;
	root["indent"]["use_space"] = false;

	Json::StyledWriter writer;
	cout << writer.write(root) << endl;

	return 0;
}
