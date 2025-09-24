#include "headers.hpp"

void	strReplace(std::string &s, std::string &s1, std::string &s2);

int main(int ac, char **av) {

	if (ac != 4)
		return (0);
	std::string s;
	std::string fileName = av[1];
	std::string	s1 = av[2];
	std::string s2 = av[3];
	std::ifstream in(av[1]);

	if (in.is_open() == false) {
		std::cout << "The file does not exist" << std::endl;
		exit(1);
	}

	fileName.append(".replace");
	std::ofstream out(fileName.c_str());

	if (out.is_open() == false) {
		std::cout << "The file does not create" << std::endl;
		exit(1);
	}

	getline(in, s, '\0');
	strReplace(s, s1, s2);
	out << s;
	in.close();
	out.close();
	return (0);
}

void	strReplace(std::string &s, std::string &s1, std::string &s2) {
	int	idx;

	idx = 0;
	while (s.find(s1) != s.npos) {
		idx = s.find(s1);
		s.insert(idx, s2);
		s.erase(idx + s2.length(), s1.length());
	}
}