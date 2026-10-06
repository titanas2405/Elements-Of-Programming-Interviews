#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>

//Write a program which takes an integer and returns the integre corresponding
//to the digits of the input written in reverse order. Example the reverse of 42 is 24

//sources https://en.cppreference.com/cpp/utility/from_chars

int Reverse(int x){
	//Takes input a number x and returns the reverse integer
	//X can be written as x = 10^n*a1 + 10^(n-1)*a2 +...+10*an-1 + an
	// To reverse :
	// 1. compute x % 10 to extract the last digit an
	// 2. result = result * 10 + an
	// 3. divide x with 10 and continue with the above steps until no x remains
	// Time Complexity O(n)
	
	
	//Definitions
	int result = 0;
	int x_remaining = x;
	
	//Loop until x_remaining becomes 0
	while (x_remaining !=0){
		//Applying the formula
		result = result* 10 + x_remaining % 10;
		//Go to next Digit
		x_remaining /= 10; 
	}
	return result;
}



std::optional<int>ParseInt(std::string_view text){
	//Takes input a string [std::string_view], parses and then outputs an optional int
	
	int value{};
	
	const auto [ptr,ec] = std::from_chars(text.data(),text.data()+text.size(),value);
	
	//Check for valid result
	if (ec!=std::errc() || ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range) return std::nullopt;
	
	return value; 
	
}


int main(int argc,char** argv){
	
	//Check Argument Count
	if (argc != 2){
		std::cout << "Usage ./Reverse <x> \n" ;
		return 1;
	}
	
	//Parsing the Argumnet
	std::optional<int> o_arg = ParseInt(argv[1]);
	
	//Check if value ex
	if (!o_arg){
		std::cout << "x must be a number\n" ;
		return 1;
	}
	
	//Getting the Values
	int x = *o_arg;
	
	//Output Outcome of Reverse
	std::cout << x << " -> " << Reverse(x) << "\n" ;
	
	return 0;
}
