#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Commands.h"

SCENARIO("Testing command class") {

	GIVEN("Creating command object") {
		Commands command;

		WHEN("Testing if white spaces are removed and different commands are recognized") {
			//are case sensitive
			THEN("Test for _using") {
				command.processCommand("using");
				REQUIRE(command.getCommand() == CommandOption::_using);
				command.processCommand("   uSiNg           ");
				REQUIRE(command.getCommand() == CommandOption::_using);
			}
			THEN("Test for _zip") {
				command.processCommand("zip");
				REQUIRE(command.getCommand() == CommandOption::_zip);
				command.processCommand("   ZiP      nothing     ");
				REQUIRE(command.getCommand() == CommandOption::_zip);
			}
			THEN("Test for _unzip") {
				command.processCommand("unzip");
				REQUIRE(command.getCommand() == CommandOption::_unzip);
				command.processCommand("   uNzIp      nothing     ");
				REQUIRE(command.getCommand() == CommandOption::_unzip);
			}
			THEN("Test for _info") {
				command.processCommand("info");
				REQUIRE(command.getCommand() == CommandOption::_info);
				command.processCommand("   iNfO     adc  ");
				REQUIRE(command.getCommand() == CommandOption::_info);
			}
			THEN("Test for _refresh") {
				command.processCommand("refresh");
				REQUIRE(command.getCommand() == CommandOption::_refresh);
				command.processCommand("   rEfresH       ");
				REQUIRE(command.getCommand() == CommandOption::_refresh);
			}
			THEN("Test for _ec") {
				command.processCommand("ec");
				REQUIRE(command.getCommand() == CommandOption::_ec);
				command.processCommand("   eC       ");
				REQUIRE(command.getCommand() == CommandOption::_ec);
			}
			THEN("Test for _help") {
				command.processCommand("help");
				REQUIRE(command.getCommand() == CommandOption::_help);
				command.processCommand("    hELp   is needed      ");
				REQUIRE(command.getCommand() == CommandOption::_help);
			}
			THEN("Test for _show") {
				command.processCommand("show");
				REQUIRE(command.getCommand() == CommandOption::_show);
				command.processCommand("   sHoW   a  a      ");
				REQUIRE(command.getCommand() == CommandOption::_show);
			}
			THEN("Test for _exit") {
				command.processCommand("exit");
				REQUIRE(command.getCommand() == CommandOption::_exit);
				command.processCommand("   eXiT  cant be found a  a      ");
				REQUIRE(command.getCommand() == CommandOption::_exit);
			}
			THEN("Test for _add") {
				command.processCommand("add");
				REQUIRE(command.getCommand() == CommandOption::_add);
				command.processCommand("   AdD   in my      ");
				REQUIRE(command.getCommand() == CommandOption::_add);
			}
			THEN("Test for _remove") {
				command.processCommand("remove");
				REQUIRE(command.getCommand() == CommandOption::_remove);
				command.processCommand("    reMoVe  SOMETHIng      ");
				REQUIRE(command.getCommand() == CommandOption::_remove);
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
		}

		WHEN("Testing if parameters are set correctly")
		{
			THEN("Testing getOneParamether") {
				command.processCommand("using  object1      ");
				REQUIRE(command.getOneParamether() == "object1");

				command.processCommand("refresh  object1  andalsoObj2    ");
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
				command.processCommand("refresh   first  second   ");
				ans = command.getTwoParamether();
				REQUIRE(ans.first == "first");
				REQUIRE(ans.second == "second");
				REQUIRE(ans.third.empty());

				command.processCommand(" show   fiRst  second  third ");
				ans = command.getTwoParamether();
				REQUIRE(ans.first == "fiRst");
				REQUIRE(ans.second == "second");
				REQUIRE(ans.third.empty());

				command.processCommand(" show   fiRst  ");
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
			}
			THEN("Testing getThreeParamether") {
				StrTuple ans;
				command.processCommand("ec   first  second  last ");
				ans = command.getThreeParamether();
				REQUIRE(ans.first == "first");
				REQUIRE(ans.second == "second");
				REQUIRE(ans.third == "last");

				command.processCommand(" ec   fiRst  second  ");
				ans = command.getThreeParamether();
				REQUIRE(ans.first == "fiRst");
				REQUIRE(ans.second == "second");


				command.processCommand(" ec   fiRst  ");
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
