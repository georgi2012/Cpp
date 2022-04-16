#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Compressor.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>  

SCENARIO("Testing string archiving")
{
	GIVEN("Testing with empty stream") {
		std::stringstream input(""), output, output2;
		WHEN("Testing if it can be archived") {
			uint32_t EC = Compressor::compress(input, output);
			THEN("Check if expanding is successful") {
				REQUIRE(EC == 0);
				Compressor::expand(output,output2);
				std::string symbows;
				char symb;
				while (output2.read(&symb, sizeof(char))) {
					symbows += symb;
				}
				REQUIRE(symbows.empty());
			}
		}
	}//given
	GIVEN("Testing for normal sentences") {
		WHEN("Testing with text") {
			const std::string text1 = "Uhm some very cool sentences I guess?";
			std::stringstream input(text1), output, output2;
			AND_WHEN("Compressing") {
				uint32_t EC = Compressor::compress(input, output);
				THEN("Testing is expanding is the same") {
					Compressor::expand(output, output2);
					std::string symbows;
					char symb;
					while (output2.read(&symb, sizeof(char))) {
						symbows += symb;
					}
					REQUIRE(symbows==text1);
					
				}
			}
		}
		WHEN("Testing with weird text") {
			const std::string text1 = "std::stringstream input(std::stringstream input\
				(std::stringstream input(std::stringstream input(std::stringstream input(std::stringstream input(text1))))))";
			std::stringstream input(text1), output, output2;
			AND_WHEN("Compressing") {
				uint32_t EC = Compressor::compress(input, output);
				THEN("Testing is expanding is the same") {
					Compressor::expand(output, output2);
					std::string symbows;
					char symb;
					while (output2.read(&symb, sizeof(char))) {
						symbows += symb;
					}
					REQUIRE(symbows == text1);
				}
			}
		}
		WHEN("Testing with numbers only") {
			const std::string text1 = "12341211142422112124141249191818171821921812484124128175828219125922141992182182147218421\
123412111424221121241412491918181718219218124841241281758282191259221419921821821472184211234121114242211212414124919181817\
182192181248412412817582821912592214199218211234121114242211212414124919181817182192181248412412817582821912592214199218218214721842182147218421";
			std::stringstream input(text1), output, output2;
			AND_WHEN("Compressing") {
				uint32_t EC = Compressor::compress(input, output);
				THEN("Testing is expanding is the same") {
					Compressor::expand(output, output2);
					std::string symbows;
					char symb;
					while (output2.read(&symb, sizeof(char))) {
						symbows += symb;
					}
					REQUIRE(symbows == text1);
				}
			}
		}//when
		WHEN("Testing with Ivan Mihov's favorite string") {
			const std::string text1 = "Jugemu Jugemu Goko no Surikire Kaijarisuigyo no Suigyomatsu Unraimatsu Furaimatsu Ku Neru \
Tokoro ni Sumu Tokoro Yabura Koji no Bura Koji Paipo-paipo Paipo no Shurigan Shuringan no Gurindai Gurindai no Ponpokopi no \
Ponpokona no Chokoyumwi no Chosuke";
			std::stringstream input(text1), output, output2;
			AND_WHEN("Compressing") {
				uint32_t EC = Compressor::compress(input, output);
				THEN("Testing is expanding is the same") {
					Compressor::expand(output, output2);
					std::string symbows;
					char symb;
					while (output2.read(&symb, sizeof(char))) {
						symbows += symb;
					}
					REQUIRE(symbows == text1);
				}
			}
		}//when
		WHEN("Testing with some really long stream") {
			std::string text1; //we will create it in random
			std::srand(time(NULL));
			unsigned index = 0;
			std::cout << "Long stream case: ";
			while (index < 10'000) {
				text1+=  std::rand() % 127;
				++index;
			}
			for(int i=0;i<5;i++)
				text1 +=text1;
			std::cout << "(" << text1.size() << " bytes)";
			std::stringstream input(text1), output, output2;
			AND_WHEN("Compressing") {
				uint32_t EC = Compressor::compress(input, output);
				THEN("Testing is expanding is the same") {
					Compressor::expand(output, output2);
					std::string symbows;
					char symb;
					while (output2.read(&symb, sizeof(char))) {
						symbows += symb;
					}
					REQUIRE(symbows == text1);
				}
			}
		}//when
	}

}//scen

