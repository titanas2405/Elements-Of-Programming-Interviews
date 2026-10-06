#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>
#include <string>
#include <cmath>

//Write a program that takes an integer and determines if that integer's representation
//as a decimal is a palindrome

//sources https://en.cppreference.com/cpp/utility/from_chars

bool NaiveIsPalindrome(int x){
	//Takes input an integer x and returns true if it is a Palindrome, false otherwise
	//This is a brute force algorithm
	//If x is negative, then it is not a Palindrom
	//If x is 0, then it is a Palindrome
	//We turn the absolute value of the integer into a string.
	//The iterate the string, comparing start and finish and 
	//worinking inwards, up to the midpoint
	//Time complexity is O(n)
	
	//Checking for the 2 cases
	if (x < 0) return false;
	if (x == 0) return true;
	
	//Get string represantation of x
	std::string str = std::to_string(x);
	
	//Iterate to the mid point string
	for (long unsigned int i = 0; i < str.size() / 2; i++) {
		//Check for missmatch
		if (str[i]!=str[str.size()-1 -i]) return false;
	}
	
	return true;
}


bool IsPalindrome(int x){
	//Takes input an integer x and returns true if it is a Palindrome, false otherwise
	//This is an optimized algorithm of NaiveIsPalindrome
	//Instead of Converting into a string and then comparing
	//we just extract the MSB and LSB
	// LSB = x % 10
	// MSB = x / 10^(num_digits -1)
	// where num_digits = floor ( log_10(x)) + 1;
	//We iterate until the midpoint of number
	//If MSB is not equal to LSB we return False
	//Otherwise Remove MSB and LSB and continue 
	//We hold a mask variable m that we divide by 100 in each iteration
	//since we remove 2 digits from x
	//Time complexity O(n)
	
	//Checking for the 2 cases
	if (x < 0) return false;
	if (x == 0) return true;
	
	//Definitions
	int num_digits = static_cast<int>(floor(log10(x)))+1;
	int m = static_cast<int>(pow(10,num_digits-1));
	
	//Iterattion to the mid point of number
	for (int i = 0; i < (num_digits)/2;i++){
		
		if (x/m != x%10){
			return false;
		}
		
		//Remove the MSB from x
		x %=m;
		
		//Remove the LSB from x
		x /= 10;
		
		//Removed MSB and LSB so we have to devide by 100
		m /= 100;
	}	
	
	return true;
}

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



bool AlternativeIsPalindrome(int x){
	//Takes input an integer x and returns true if it is a Palindrome, false otherwise
	//This is an alternative version of optimized algorithm of NaiveIsPalindrome
	//We use the reverse function to xompute the reverse of x 
	// Then Compare reverse x with x
	// Using the Reverse Function from Reverse.cpp
	//Time Complexity O(n)
	
	//Checking for the 2 cases
	if (x < 0) return false;
	if (x == 0) return true;
	

	return Reverse(x) == x ;
}



std::optional<int>ParseInt(std::string_view text){
	//Takes input a string [std::string_view], parses and then outputs an optional int
	
	int value{};
	const auto [ptr,ec] = std::from_chars( text.data(),text.data() + text.size(),value,10);
	
	//Check for any errors 
	if (ec != std::errc() || ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range) return std::nullopt; 
	 
	
	return value;
}

int main(int argc,char ** argv){
	
	//Check Argument Count
	if (argc !=2){
		std::cout << "Usage: ./Palindrome <x>";
		return 1;
	}
	
	//Parsing the Argumnet
	std::optional<int> o_arg = ParseInt(argv[1]);
	
	//Check if value ex
	if (!o_arg){
		std::cout << "x must be a number or in range\n" ;
		return 1;
	}
	
	//Getting the Values
	int x = *o_arg;
	
	//Output if x is Palindrome from NaiveIsPalindrome
	std::cout << "[N] Is x a Palindrome :" << NaiveIsPalindrome(x) << "\n" ;
	//Output if x is Palindrome from optimized IsPalindrome
	std::cout << "[o] Is x a Palindrome :" << NaiveIsPalindrome(x) << "\n" ;
	//Output if x is Palindrome from altrenative IsPalindrome
	std::cout << "[o] Is x a Palindrome :" << NaiveIsPalindrome(x) << "\n" ;

}
