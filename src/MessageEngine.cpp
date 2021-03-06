/*
Copyright © 2011-2012 Thane Brimhall

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

/**
 * class MessageEngine
 *
 * The MessageEngine class loads all of FLARE's internal messages from a configuration file
 * and returns them as human-readable strings.
 *
 * This class is primarily used for making sure FLARE is flexible and translatable.
 */

#include "GetText.h"
#include "SharedResources.h"
#include "Settings.h"
#include <sstream>

using namespace std;

MessageEngine::MessageEngine() {
	GetText infile;
	for (unsigned int i = 0; i < mods->mod_list.size(); i++) {
		string path = PATH_DATA + "mods/" + mods->mod_list[i] + "/languages/";
		if (infile.open(path + "engine." + LANGUAGE + ".po")) {
			while (infile.next()) {
				messages.insert(pair<string,string>(infile.key, infile.val));
			}
		    infile.close();
		}
		if (infile.open(path + "data." + LANGUAGE + ".po")) {
			while (infile.next()) {
				messages.insert(pair<string,string>(infile.key, infile.val));
			}
		    infile.close();
		}

	}
}
/*
 * Each of the get() functions returns the mapped value
 * They differ only on which variables they replace in the string - strings replace %s, integers replace %d
 */
string MessageEngine::get(const string& key) {
	string message = messages[key];
	if (message == "") message = key;
	return message;
}

string MessageEngine::get(const string& key, int i) {
	string message = messages[key];
	if (message == "") message = key;
	size_t index = message.find("%d");
	if (index != string::npos) message = message.replace(index, 2, str(i));
	return message;
}

string MessageEngine::get(const string& key, const string& s) {
	string message = messages[key];
	if (message == "") message = key;
	size_t index = message.find("%s");
	if (index != string::npos) message = message.replace(index, 2, s);
	return message;
}

string MessageEngine::get(const string& key, int i, const string& s) {
	string message = messages[key];
	if (message == "") message = key;
	size_t index = message.find("%d");
	if (index != string::npos) message = message.replace(index, 2, str(i));
	index = message.find("%s");
	if (index != string::npos) message = message.replace(index, 2, s);
	return message;
}

string MessageEngine::get(const string& key, int i, int j) {
	string message = messages[key];
	if (message == "") message = key;
	size_t index = message.find("%d");
	if (index != string::npos) message = message.replace(index, 2, str(i));
	index = message.find("%d");
	if (index != string::npos) message = message.replace(index, 2, str(j));
	return message;
}

// Changes an int into a string
string MessageEngine::str(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}
