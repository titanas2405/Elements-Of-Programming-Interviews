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

//Write a program that takes an array A and an index i into A, and rearranges the elements such that all the 
//elements less than A[i] (the "pivot") appear first, followed by elements equal to the pivot,followed by
//elements greater than the pivot


//Variants:
//	1: Asumming that keys take one of three values, reorder the array so that all objects with the same 
//     key appear together. The order is not important. Use O(1) aditional space and O(n) time
//
//		Solution: Apply the Optimized Dutch Flag Partition algorithm
//
//	2: Given an array A of n objects with keys that take one of four values, reorder the arrays so that all
//	   objects that have the same key appear together
//		
//		Solution: Find the second lowest value and choose it as a pivot. Apply the Optimized Dutch Flag Partition 
//				  algorithm to form the 2 groups. Apply the to the upper mixed group again the algorithm and choose
//				  the lower value from the two as the pivot
//
//	3: Given an array A of n objects with Boolean-valued keys, reorder the array so that objects that have the key
//	   false appear first. Use O(1) additional space and O(n) time
//
//		Solution: true == 1 and false == 0 so choose as pivot false and apply only the first swap loop 
//				  of the Optimized Dutch Flag Partition algorithm 
//
//	4: Given an array A of n objects with Boolean-valued keys, reorder the array so that objects that have the key
//	   false appear first. The relative ordering of objects with key true should not change.
//	   Use O(1) additional space and O(n) time
//	
//		Solution: true == 1 and false == 0 so choose as pivot false and apply only the second swap loop 
//				  of the Optimized Dutch Flag Partition algorithm 


//sources https://en.cppreference.com/cpp/utility/from_chars
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c	
//https://www.w3schools.com/cpp/cpp_list.asp


void DutchFlagPartition(int pivot_index,std::vector<int>& A){
	//Takes input a pivot index and an vector of colors and and rearranges the elements such that all the 
	//elements less than A[pivot_index] appear first, followed by elements equal to the pivot,followed by
	//elements greater than the pivot
	
	//For this we create 3 lists.
	// - One for elements lower than A[pivot_index]
	// - One for elements equal to A[pivot_index]
	// - One for elements greater than A[pivot_index]
	
	//Then we concantinate and return the newly formed vector
	
	//Time complexity is O(n)
	//Space Complexity is O(n)
	
	//Definitions of lists
	std::list<int> l_list;
	std::list<int> e_list;
	std::list<int> g_list;
	std::list<int> merged;
	
	//Looping to all elements of A
	int pivot_element = A[pivot_index];
	for (const auto& e : A) {
		//Pushing to appropriate list
		if (e<pivot_element) l_list.push_front(e);
		if (e==pivot_element) e_list.push_front(e);
		if (e>pivot_element) g_list.push_front(e);
	}
	
	//Merging the lists
	merged.splice(merged.end(), l_list, l_list.begin(), l_list.end());
	merged.splice(merged.end(), e_list, e_list.begin(), e_list.end());
	merged.splice(merged.end(), g_list, g_list.begin(), g_list.end());
	
	
	
	//Assigning to A the merged list
	A.assign(merged.begin(), merged.end());
	
}

void OptimizedDutchFlagPartition(int pivot_index,std::vector<int>& A){
	//Takes input a pivot index and an vector of colors and and rearranges the elements such that all the 
	//elements less than A[pivot_index] appear first, followed by elements equal to the pivot,followed by
	//elements greater than the pivot
	
	//To optimize in space complexity to O(1) and keeping the 
	//same time complexity O(n) we apply a two-swap technique:
	
	//First, group all elements less than pivot:
	
	//	For an element at index j we shall swap it with an element at index i we are sure
	//	that is less than the pivot
	//	if the element at index j is less than the pivot then the swap with element at index i does not do anything 
	//	if the element at index j is bigger than the pivot then the swap with element at index i shall fix the inequallity 
	//	By placing always an element at index i that is less than the pivot at the furthest possible spot to the left
	//	(increasing the furthest possible spot) we ensure that we have grouped all the smaller elements than the pivot  
	//	We have splitted the array into two subrrays A1,A2, where max(A1) < pivot and min(A2) >= pivot
	//	We only need to loop once the whole vector, because if encounter an element less than the pivot we swap, meaning we dont 
	//	skip any elemnts bigger than the pivot
	
	//Second, group all element bigger than the pivot
	//	We do almost the same as the previous pass except we swap when element at index i is  bigger than the pivot
	//	and stop once we reach the left group 

	//After the second pass, we ensure that we form the 3 groups we neesd
	// - One for elements lower than pivot
	// - One for elements equal to pivot
	// - One for elements greater pivot
	
	
	
	
	//Definitions
	int pivot = A[pivot_index];
	int smaller = 0;
	int larger = A.size() -1;
	//Iterate the whole vector in forward order
	for (int i = 0; i< (int) A.size();i++){
		//swap when less than pivot
		if (A[i] < pivot) std::swap(A[i],A[smaller++]);
	}
	
	//Iterate the whole vector in backward order
	for (int i = (int) A.size()-1; i>= 0 && A[i]>= pivot;i--){
		//swap when greater than pivot
		if (A[i] > pivot) std::swap(A[i],A[larger--]);
	}
	
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
		std::cout << "Usage: ./DutchFlagPartion <Array> <i>\n";
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
	
	
	
	if (i < 0 || i > (int)ints.size()){ 
		std::cout << "i out of bounds\n" ;
		return 1;
	}
				   
	PrintVector(ints);
	OptimizedDutchFlagPartition(i,ints);
	PrintVector(ints);
	std::cout << "i :" << i << "\n" ;
	
}
