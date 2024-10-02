//
// Created by majoramari on 10/2/24.
//

#ifndef READER_H
#define READER_H
#include <iostream>

using namespace std;

namespace reader {
	inline string file_name() {
		string file_name;
		cout << "Enter the file name: ";
		cin >> file_name;
		return file_name;
	}
}

#endif //READER_H
