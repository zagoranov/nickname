#include <iostream>
#include "RadixTree.h"

//-----------------------------------------------------------------------------------------

int main()
{
	RadixTree rt;

	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.empty())         
			break;
		rt.Add(line.c_str());
		rt.ShowPretty();
	}

	rt.ShowUnique();

	//std::system("pause");
}


/*rt.Add("aleksey");
rt.Add("sasha");
rt.Add("aleks");
rt.Add("alek");
rt.Add("alesha");
rt.Add("maxim");*/
