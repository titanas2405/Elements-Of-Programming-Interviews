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
#include <fstream>
#include <exception>
#include <memory>

//Write a program which takes two arrays representing integers, and returnrs an integer reresenting their 
//product. For example, since 193707721 * -7618257287 = -147573952589676412927, if inputs are 
//<1,9,3,7,0,7,7,2,1> and <-7,6,1,8,2,5,7,2,8,7>, your function should 
//return <-1,4,7,5,7,3,9,5,2,5,8,9,6,7,6,4,1,2,9,2,7>

//sources https://en.cppreference.com/cpp/utility/from_chars
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c	
//https://www.w3schools.com/cpp/cpp_list.asp

std::vector<int> Multiply(std::vector<int> a,std::vector<int> b){
	//Takes input two arrays representing integers, and returnrs an integer reresenting their 
	//product. 
	//The algorithm follows a school grade multipliction algorithm
	//The size of the result is at most n + m where n and m are the number of 
	//	digits of the 2 numbers
	//We apply the algorithm on the positive numbers and then put the negative sign if needed
	//We first reverse the numbers, because the multiplication starts from end
	//a can be written as a = 10^n*an + 10^(n-1)*an-1 +...+10*a1 + a0
	//b can be written as b = 10^m*bm + 10^(n-1)*bm-1 +...+1	0*b1 + b0 
	// a * b = (10^n*an + 10^(m-1)*am-1 +...+10*a1 + a0) * (10^m*bm + 10^(m-1)*bm-1 +...+10*b1 + b0 )
	//The digit a_i multiplied with b_j will be added to the result like this 
	//	a_i * b_j * 10 ^(i + j) 
	//So to find the multiplication of a and b we shall add every combination of i,j 
	//It is true that a_i * b_j * 10 ^(i + j) will be added to (i+j)th digit of the result
	//We shall % modulo it with 10 and keep the reult to 
	//	digit and pass to the next digit the overflown 
	//  value and add it[result[i+j+1] +=result[i+j]/10]
	//If result[i+j] < 10 the division and modulo will not change anything
	//We account for overflow for all digits correctly. Since we iterate in order all pairs 
	//	(i,j) [(0,0),(0,1)...(0,m),(1,0),(1,1)...(1,m)...(n,0),(n,1)...(n,m)]
	//	If we accounted overflow for a pair (i+k,j-k)[index i+j], we are sure that we will
	//  	account overflow for index [index i+j+1], since (i+k+1,j-k) will be seen after (i+k,j-k)  	  
	//At last we shall strip any zeros, because the multiplication shall not use all n+m digits in result
	//	then reverse and apply the sign.
	//Time Complexity is O(n*m) because we need to add every (i,j) partial multiplication
	 
	 
	//Retrieve in a bool variable if the result is negative
	//Either one of the first digit of both numbers shall be negative 
	//	for result to be negative 
	bool is_negative = (a[0] < 0) xor (b[0] < 0); 
	
	//Ensure we do multiplication with positive numbers
	a[0] = std::abs(a[0]),b[0] = std::abs(b[0]);
	
	
	//Reverse the numbers for easier multiplication
	std::reverse(a.begin(),a.end());
	std::reverse(b.begin(),b.end());
	
	//Defining result to have n+m size
	std::vector<int> result(a.size()+b.size(),0);
	
	//Iterating on all combinations (i,j) 
	for (int i = 0; i < (int) a.size() ;i++){
		for (int j = 0; j < (int) b.size() ;j++){
			//std::cout << i +1 <<":"<< a[i] << " -"<< j +1 << ":"<< b[j] << "\n";
			//Defining the index. Index is the power of 10 in essence
			int index = i + j;
			
			//Add to the result the partial multiplication
			result[index] += a[i]*b[j];
			
			//Add to the next digit the overflow  
			result[index+1] += result[index]/10;
			//Keeping only the last digit to the result at index 
			result[index] %=10;  
		}
	}
	
	//Strip the Zeros of the result
	//Looping until no more zeros at back are apparent
	while(result.size() != 1 && result.back() == 0 ){
		result.pop_back();
	}
	
	//reversing the result
	std::reverse(result.begin(),result.end());
	
	//Applying the sig
	if (is_negative == true) result[0] *=-1;
	
	return result;
}



std::optional<int>ParseInt(std::string_view text){
	//Takes input a string [std::string_view], parses and then outputs an optional int
	
	int value{};
	const auto [ptr,ec] = std::from_chars( text.data(),text.data() + text.size(),value,10);
	
	//Check for any errors 
	if (ec != std::errc() || ptr != text.data() + text.size()) return std::nullopt;	 
	
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


std::vector<int> ParseVectorDigit(const std::vector<std::string>& Vector){
	std::vector<int> result;
	for (int i = 0; i < (int) Vector.size();i++) {
			//Parsing
			std::string s = Vector[i];
			
			std::optional<int> n = ParseInt(s);
			if (!n) {
				std::cout << "Error parsing '" << s << "' into a number\n";
				throw std::invalid_argument("Digits must be in range [0,9]");
			}
			
			//Only allow first digit to be negative
			if (i == 0 && (abs(*n) >= 0 && abs(*n) <=9)){
				result.push_back(*n);
			}else if(*n >= 0 &&  *n <=9){
				result.push_back(*n);
			}else{
				std::cout << "Digits must be in range [0,9] \n";
				std::cout << "Error digit is "<<*n<<"\n";
				throw std::exception();
			}
			
	}

	return result;
}

int main(int argc,char ** argv){
	
	//Check Argument Count
	if (argc !=3){
		std::cout << "Usage: ./Multiply <Array> <Array>\n";
		return 1;
	}
	
	//Parsing the Argumnets
	std::vector<std::string> o_array1 = Split(argv[1],",");
	std::vector<std::string> o_array2 = Split(argv[2],",");
	           
	
	//Getting the Values
	std::vector<int> a = ParseVectorDigit(o_array1);
	std::vector<int> b = ParseVectorDigit(o_array2);
	
		
	//Printing the vectors before 
	PrintVector(a);
	PrintVector(b);
	
	//Printing the vector representation of multiplying the numbers
	PrintVector(Multiply(a,b));
	

	
	

}
