#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

using namespace std;

class MyIniParser {
	string _fileName;
	map <string, map<string, string>> _fileMap;

public:
	MyIniParser(string iniFileName = "file.ini" ) {
		_fileName = iniFileName;
	}
	
	// Open and read file
	bool loadFromFile() {
		string spaces("[		[:space:][:blank:]\t\r\v]*");

		regex spacesLine("^" + spaces + "$");
		regex commentLine("^" + spaces + "[#;].*$");
		
		regex secLine("^"+spaces+"\\[.*\\]"+spaces+"$");
		regex varLine("^.+=.+$");

		// open file
		ifstream fs(_fileName, ios::in);

		if ( !fs ) {
			return false;
		}

		// read file
		string line, sec, var, val;

		// read every line
		while (!fs.eof()) {
			getline(fs, line);

			// Missing empty and comment lines
			if (regex_match(line, spacesLine) || regex_match(line, commentLine) ) {
				continue;
			}

			// Match section
			if (regex_match(line, secLine)) {
				int posBrace1 = line.find_first_of("[");
				int posBrace2 = line.find_last_of("]");
				
				sec = line.substr(posBrace1+1, posBrace2 - posBrace1 - 1);
			}
			// Match variable
			else  if (regex_match(line, varLine)) {
				int pos = line.find("=");
				
				var = line.substr(0, pos);
				val = line.substr(pos+1, line.length()-pos);
				
				_fileMap[sec][var] = val;
			}
		}

		return true;
	}

	// Get value by SECTION and KEY
	string getField(string section, string key, string defaultValue) {
		auto it = _fileMap.find(section);

		if (it != _fileMap.end()) {
			auto it = _fileMap[section].find(key);
			
			if (it != _fileMap[section].end()) {
				return _fileMap[section][key];
			}
		}

		return defaultValue;
	}
	
	// Get all sections
	vector<string> getSections() {
		vector<string> vecSections;
		
		for (auto i = _fileMap.begin(); i != _fileMap.end(); ++i) {
			vecSections.push_back(i->first);
		}

		return vecSections;
	}
	
	// Get all fields by SECTION
	vector<string> getFields(string section){
		// get section map
		auto it = _fileMap.find(section);
		
		if (it == _fileMap.end()) {
			return vector<string>();
		}
		// get fields
		vector<string> fields;
		for (auto i = it->second.begin(); i != it->second.end(); ++i) {
			fields.push_back(i->first);
		}

		return fields;
	}
};

int main(int argc, char* argv[])
{
	MyIniParser parser("example.ini");
	parser.loadFromFile();

	cout << parser.getField("server","host","default");

	return 0;
}