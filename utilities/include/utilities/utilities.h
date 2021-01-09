#ifndef _UTILITIES_H__
#define _UTILITIES_H__
namespace multicamera{
	namespace utilities{
		///Utility function to get the size of the array at compile time
		//TODO: Add compile time restriction about the input type 
		//only arrays are allowed
		template<std::size_t N, class T>
		constexpr std::size_t countof(T(&)[N]) 
		{ return N; }
	}
}
#define

