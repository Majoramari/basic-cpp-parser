#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
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

TokenType classify_token(const string &token) {
	vector<string> keywords = {
		"for", "while", "if",
		"else", "print", "string",
		"int", "float", "true",
		"false", "and", "or",
		"not", "return"
	};

	if (regex_match(token, regex("[A-Za-z_][A-Za-z0-9_]*")))
		return TokenType::IDENTIFIER;

	if (regex_match(token, regex("[0-9]+")))
		return TokenType::INTEGER;

	if (regex_match(token, regex("[0-9]+\\.[0-9]+")))
		return TokenType::FLOAT;

	if (regex_match(token, regex("\".*\"")))
		return TokenType::STRING;

	if (ranges::find(keywords, token) != keywords.end())
		return TokenType::KEYWORD;

	if (
		vector<string> operators = {"+", "-", "*", "/", "=", "%"};
		ranges::find(operators, token) != operators.end()
	)
		return TokenType::OPERATOR;

	return TokenType::PUNCTUATOR;
}

vector<Token> tokenize(const string &line) {
	vector<Token> tokens;

	// Regular expression that matches tokens:
	// - floating point numbers (123.456)
	// - integers (123)
	// - strings ("hello world")
	// - identifiers (earth)
	// - operators (==, !=, <=, >=, +, -, *, /, =, %)
	// - punctuates (;, (, ), ,)
	const regex token_pattern(R"([0-9]+\.[0-9]+|[0-9]+|".*?"|[A-Za-z_][A-Za-z0-9_]*|==|!=|<=|>=|[+\-*/=%;(),])");
	sregex_iterator iter(line.begin(), line.end(), token_pattern);
	const sregex_iterator end;

	while (iter != end) {
		string token_value = iter->str();
		Token token;
		token.value = token_value;
		token.type = classify_token(token_value);
		tokens.push_back(token);
		++iter;
	}

	return tokens;
}

void parse_file(const string &file_path) {
	ifstream file(file_path);
	string line;
	vector<Token> tokens;

	while (getline(file, line)) {
		vector<Token> line_tokens = tokenize(line);
		tokens.insert(tokens.end(), line_tokens.begin(), line_tokens.end());
	}

	for (const auto &[token_value, token_type]: tokens) {
		switch (token_type) {
			case TokenType::IDENTIFIER: cout << "Identifier";
				break;
			case TokenType::INTEGER: cout << "Integer";
				break;
			case TokenType::FLOAT: cout << "Float";
				break;
			case TokenType::STRING: cout << "String";
				break;
			case TokenType::KEYWORD: cout << "Keyword";
				break;
			case TokenType::OPERATOR: cout << "Operator";
				break;
			case TokenType::PUNCTUATOR: cout << "Punctuator";
				break;
		}
		cout << ": " << token_value << endl;
	}
}

int main() {
	const string file_path = "code.txt";
	parse_file(file_path);
	return 0;
}
