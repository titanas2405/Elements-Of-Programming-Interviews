#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>

//Write a program that takes in a double x and an integer y and returns x^y. You can ignore
//overflow and underflow

double NaivePower(double x, int y){
	//Takes as input a double x and an integer y and returns x^y
	//This is a brute force algorithm
	//Checking the sign of y:
	//	- Negative: Divide
	//  - Positive: Multiply
	//[Multiply Case] First we compute x * x
	//Then we compute x^2 * x
	//Then we compute x^3 * x
	//Until x^(y-1) * x
	//Time Complexity O(2^n). Assume multiplication/division take O(1)
	//Suppose y = 2^n. algorithm takes 2^n steps
	
	//Definitions
	double result = 1.0;
	int count = y;
	
	//Check if count is negative 
	if (count < 0) {
		count = -count;
		x = 1.0 / x;
	};
	
	//Loop from 0 to y and multiply/divide according to sign of y 
	for (int i = 0; i < count;i++){
			result = result * x;
	}
	
	
	return result;
}

double Power(double x, int y){
	//Takes as input a double x and an integer y and returns x^y
	//This is an optimized version of the naive power algorithm
	//Trick: break y into 2*k +1 [odd] or 2*k [even]
	//[Even] now we compute x^(2k)= (x^k)^2 which is 1 + k multiplications
	//[Odd] now we compute x^(2k+1) = (x^2k)*x = ((x^2)^k)*x which is 2 + k multiplications
	//If LSB of Y is 1 then we do result *= x; 
	//Because each time we divide y then we double the power with x*=x 
	//We use a while loop instead of recursion to skip overhead of function calls
	//Checking the sign of y:
	//	- Negative: Divide
	//  - Positive: Multiply
	//Time Complexity O(n). Assume multiplication/division take O(1)
	//Suppose y = 2^n. algorithm does at most twice multiplications
	

	//Definitions
	double result = 1.0;
	int power = y;
	
	//Check if count is negative 
	if (power < 0) {
		power = -power;
		x = 1.0 / x;
	};
	
	//While Loop until power becomes 0
	while(power != 0){
		//Check for LSB if it 1 for power
		if (power&1U){
			result *=x;
		}
		//Double the power of x
		x*=x;
		//Shift to next bit of Power
		power >>= 1;
	}
	
	return result;
}



std::optional<double>ParseDouble(std::string_view text){
	//Takes input a string [std::string_view], parses and then outputs an optional double
	
	double value{};
	const auto [ptr,ec] = std::from_chars(text.data(),text.data() + text.size(),value, 
										  std::chars_format::general );
	
	//Check for any errors 
	if (ec != std::errc() || ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range) return std::nullopt; 
	 
	return value;
}

std::optional<int>ParseInt(std::string_view text){
	//Takes input a string [std::string_view], parses and then outputs an optional int
	
	int value{};
	const auto [ptr,ec] = std::from_chars( text.data(),text.data() + text.size(),value,10);
	
	//Check for any errors 
	if (ec != std::errc() || ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range) return std::nullopt; 
	 
	
	return value;
}


int main(int argc,char**argv){
	
	//Argument Count Check
	if (argc!=3){
		std::cout <<"Usage: ./Power <x> <y> \n";
		return 1;	
	}
	
	//Parse String to Optional Double and Int 
	std::optional<double>o_arg1 = ParseDouble(argv[1]);
	std::optional<int>o_arg2 = ParseInt(argv[2]);
	
	//Check if we have any value
	if (!o_arg1 || !o_arg2){ 
		std::cout << "either argument x is not double or y is not int";
		return 1;
	}
	
	//Getting the Values
	double x = *o_arg1;
	int y = *o_arg2;
	
	
	//Outputing Outcome For Naive Power
    std::cout << "[N] Outcome: " << NaivePower(x,y) << "\n";
	//Outputing Outcome For Optimized Power
    std::cout << "[O] Outcome: " << NaivePower(x,y) << "\n";	
	
	
	return 0;	
}
