#include "FrontEnd.h"
#include <iostream>

//Testing given excamples with console output

using std::cout;
using std::endl;

void createTestFiles()
{
    std::fstream file;
    const string file1 = "FrontEndTest_Lozenec.txt";
    const string file2 = "FrontEndTest_Lozenec_new.txt";
    file.open(file1, std::ofstream::out | std::ofstream::trunc); //delete content or create file
    if (file) {
        file <<"Uspeshnia - Gosho\n"
            "Uspeshnia - Misho\n"
            "Gosho - Pesho\n"
            "Gosho - Dancho\n"
            "Pesho - Alex\n"
            "Dancho - Boris\n"
            "Dancho - Kamen\n"
            "Uspeshnia - Slavi\n"
            "Slavi - Slav1\n"
            "Slavi - Slav2\n"
            "Slav1 - Mecho\n"
            "Mecho - Q12Adl\n";
        file.close();
        std::cout << "(Creates test file " << file1 << ")\n";
    }
    else {
        std::cout << "There was a problem creating test file.\n";
        throw ExitProgram();
    }
    //File2
    file.open(file2, std::ofstream::out | std::ofstream::trunc); //delete content or create file
    if (file) {
        file << "Uspeshnia - Mitko\n"
            "Mitko - MishoPetrov\n"
            "MishoPetrov - Misho\n"
            "Misho - Slav\n";
        file.close();
        std::cout << "(Creates test file " << file2 << ")\n";
    }
    else {
        std::cout << "There was a problem creating test file.\n";
        throw ExitProgram();
    }
}

int main() {
    FrontEnd processor;
    try {
        createTestFiles();
        std::cout << "load Lozenec FrontEndTest_Lozenec.txt\n";
        processor.executeCommand("load Lozenec FrontEndTest_Lozenec.txt");
        std::cout << "find Lozenec Alex\n";
        processor.executeCommand(" find Lozenec Alex ");
        std::cout << "num_subordinates Lozenec Alex \n";
        processor.executeCommand("num_subordinates Lozenec Alex ");
        std::cout << "manager Lozenec Slav1 \n";
        processor.executeCommand("manager Lozenec Slav1");
        std::cout << "num_employees Lozenec\n";
        processor.executeCommand("num_employees Lozenec");
        std::cout << "num_employees Lozenec2\n";
        processor.executeCommand("num_employees Lozenec2");
        std::cout << "overloaded Lozenec\n";
        processor.executeCommand("overloaded Lozenec");
        std::cout << "load Lozenec_new FrontEndTest_Lozenec_new.txt\n";
        processor.executeCommand("load Lozenec_new FrontEndTest_Lozenec_new.txt");
        processor.executeCommand("join Lozenec Lozenec_new LozBig");
        std::cout << "save LozBig FrontEndTest_LozBig.data \n";
        processor.executeCommand("save LozBig FrontEndTest_LozBig.data ");
        std::cout << " manager LozBig Misho\n";
        processor.executeCommand("manager LozBig Misho ");
        std::cout << "num_subordinates LozBig MishoPetrov \n";
        processor.executeCommand("num_subordinates LozBig MishoPetrov ");
        std::cout << "fire LozBig MishoPetrov \n";
        processor.executeCommand("fire LozBig MishoPetrov ");
        std::cout << "num_subordinates LozBig Uspeshnia \n";
        processor.executeCommand("num_subordinates LozBig Uspeshnia ");
        std::cout << "save LozBig LozBig.data \n";
        processor.executeCommand("save LozBig LozBig.data ");
        std::cout << "hire Lozenec MishoPetrov Misho \n";
        processor.executeCommand("hire Lozenec MishoPetrov Misho ");
        std::cout << "salary Lozenec Gosho \n";
        processor.executeCommand("salary Lozenec Gosho ");
        std::cout << "hire Lozenec_new Mitko Uspeshnia \n";
        processor.executeCommand("hire Lozenec_new Mitko Uspeshnia ");
        std::cout << "hire Lozenec_new MishoPetrov Mitko \n";
        processor.executeCommand("hire Lozenec_new MishoPetrov Mitko ");
        std::cout << "incorporate Lozenec_new \n";
        processor.executeCommand("incorporate Lozenec_new ");
        std::cout << "save Lozenec_new \n";
        processor.executeCommand("save Lozenec_new ");
        std::cout << "hire Lozenec_new Ivan Misho \n";
        processor.executeCommand("hire Lozenec_new Ivan Misho ");
        std::cout << "hire Lozenec_new Stojan Ivan \n";
        processor.executeCommand("hire Lozenec_new Stojan Ivan ");
        std::cout << "modernize Lozenec_new \n";
        processor.executeCommand("modernize Lozenec_new ");
        std::cout << "save Lozenec_new \n";
        processor.executeCommand("save Lozenec_new ");
        std::cout << "save Lozenec_new loz.data\n";
        processor.executeCommand("save Lozenec_new loz.data");
        std::cout << "exit\n";
        processor.executeCommand("exit");
        
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
   
    return 0;
}