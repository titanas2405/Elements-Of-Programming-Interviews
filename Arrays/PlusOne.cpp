#include <algorithm>
#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>
#include <string>
#include <cmath>
#include <vector>
#include <list>

//Write a program which takes as input an array of digits encoding a decimal number D and updates the array to
//represent the number D + 1. For example, if the input is <1,2,9> then you should update the array to <1,3,0>.
//Your algorithm should work even if it is implemented in a language that has finite-percision arithmetic 

//sources https://en.cppreference.com/cpp/utility/from_chars
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c	
//https://www.w3schools.com/cpp/cpp_list.asp

int DigitsToInt(const std::vector<int>& digits) {
    //Takes input a vector of ints (digits) and returns the corresponding number in base 10
    // Example: {1, 2, 3} returns 123.
    
    //Definitions
    int number = 0;

	//Iterate all digits and multiply by 10 each time and add teh digit
    for (int digit : digits) number = number * 10 + digit;

    return number;
}


std::vector<int> IntToDigits(int number) {
	//Takes input a number and returns the corresponding vector containing digits
    // Example: 1,2,3 returns {1, 2, 3}.
    //we just extract the first digit
	// first digit = x / 10^(num_digits -1)
	// where num_digits = floor ( log_10(x)) + 1;
	//and push it into the vector of digits
    //We hold a mask variable m that we divide by 10 in each iteration
	//since we remove 1 digit from number 
	
	if (number == 0) return {0};
	
	
	//Definitions
	int num_digits = static_cast<int>(log10(number))+1;
	int m = static_cast<int>(pow(10,num_digits-1)); 
	
	//While loop until no number left
	std::vector<int> digits;
	while (number){
		//Push the fisrt digit of number calculated with mask to digits
		digits.push_back(number/m);
		
		//Remove the first digit with mask
        number%=m;
        
        //Update mask
        m/=10;
	}

    return digits;
}


std::vector<int> NaivePlusOne(std::vector<int>A){
	//takes as input an array of digits encoding a decimal number D and updates the array to
	//represent the number D + 1.
	//This is a naive algorithm
	//We turn the vector to an int. Add 1, and then turn it back to vector and return it
	// Time complexity O(n)
	return IntToDigits(DigitsToInt(A)+1);
}


std::vector<int> PlusOne(std::vector<int>A){
	//takes as input an array of digits encoding a decimal number D and updates the array to
	//represent the number D + 1.
	//This is an optimized version of the Naive PlusOne
	//We manipulae the digits of Array directly
	//Add to the last digit 1
	//From school addition:
	//In case a digit becomes ten we reset to 0 and add 1 to next digit
	//Do this until no more digits or digit + 1 is less than 10
	//At end we check if the last digit is 10. In the case of being 10, we
	//increase the vector and insert 1 at end to count for the overflow
	
	//Add 1 to the first digit
	++A.back();
	
	//Iterate array and in a ripple way count for carry
	for (int i = A.size()-1;i>0 && A[i] == 10;--i){
		
		//reset
		A[i] = 0;
		
		//add 1 to next digit
		++A[i-1];	
	}
	
	//Check last digit for overflow
	if (A[0] == 10){
		
		//reset
		A[0] = 0;
		
		//insert 1 at start
		A.insert(A.begin(),1);
	}
	
	return A;
}



std::optional<int>ParseInt(std::string_view text){
	//Takes input a string [std::string_view], parses and then outputs an optional int
	
	int value{};
	const auto [ptr,ec] = std::from_chars( text.data(),text.data() + text.size(),value,10);
	
	//Check for any errors 
	if (ec != std::errc() || ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range) return std::nullopt; 
	 
	
	return value;
}

std::vector<std::string> Split(std::string s, const std::string& delimiter) {
	//Takes input a ve and a delimeter and returns the splitted values from string using the delimeter
	
	//Definitions
	std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    
    //Loop until no new token is found until delimeter
	while ((pos = s.find(delimiter)) != std::string::npos) {
        //Token is the substring from 0 to the position of the last char
        //of the token
        token = s.substr(0, pos);
        
        //insert to tokens the token
        tokens.push_back(token);
        
        //remove the token and forward to next token 
        s.erase(0, pos + delimiter.length());
    }	
    //insert any leftover from string
    tokens.push_back(s);
	
	return tokens;
}




template <typename T> 
void PrintVector(const std::vector<T>& V) {
	//Takes input a vector and prints it
	
	//Iterate through all vector and print all elements
	for (const auto& e : V) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

int main(int argc,char ** argv){
	
	//Check Argument Count
	if (argc !=2){
		std::cout << "Usage: ./PlusOne <Array>\n";
		return 1;
	}
	
	//Parsing the Argumnets
	std::vector<std::string> o_array = Split(argv[1],",");
	           
	
	//Getting the Values
	std::vector<int> ints;
	
	//Iterationg the vector
	for (const auto& s : o_array) {
		//Parsing
		std::optional<int> n = ParseInt(s);
		if (!n) {
			std::cout << "Error parsing '" << s << "' into a number\n";
			return 1;
		}
		
		if (*n < 0 ||  *n >9) {
			std::cout << "Digits must be in range [0,9] \n";
			std::cout << "Error digit is "<<*n<<"\n";
			return 1;
		}
		ints.push_back(*n);
	}

		
	//Printing the vector before 
	//PrintVector(ints);
	
	//std::cout << "Number :" << << "\n" ;
	
	std::vector<int> v = PlusOne(ints);
	PrintVector(v);
	
	
	//Applying optimized algorithm 
	//OptimizedDutchFlagPartition(i,ints);
	
	//Printing the vector after
	//PrintVector(ints);
	
	

}
