#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Command.h"

SCENARIO("Testing command class") {

	GIVEN("Creating command object") {
		Command command;

		WHEN("Testing if white spaces are removed and different commands are recognized") {
			//are case sensitive
			THEN("Test for Save") {
				command.processCommand("SaVe");
				REQUIRE(command.getCommand() == CommandOption::_save);
				command.processCommand("   savE           ");
				REQUIRE(command.getCommand() == CommandOption::_save);
			}
			THEN("Test for load") {
				command.processCommand("load");
				REQUIRE(command.getCommand() == CommandOption::_load);
				command.processCommand("   loAd      nothing     ");
				REQUIRE(command.getCommand() == CommandOption::_load);
			}
			THEN("Test for find") {
				command.processCommand("find");
				REQUIRE(command.getCommand() == CommandOption::_find);
				command.processCommand("   FInd      nothing     ");
				REQUIRE(command.getCommand() == CommandOption::_find);
			}
			THEN("Test for num_subordinates") {
				command.processCommand("num_subordinates");
				REQUIRE(command.getCommand() == CommandOption::_num_subordinates);
				command.processCommand("   nuM_sUbordinates     adc  ");
				REQUIRE(command.getCommand() == CommandOption::_num_subordinates);
			}
			THEN("Test for manager") {
				command.processCommand("manager");
				REQUIRE(command.getCommand() == CommandOption::_manager);
				command.processCommand("   mANager       ");
				REQUIRE(command.getCommand() == CommandOption::_manager);
			}
			THEN("Test for num_employees") {
				command.processCommand("num_employees");
				REQUIRE(command.getCommand() == CommandOption::_num_employees);
				command.processCommand("   num_EMployEes       ");
				REQUIRE(command.getCommand() == CommandOption::_num_employees);
			}
			THEN("Test for overloaded") {
				command.processCommand("overloaded");
				REQUIRE(command.getCommand() == CommandOption::_overloaded);
				command.processCommand("    overloaDEd  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_overloaded);
			}
			THEN("Test for Exit") {
				command.processCommand("eXit");
				REQUIRE(command.getCommand() == CommandOption::_exit);
				command.processCommand("   exIt   a  a      ");
				REQUIRE(command.getCommand() == CommandOption::_exit);
			}
			THEN("Test for Help") {
				command.processCommand("heLp");
				REQUIRE(command.getCommand() == CommandOption::_help);
				command.processCommand("   hElp   is needed a  a      ");
				REQUIRE(command.getCommand() == CommandOption::_help);
			}
			THEN("Test for join") {
				command.processCommand("join");
				REQUIRE(command.getCommand() == CommandOption::_join);
				command.processCommand("   jOIn   is needed a  a      ");
				REQUIRE(command.getCommand() == CommandOption::_join);
			}
			THEN("Test for fire") {
				command.processCommand("fire");
				REQUIRE(command.getCommand() == CommandOption::_fire);
				command.processCommand("    fIRe  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_fire);
			}
			THEN("Test for hire") {
				command.processCommand("hire");
				REQUIRE(command.getCommand() == CommandOption::_hire);
				command.processCommand("    HIRe  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_hire);
			}
			THEN("Test for salary") {
				command.processCommand("salary");
				REQUIRE(command.getCommand() == CommandOption::_salary);
				command.processCommand("    saLAry  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_salary);
			}
			THEN("Test for incorporate") {
				command.processCommand("incorporate");
				REQUIRE(command.getCommand() == CommandOption::_incorporate);
				command.processCommand("    incOrpOrate  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_incorporate);
			}
			THEN("Test for modernize") {
				command.processCommand("modernize");
				REQUIRE(command.getCommand() == CommandOption::_modernize);
				command.processCommand("    modERnize  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_modernize);
			}

			THEN("Test for invalid commands") {
				command.processCommand("opEnn");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
				command.processCommand("save_as");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
				command.processCommand(" cl0se ");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
				command.processCommand("It's a valid command");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
				command.processCommand(" \"new\"");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
				command.processCommand(" dunno ");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
				command.processCommand("tests are boring to write...");
				REQUIRE(command.getCommand() == CommandOption::_invalid);
			}
		}//when com rec

		WHEN("Testing if parameters are set correctly")
		{
			THEN("Testing getOneParamether") {
				command.processCommand("modERnize  object1      ");
				REQUIRE(command.getOneParamether() == "object1");

				command.processCommand("modERnize  object1  andalsoObj2    ");
				REQUIRE(command.getOneParamether() == "object1");
				AND_THEN("Testing with empty string") 
				{
					command.processCommand("");
					REQUIRE(command.getOneParamether().empty());
				}
			}
			//in our case getOpenPath calls SaveAsPath so we have tested it already^
			THEN("Testing getTwoParamether") {
				StrTuple ans;
				command.processCommand("fire   first  second   ");
				ans = command.getTwoParamether();
				REQUIRE(ans.first == "first");
				REQUIRE(ans.second == "second");
				REQUIRE(ans.third.empty());

				command.processCommand(" fire   fiRst  second  third ");
				ans = command.getTwoParamether();
				REQUIRE(ans.first == "fiRst");
				REQUIRE(ans.second == "second");
				REQUIRE(ans.third.empty());

				command.processCommand(" fire   fiRst  ");
				ans = command.getTwoParamether();
				REQUIRE(ans.first == "fiRst");
				REQUIRE(ans.second.empty());
				REQUIRE(ans.third.empty());

				AND_THEN("Testing with empty string")
				{
					command.processCommand("");
					ans = command.getTwoParamether();
					REQUIRE(ans.first.empty());
					REQUIRE(ans.second.empty());
					REQUIRE(ans.third.empty());
				}
				THEN("Testing path recognition") {
					command.processCommand("load  some_name  \"C:\\Temp\\another file.xml\" ");
					ans = command.getTwoParamether();
					REQUIRE(ans.second == "C:\\Temp\\another file.xml");
				}
			}
			THEN("Testing getThreeParamether") {
				StrTuple ans;
				command.processCommand("join   first  second  last ");
				ans = command.getThreeParamether();
				REQUIRE(ans.first == "first");
				REQUIRE(ans.second == "second");
				REQUIRE(ans.third == "last");

				command.processCommand(" join   fiRst  second  ");
				ans = command.getThreeParamether();
				REQUIRE(ans.first == "fiRst");
				REQUIRE(ans.second == "second");
	

				command.processCommand(" join   fiRst  ");
				ans = command.getThreeParamether();
				REQUIRE(ans.first == "fiRst");
				REQUIRE(ans.second.empty());

				AND_THEN("Testing with empty string")
				{
					command.processCommand("");
					ans = command.getTwoParamether();
					REQUIRE(ans.first.empty());
					REQUIRE(ans.second.empty());
					REQUIRE(ans.third.empty());
				}

			}
		}
	}//given

}//scenario
