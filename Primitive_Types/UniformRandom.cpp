#include <iostream>
#include <charconv> 
#include <cstdint>
#include <optional>
#include <system_error>
#include <string_view>
#include <string>
#include <cmath>
#include <random>


//How would you implement a random number generator that generates a random
//integer i between a and b, inclusive, given a random number generator that produces
//zero or one with equal propability ? All values in [a,b] should be equally likely

// sources :
// 	https://en.cppreference.com/cpp/utility/from_chars
// 	https://en.cppreference.com/cpp/numeric/random/random_device


int RandomBit() {
    //Function that returns 0 or 1 with equal propability
    
    static std::mt19937 gen{std::random_device{}()};
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen);
}

int UniformRandom(int a, int b){
	//Takes input 2 integers and computes a random number inside [a,b]
	//Note that we can drawing a random number from [a,b] is the same as
	//drawing a random number from [0,b-a] and adding a
	//A way of creating an equally likely random number is by 
	//concantinating the bits of the random function i times
	//However we cant use this method for all cases of b -a
	//If b - a  =  2^i - 1 then we can use the above method
	//If b - a !=  2^i - 1 then:
	//Iterate until we find the lowest number 2^i-1 >= b-a and concantinate the bits
	//If the result is less than b-a, we have succesfully created a random number otherwise
	//loop again
	//return the result + a    
	// Note that in the iteration we do the condition (1 << i) < new_bound, and stop at lowest 2^i - 1
	
	//Time Complexity is O(log_2(b-a+1))
	
	//The propability of success is t/2^i where t = b - a + 1
	//Since 2^i is smallest power of 2 greater than or equal to t 
	//then 2^i must be less than 2t
	//2^i < 2t <=> t/2^i > 1/2
	//So the propability of failiure in the first try is P(fail) = 1- t/2^i < 1/2
	
	//The propability that more than k tries are needed is less or equal to 1/2^k (independent events)
	
	//Expected Tries = 1 + 2*P(Fail)^1 + 3*P(Fail)^2 + ... + k*P(Fail)^k-1
	
	//Expected Tries < 1 + 2(1/2)^1 + 3(1/2)^2 + ... + k(1/2)^k-1 which converges
	
	//So number of tries is O(1)
	
	//Each Try makes ceil(log_2(b-a+1)) calls to the random function
	
	
	
	//Definitions
	int new_bound = b-a;
	int result;
	
	//Loop until we found number in bounds
	do {
		//Reset result
		result = 0.0;
		
		//Loop until MSB
		for (int i = 0; (1<<i) < new_bound;i++ ){
			//Build random number with concantination
			result = (result << 1) | RandomBit();
		}
		
	}while(result > new_bound );
	
	//Add a, so random number is in [a,b]
	result +=a;
	
	return result;
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
	if (argc !=3){
		std::cout << "Usage: ./UniformRandom <a> <b>";
		return 1;
	}
	
	//Parsing the Argumnet
	std::optional<int> o_arg1 = ParseInt(argv[1]);
	std::optional<int> o_arg2 = ParseInt(argv[2]);
	
	//Check if value exist
	if (!o_arg1 || !o_arg2){
		std::cout << "a,b must be a number or in range\n" ;
		return 1;
	}
	
	//Getting the Values
	int a = *o_arg1;
	int b = *o_arg2;
	
	//Output of random number in [a,b] from UniformRandom
	std::cout << "Random Number in ["<<a<<","<<b<<"] : " << UniformRandom(a,b) << "\n" ;
	
	return 0;
}
