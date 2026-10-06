#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>

//Given two positive integers, compute their quotinent, using only addition,substraction
//and shifting operations


unsigned NaiveDivide(unsigned x,unsigned y){
	//Takes input 2 unsigned numbers x,y and returns the quontinet of x/y
	//This is a brute force algorithm
	//We substract in each iteration y and
	//stop until the leftover of x is less than y
	//Time Complexity : O(2^n) [worst case, x = 2^n -1, y = 1]
	
	//Definitions
	unsigned result = 0;
	
	//Loop until x is less than y
	while(x>=y){
		
		//increament result
		++result;
		
		//remove from x *y
		x -= y;
	
	}
	
	return result;
}

unsigned Divide(unsigned x,unsigned y){
	//Takes input 2 unsigned numbers x,y and returns the quontinet of x/y
	//This is an optimized version of the naive divide algorithm
	//We find in each iteration the largest k s.t. 2^k*y <=x and
	//substract from x, 2^k*y and add to the result 2^k
	//We continue in this fashion until the leftover of x is less than y
	//Time Complexity : O(n) [worst case, x = 2^n - 1, y = 1]
	//power becomes n-1, x becomes 2^n - 2^(n-1) -1
	//continuing this until power becomes 0 
	
	
	//Definitions
	//Start power in largest value possible since in each iteration
	//we know that it will be smaller
	unsigned result = 0;
	int power = 32;
	unsigned long long y_power = static_cast<unsigned long long>(y) << power;
	
	//Loop until x is less than y
	while(x>=y){
		
		
		//Find Largest k s.t 2^k*y <=x
		while(y_power > x){
			y_power >>=1;
			--power;
		}
		
		//1U << power will result into 2^k
		result += 1U << power;
		
		//remove from x 2^k*y
		x -= y_power;
	}
	
	return result;
}


std::optional<std::uint32_t> ParseUnsigned(std::string_view text){
	// Takes input a string [std::string_view] and returns an optional uint32_t	
	
	std::uint32_t value{};
	const auto [ptr, ec] = std::from_chars(text.data(),  text.data() + text.size(), value);
	
	if (ec != std::errc{} || ptr != end) return std::nullopt;
	
	return value;
}

int main(int argc, char** argv) {
		
	//argument Count Check
	if (argc != 3) {
		std::cout << "Usage ./Quontinent <x> <y> \n" ;	
		return 1;
	}
	
	//Parse String to Optional 32 bit Unsigned Int 
	const std::optional<std::uint32_t> o_arg1 = ParseUnsigned(argv[1]);
	const std::optional<std::uint32_t> o_arg2 = ParseUnsigned(argv[2]);
	
	//Check if we have any value
	if (!o_arg1 || !o_arg2){ 
		std::cout << "either argument x-y is not number";
		return 1;
	}
	
	//Getting the Values
	std::uint32_t x = *o_arg1;
	std::uint32_t y = *o_arg2;
	
	//Check if y is 0
	if (y == 0){ 
		std::cout << "y must be >= 0 \n";
		return 1;
	}
	
	//Outputing Outcome For Naive Divide
    std::cout << "[N] Outcome: " << NaiveDivide(x,y) << "\n";
	
	//Outputing Outcome For Optimized Divide
    std::cout << "[O] Outcome: " <<  Divide(x,y) << "\n";
	
	return 0;
}
	
