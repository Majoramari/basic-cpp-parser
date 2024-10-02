#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

enum class TokenType {
	IDENTIFIER,
	INTEGER,
	FLOAT,
	STRING,
	KEYWORD,
	OPERATOR,
	PUNCTUATOR
};

struct Token {
	string value;
	TokenType type;
};

TokenType tokenize(const string &word) {
	vector<string> keywords = {"for", "while", "if", "else", "print", "string"};

	if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
		return TokenType::KEYWORD;
	}

	if (regex_match(word, regex("[A-Za-z_][A-Za-z0-9_]*"))) {
		return TokenType::IDENTIFIER;
	}

	if (regex_match(word, regex("[0-9]+"))) {
		return TokenType::INTEGER;
	}

	if (regex_match(word, regex("[0-9]+\\.[0-9]+"))) {
		return TokenType::FLOAT;
	}

	if (regex_match(word, regex("\".*\""))) {
		return TokenType::STRING;
	}

	vector<string> operators = {"+", "-", "*", "/", "=", "%"};

	if (find(operators.begin(), operators.end(), word) != operators.end()) {
		return TokenType::OPERATOR;
	}

	return TokenType::PUNCTUATOR;
}

vector<Token> parse_file(const string &file_path) {
	ifstream file(file_path);

	if (!file.is_open())
		throw runtime_error("Could not open the file!");

	string word;
	vector<Token> tokens;
	while (file >> word) {
		Token token = {
			word,
			tokenize(word)
		};
		tokens.push_back(token);
	}

	file.close();

	return tokens;
}

void print_tokens(const vector<Token> &tokens) {
	for (const auto &[value, type]: tokens) {
		cout << value << " ";
		switch (type) {
			case TokenType::KEYWORD: cout << "Keyword";
				break;
			case TokenType::IDENTIFIER: cout << "Identifier";
				break;
			case TokenType::INTEGER: cout << "Integer";
				break;
			case TokenType::FLOAT: cout << "Float";
				break;
			case TokenType::STRING: cout << "String";
				break;
			case TokenType::OPERATOR: cout << "Operator";
				break;
			case TokenType::PUNCTUATOR: cout << "Punctuator";
				break;
		}
		cout << endl;
	}
}

int main() {
	const string file_path = "code.txt"; // read_file_name();
	const vector<Token> tokens = parse_file(file_path);
	print_tokens(tokens);
	return 0;
}
