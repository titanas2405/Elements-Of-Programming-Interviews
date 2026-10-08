#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>
#include <string>
#include <cmath>
#include <vector>

//Write a program that takes an array A and an index i into A, and rearranges the elements such that all the 
//elements less than A[i] (the "pivot") appear first, followed by elements equal to the pivot,followed by
//elements greater than the pivot

//sources https://en.cppreference.com/cpp/utility/from_chars
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c	

typedef enum {RED, WHITE, BLUE} Color;

void DutchFlagPartition(int pivot_index,std::vector<int>& A){
	
	return;
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
void PrintVector(std::vector<T>& V) {
	//Takes input a vector and prints it
	
	//Iterate through all vector and print all elements
	for (const auto& e : V) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

int main(int argc,char ** argv){
	
	//Check Argument Count
	if (argc !=3){
		std::cout << "Usage: ./Palindrome <Array> <i>";
		return 1;
	}
	
	//Parsing the Argumnets
	std::vector<std::string> o_array = Split(argv[1],",");
	std::optional<int> o_i = ParseInt(argv[2]);
	
	           
	//Check if value exist
	if (!o_i){
		std::cout << "i must be a number or in range\n" ;
		return 1;
	}
	
	//Getting the Values
	int i = *o_i;
	std::vector<int> ints;
	
	for (const auto& s : o_array) {
		std::optional<int> n = ParseInt(s);
		if (!n) {
			std::cout << "Error parsing '" << s << "' into a number\n";
			return 1;
		}
		ints.push_back(*n);
	}
				   
	PrintVector(ints);
			
	std::cout << "i :" << i << "\n" ;
	
}
