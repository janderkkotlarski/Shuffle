#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <random>

std::vector <int> make_vectoid()
{
	std::vector <int> vectoid;
	
	for (int count{0}; count < 10; ++count)
	{
		vectoid.push_back(count);		
	}
	
	return vectoid;	
}

int vectoid_length(const std::vector <int>& vectoid)
{
	const int vectoid_size{static_cast <int> (vectoid.size())};
	assert(vectoid_size > 0);
	
	if (vectoid_size > 0)
	{
		return vectoid_size;
	}
	
	return -1;
}

void show_vectoid(const std::vector <int>& vectoid)
{
	const int vectoid_size{vectoid_length(vectoid)};

	if (vectoid_size > 0)
	{
		for (int count{0}; count < 10; ++count)
		{
			std::cout << '[' << vectoid[count] << ']';		
		}
		
		std::cout << '\n';
	}
}

void mash_vectoid(std::vector <int>& vectoid)
{
	const int vectoid_size{vectoid_length(vectoid)};

	if (vectoid_size > 1)
	{
		std::vector <std::vector <int>> vectids;
		const std::vector <int> dummy;
		
		int position{0};
		
		for (int count{0}; count < 2; ++count)
		{
			vectids.push_back(dummy);
			
			for (int count_2{0}; count_2 < vectoid_size/2 + (vectoid_size%2)*(1 - count); ++count_2)
			{
				vectids[count].push_back(vectoid[position]);
				++position;
			}
		}
		
		position = 0;
		
		for (int count{0}; count < vectoid_size/2 + vectoid_size%2; ++count)
		{
			for (int count_2{0}; count_2 < 2; ++count_2)
			{
				if ((count < vectoid_size/2 + 1) || (count_2 < 1))
				{
					vectoid[position] = vectids[count_2][count];
					++position;
				}
			}
		}		
	}
}

void exchange_vectoid(std::vector <int>& vectoid)
{
	const int vectoid_size{vectoid_length(vectoid)};

	if (vectoid_size > 1)
	{
		const unsigned int half_max{(static_cast<unsigned int>(-1))/2};
		std::random_device rand;
		
		const int coin{static_cast<int>(rand()/half_max)};
		
		const int stack{(vectoid_size/4 + 1 + coin)%vectoid_size};
		
		std::vector <int> vectid;
		
		for (int count{stack}; count < vectoid_size; ++count)
		{
			vectid.push_back(vectoid[count]);
		}
		
		for (int count{0}; count < stack; ++count)
		{
			vectid.push_back(vectoid[count]);
		}
		
		vectoid = vectid;
	}
}

void multi_mash_vectoid(std::vector <int>& vectoid, const int multi)
{
	assert(multi > 0);
	
	if (multi > 0)
	{
		for (int count{0}; count < multi; ++count)
		{
			mash_vectoid(vectoid);
			exchange_vectoid(vectoid);
		}
	}
}

int main()
{
	const std::string program_name{"Shuffle V0.1"};
	assert(program_name != "");
	
	const int multi{10};
	assert(multi > 0);
	
	std::vector <int> vectoid{make_vectoid()};
	
	show_vectoid(vectoid);
	
	char any_key{' '};
	
	while (any_key != '0')
	{
		std::cout << "Press any key and Enter to shuffle, 0 makes the program quit.\n";
		std::cin >> any_key;
		
		if (any_key != '0')
		{
			multi_mash_vectoid(vectoid, multi);
			
			show_vectoid(vectoid);
		}
	}
	
	return 0;
} 
